#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Verificacion funcional de SIADEX / HPDL-Planner.

La bateria de tests de `tests/run_tests.sh` comprueba, sobre todo, que el
binario responde (sale con 0, imprime lo esperado, rechaza lo que debe
rechazar).  Este fichero comprueba algo mas fuerte: que los planes que
produce el planificador **son correctos**, es decir, que al ejecutar sus
acciones en orden contra el estado inicial del problema se cumplen todas las
precondiciones (el plan es aplicable) y se alcanza el objetivo.

Tambien incluye la regresion del fallo de terminacion: el dominio Transport
del IPC 2020 tiene un metodo recursivo (`m-drive-to-via`) con el que la
busqueda en profundidad no terminaba nunca (consumia ~30 GB de RAM sin dar
plan).  El test exige que esa instancia se resuelva en un tiempo acotado y
con memoria acotada; con un binario sin la poda de ciclos falla por timeout.

Uso:
    python3 tests/test_siadex.py --planner build/planner
    python3 tests/test_siadex.py                        # busca build/planner
    python3 -m unittest discover -s tests -p "test_*.py"

    PLANIFICADOR=/ruta/al/planner python3 tests/test_siadex.py

Solo usa la biblioteca estandar.  El planificador necesita Linux/WSL.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
import unittest

try:                      # POSIX; en Windows el planificador no corre igual
    import resource
except ImportError:       # pragma: no cover
    resource = None

# ---------------------------------------------------------------------------
# Lectura de HPDL (subconjunto suficiente: acciones, init y tareas-objetivo)
# ---------------------------------------------------------------------------


def tokenize(text):
    """S-exprs de HPDL a lista de tokens, ignorando comentarios `;`."""
    out = []
    for line in text.splitlines():
        # los comentarios empiezan en ';' y llegan al final de la linea
        cut = line.find(";")
        if cut >= 0:
            line = line[:cut]
        line = line.strip()
        if not line:
            continue
        out.extend(re.findall(r"\(|\)|\[|\]|[^\s()\[\]]+", line))
    return out


def parse_sexpr(tokens):
    """Construye listas anidadas a partir de los tokens."""
    stack = [[]]
    for tok in tokens:
        if tok in ("(", "["):
            stack.append([])
        elif tok in (")", "]"):
            if len(stack) < 2:
                raise ValueError("parentesis desbalanceados")
            done = stack.pop()
            stack[-1].append(done)
        else:
            stack[-1].append(tok)
    if len(stack) != 1:
        raise ValueError("parentesis desbalanceados")
    return stack[0]


def parse_file(path):
    with open(path, encoding="utf-8", errors="replace") as fh:
        exprs = parse_sexpr(tokenize(fh.read()))
    if not exprs:
        raise ValueError("fichero vacio: %s" % path)
    return exprs[0]


def _items(expr):
    """Subexpresiones de un bloque, ignorando el `and` opcional."""
    return [e for e in expr[1:] if isinstance(e, list) and e
            and e[0] != "and"]


def _block(expr, key):
    """Devuelve la primera sublista que empieza por `key`."""
    for item in expr:
        if isinstance(item, list) and item and item[0] == key:
            return item
    return None


def _after(seq, key):
    """Valor (sublista) que sigue a `key` entre los hermanos de `seq`."""
    for i, item in enumerate(seq):
        if item == key:
            nxt = seq[i + 1] if i + 1 < len(seq) else None
            return nxt if isinstance(nxt, list) else None
    return None


def read_domain(path):
    """Devuelve {nombre_accion: (parametros, precondicion, efecto)}.

    Solo admite los constructores que usan los dominios de los fixtures:
    `and`, `not` y literales.  Cualquier otra cosa en una precondicion se
    rechaza explicitamente en lugar de evaluarse mal.
    """
    acciones = {}

    def visitar(seq):
        for item in seq:
            if not isinstance(item, list) or not item:
                continue
            if item[0] == ":action":
                nombre = item[1]
                params = _after(item, ":parameters") or []
                # "?x - tipo ?y - tipo" -> [?x, ?y]
                nombres = [p for p in params if isinstance(p, str)
                           and p.startswith("?")]
                acciones[nombre] = (nombres,
                                    _flatten_and(_after(item,
                                                        ":precondition")),
                                    _flatten_and(_after(item, ":effect")))
            else:
                visitar(item)

    visitar(parse_file(path))
    return acciones


