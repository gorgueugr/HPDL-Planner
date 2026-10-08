# Ejemplos

| Dominio | Problema | Descripción | ¿Funciona con el build por defecto? |
|---|---|---|---|
| `blocks.hpdl` | `blocks-problem.hpdl` | Blocksworld HTN mínimo. Plan: `(pick-up a)`, `(stack a b)`. | **Sí** |
| `bloques.hpdl` | `bloques-problem.hpdl` | Ejemplo original del proyecto (bloques, en español), con `:fluents`, `:derived-predicates` y una función definida en Python. | **No**, necesita Python 2.7 |

## `bloques.hpdl` necesita Python

Usa la función

```
(:functions
  (igual ?x ?y) { return ?x == ?y }
)
```

que se evalúa con el intérprete Python 2.7 embebido. HPDL no tiene un objetivo de
igualdad entre términos (el token `=` de la gramática es solo comparación numérica), así
que este dominio no se puede escribir sin Python. Para ejecutarlo:

```bash
cmake -S . -B build -DHPDL_ENABLE_PYTHON=ON     # requiere python2.7-dev
cmake --build build -j
./build/planner -d examples/bloques.hpdl -p examples/bloques-problem.hpdl
```

Con el build por defecto falla con
`Parser compiled without Python support. Install python and recompile.`

## Uso

```bash
# plan del ejemplo minimo
./build/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl

# con el arbol de descomposicion
./build/planner -t -d examples/blocks.hpdl -p examples/blocks-problem.hpdl

# arbol de descomposicion (formato validador de pandaPIparser)
./build/planner -t -d examples/blocks.hpdl -p examples/blocks-problem.hpdl > plan.txt
python3 tools/format_output.py plan.txt

# volcado del plan a XML
./build/planner -x plan.xml -d examples/blocks.hpdl -p examples/blocks-problem.hpdl
```

> Recuerda: el objetivo del problema va como red de tareas
> (`(:tasks-goal :tasks (...))`), no como *goal* PDDL plano.
