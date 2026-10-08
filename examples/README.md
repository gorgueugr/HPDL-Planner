# Ejemplos

| Dominio | Problema | Descripcion | Con el build por defecto |
|---|---|---|---|
| `blocks.hpdl` | `blocks-problem.hpdl` | Blocksworld HTN minimo. Plan: `(pick-up a)`, `(stack a b)`. | **Si** |
| `bloques.hpdl` | `bloques-problem.hpdl` | Ejemplo original del proyecto (bloques, en espanol), con `:fluents`, `:derived-predicates` y una funcion definida en Python. | **Si, si se detecta Python 3** |

## `bloques.hpdl` y el interprete Python

Usa la funcion

```
(:functions
  (igual ?x ?y) { return ?x == ?y }
)
```

que se evalua con el interprete Python embebido. HPDL no tiene un objetivo de igualdad
entre terminos (el token `=` de la gramatica es solo comparacion numerica), asi que este
dominio no se puede escribir sin Python.

El soporte se **autodetecta**: con las cabeceras de Python 3 presentes se compila, y si no
se desactiva. Para asegurarte:

```bash
sudo apt-get install python3-dev
cmake -S . -B build -DHPDL_PYTHON=ON     # ON | AUTO (por defecto) | OFF
cmake --build build -j
./build/planner -d examples/bloques.hpdl -p examples/bloques-problem.hpdl
```

Plan que produce (6 acciones):

```
:action (desapilar C B)
:action (dejar C)
:action (desapilar B A)
:action (dejar B)
:action (coger A)
:action (apilar A C)
```

Si compilas sin Python, `bloques.hpdl` falla con
`Parser compiled without Python support. Install python and recompile.`

## Uso

```bash
# ejemplo minimo
./build/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl

# arbol de descomposicion (formato del validador de pandaPIparser)
./build/planner -t -d examples/blocks.hpdl -p examples/blocks-problem.hpdl > plan.txt
python3 tools/format_output.py plan.txt

# volcado del plan a XML
./build/planner -x plan.xml -d examples/blocks.hpdl -p examples/blocks-problem.hpdl
```

> Recuerda: el objetivo del problema va como red de tareas
> (`(:tasks-goal :tasks (...))`), no como *goal* PDDL plano.