def _flatten_and(expr):
    """`(and a b c)` -> [a, b, c]; `(p x)` -> [[p, x]]."""
    if not expr:
        return []
    if expr[0] == "and":
        return [e for e in expr[1:] if isinstance(e, list)]
    return [expr]


def read_problem(path):
    """Devuelve (init como conjunto de literales ground, objetivo como tareas)."""
    prob = parse_file(path)
    init = set()
    init_block = _block(prob, ":init")
    if init_block:
        for lit in _items(init_block):
            init.add(tuple(lit))
    goal = []
    goal_block = _block(prob, ":tasks-goal")
    if goal_block:
        tasks = _block(goal_block, ":tasks")
        if tasks:
            for t in _items(tasks):
                goal.append(tuple(t))
    return init, goal


def read_plan(path):
    """Lee el plan de `-o`: lineas `:action (nombre arg1 arg2 ...)`."""
    plan = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            m = re.match(r"^:action\s*\((.*)\)\s*$", line)
            if not m:
                raise ValueError("linea de plan no reconocida: %r" % line)
            parts = m.group(1).split()
            plan.append((parts[0], parts[1:]))
    return plan


# ---------------------------------------------------------------------------
# Validacion del plan
# ---------------------------------------------------------------------------


class PlanError(AssertionError):
    pass


def _ground(literal, binding):
    """Sustituye variables `?x` con el binding; devuelve tupla."""
    return tuple(binding.get(a, a) if a.startswith("?") else a
                 for a in literal)


def _holds(literal, state, binding):
    if literal[0] == "not":
        inner = literal[1]
        return _ground(inner, binding) not in state
    return _ground(literal, binding) in state


def validate_plan(actions, init, plan):
    """Ejecuta el plan sobre el estado inicial.

    Devuelve el estado final.  Lanza PlanError si una accion no es aplicable
    o no existe en el dominio.
    """
    state = set(init)
    for step, (name, args) in enumerate(plan, 1):
        if name not in actions:
            raise PlanError("paso %d: accion desconocida %r" % (step, name))
        params, pre, eff = actions[name]
        if len(params) != len(args):
            raise PlanError("paso %d: %s espera %d argumentos, recibio %d"
                            % (step, name, len(params), len(args)))
        binding = dict(zip(params, args))

        for lit in pre:
            if not _holds(lit, state, binding):
                raise PlanError(
                    "paso %d: precondicion no satisfecha en %s: %s"
                    % (step, name, _ground(lit, binding)))

        for lit in eff:
            if lit[0] == "not":
                state.discard(_ground(lit[1], binding))
            else:
                state.add(_ground(lit, binding))
    return state


# ---------------------------------------------------------------------------
# Ejecucion del planificador
# ---------------------------------------------------------------------------

LIMITE_MEMORIA_BYTES = 3 * 1024 * 1024 * 1024   # 3 GB: el bug original pedia 30


class Runner(object):
    def __init__(self, planner):
        self.planner = planner

    def run(self, domain, problem, timeout=60, plan_file=None, extra=()):
        cmd = [self.planner, "-d", domain, "-p", problem, "-v0"] + list(extra)
        if plan_file:
            cmd += ["-o", plan_file]
        t0 = time.time()
        try:
            proc = subprocess.run(
                cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                timeout=timeout, preexec_fn=_limitar_memoria)
        except subprocess.TimeoutExpired:
            raise PlanError("timeout: el planificador no termino en %ss "
                            "(posible divergencia en la busqueda)" % timeout)
        return proc, time.time() - t0


def _limitar_memoria():
    """Corta el hijo si se dispara de memoria (evita comerse la maquina)."""
    if resource is None:
        return
    try:
        resource.setrlimit(resource.RLIMIT_AS,
                           (LIMITE_MEMORIA_BYTES, LIMITE_MEMORIA_BYTES))
    except (ValueError, OSError):
        pass


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

AQUI = os.path.dirname(os.path.abspath(__file__))
RAIZ = os.path.dirname(AQUI)
EJEMPLOS = os.path.join(RAIZ, "examples")
FIXTURE_IPC = os.path.join(AQUI, "fixtures", "ipc2020-transport")


def localizar_planificador(explicito=None):
    candidatos = []
    if explicito:
        candidatos.append(explicito)
    if os.environ.get("PLANIFICADOR"):
        candidatos.append(os.environ["PLANIFICADOR"])
    candidatos += [os.path.join(RAIZ, "build", "planner"),
                   os.path.join(RAIZ, "build-wsl", "planner")]
    for c in candidatos:
        if c and os.path.isfile(c) and os.access(c, os.X_OK):
            return c
    return None


class TestSiadex(unittest.TestCase):

    planner = None

    @classmethod
    def setUpClass(cls):
        cls.planner = localizar_planificador(PLANNER_ARG)
        if not cls.planner:
            raise unittest.SkipTest(
                "no encuentro el binario: pasa --planner o define PLANIFICADOR")
        cls.runner = Runner(cls.planner)
        cls.tmp = tempfile.mkdtemp(prefix="siadex-test-")

    @classmethod
    def tearDownClass(cls):
        if getattr(cls, "tmp", None):
            shutil.rmtree(cls.tmp, ignore_errors=True)

    def plan_path(self, nombre):
        return os.path.join(self.tmp, nombre + ".plan")

    # -- comportamiento basico -------------------------------------------

    def test_ayuda(self):
        proc = subprocess.run([self.planner, "--help"],
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                              timeout=30)
        salida = (proc.stdout + proc.stderr).decode("utf-8", "replace")
        # el binario documenta la ayuda pero sale con 1; lo que importa
        # funcionalmente es que la imprima (ver nota en el README del PR)
        self.assertIn(proc.returncode, (0, 1))
        self.assertIn("domain_file", salida,
                      "la ayuda debe documentar la opcion de dominio")

    def test_rechaza_dominio_inexistente(self):
        proc, _ = self.runner.run("/no/existe/dominio.hpdl",
                                  os.path.join(EJEMPLOS,
                                               "blocks-problem.hpdl"),
                                  timeout=30)
        # OJO: el planificador informa del error pero termina con codigo 0,
        # asi que aqui solo se puede comprobar el mensaje.  Si algun dia se
        # corrige el codigo de salida, anadir assertNotEqual(returncode, 0).
        salida = (proc.stdout + proc.stderr).decode("utf-8", "replace")
        self.assertTrue("error" in salida.lower()
                        or "unable to open" in salida.lower(),
                        "un dominio inexistente debe reportarse; "
                        "salida: %r" % salida[-300:])

    # -- planes correctos, no solo "hay salida" --------------------------

    def test_blocks_plan_valido(self):
        dominio = os.path.join(EJEMPLOS, "blocks.hpdl")
        problema = os.path.join(EJEMPLOS, "blocks-problem.hpdl")
        plan_file = self.plan_path("blocks")
        proc, _ = self.runner.run(dominio, problema, plan_file=plan_file)
        self.assertEqual(proc.returncode, 0,
                         proc.stderr.decode("utf-8", "replace")[-400:])

        acciones = read_domain(dominio)
        init, _ = read_problem(problema)
        plan = read_plan(plan_file)
        self.assertTrue(plan, "el plan no puede estar vacio")

        estado = validate_plan(acciones, init, plan)
        # objetivo del problema: (:tasks-goal :tasks (make-on a b))
        self.assertIn(("on", "a", "b"), estado,
                      "tras el plan debe cumplirse (on a b); plan=%r" % (plan,))

    def test_transport_ipc2020_plan_valido(self):
        """Regresion: pfile01 del IPC 2020 (metodo recursivo)."""
        dominio = os.path.join(FIXTURE_IPC, "domain.hpdl")
        problema = os.path.join(FIXTURE_IPC, "problem.hpdl")
        plan_file = self.plan_path("transport")
        proc, segundos = self.runner.run(dominio, problema, timeout=60,
                                         plan_file=plan_file)
        self.assertEqual(proc.returncode, 0,
                         proc.stderr.decode("utf-8", "replace")[-600:])
        self.assertLess(segundos, 30,
                        "pfile01 debe resolverse rapido; tardo %.1fs "
                        "(regresion de la busqueda)" % segundos)
        self.assertTrue(
            os.path.exists(plan_file) and os.path.getsize(plan_file) > 0,
            "no se genero ningun plan en %.1fs: si el proceso murio antes, "
            "es la regresion de terminacion (DFS sin poda de ciclos). "
            "salida: %r"
            % (segundos,
               (proc.stdout + proc.stderr).decode("utf-8", "replace")[-300:]))

        acciones = read_domain(dominio)
        init, objetivos = read_problem(problema)
        plan = read_plan(plan_file)
        self.assertEqual(len(plan), 8,
                         "pfile01 tiene un plan de 8 acciones, salio %d: %r"
                         % (len(plan), plan))

        estado = validate_plan(acciones, init, plan)

        # objetivo HTN: entregar package-0 en city-loc-0 y package-1 en city-loc-2
        self.assertIn(("at", "package-0", "city-loc-0"), estado)
        self.assertIn(("at", "package-1", "city-loc-2"), estado)
        self.assertIn(("capacity", "truck-0", "capacity-1"), estado,
                      "el camion debe acabar con la capacidad inicial")
        self.assertNotIn(("in", "package-0", "truck-0"), estado)
        self.assertNotIn(("in", "package-1", "truck-0"), estado)

    def test_plan_determinista(self):
        dominio = os.path.join(FIXTURE_IPC, "domain.hpdl")
        problema = os.path.join(FIXTURE_IPC, "problem.hpdl")
        planes = []
        for i in range(2):
            plan_file = self.plan_path("det%d" % i)
            self.runner.run(dominio, problema, timeout=60, plan_file=plan_file)
            planes.append(read_plan(plan_file))
        self.assertEqual(planes[0], planes[1],
                         "dos ejecuciones deben devolver el mismo plan")

    def test_instancia_sin_solucion_termina(self):
        """pfile05 no tiene plan: debe agotar el arbol, no colgarse."""
        dominio = os.path.join(FIXTURE_IPC, "domain.hpdl")
        problema = os.path.join(self.tmp, "sin-solucion.hpdl")
        # mismo dominio, objetivo imposible: entregar en una localizacion
        # a la que no llega ninguna carretera
        with open(problema, "w", encoding="utf-8") as fh:
            fh.write("""(define (problem imposible) (:domain dom)
  (:objects
    capacity-0 capacity-1 - capacity-number
    city-loc-0 city-loc-9 - location
    package-0 - package
    truck-0 - vehicle
  )
  (:init
    (capacity-predecessor capacity-0 capacity-1)
    (at package-0 city-loc-0)
    (at truck-0 city-loc-0)
    (capacity truck-0 capacity-1)
    (type_member_capacity-number capacity-0)
    (type_member_capacity-number capacity-1)
    (type_member_location city-loc-0)
    (type_member_location city-loc-9)
    (type_member_package package-0)
    (type_member_vehicle truck-0)
  )
  (:tasks-goal
      :tasks [
        (deliver package-0 city-loc-9)
      ]
  )
)
""")
        plan_file = self.plan_path("imposible")
        proc, segundos = self.runner.run(dominio, problema, timeout=60,
                                         plan_file=plan_file)
        err = proc.stderr.decode("utf-8", "replace")
        self.assertIn("Empty stack", err,
                      "una instancia sin solucion debe agotar el arbol; "
                      "salida: %r" % err[-400:])
        self.assertLess(segundos, 30, "agotar el arbol debe ser rapido")

    def test_plan_invalido_se_detecta(self):
        """El validador no debe dar por bueno un plan incorrecto."""
        acciones = read_domain(os.path.join(EJEMPLOS, "blocks.hpdl"))
        init, _ = read_problem(os.path.join(EJEMPLOS, "blocks-problem.hpdl"))
        with self.assertRaises(PlanError):
            validate_plan(acciones, init, [("stack", ["a", "b"])])
        with self.assertRaises(PlanError):
            validate_plan(acciones, init, [("volare", ["a"])])


def _parse_args(argv):
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    p.add_argument("--planner", default=None,
                   help="ruta al binario `planner` (si no, build/planner)")
    p.add_argument("resto", nargs="*", help="argumentos para unittest")
    return p.parse_known_args(argv)


PLANNER_ARG = None

if __name__ == "__main__":
    args, desconocidos = _parse_args(sys.argv[1:])
    PLANNER_ARG = args.planner
    TestSiadex.planner = PLANNER_ARG
    unittest.main(argv=[sys.argv[0]] + args.resto + desconocidos, exit=True,
                  verbosity=2)
