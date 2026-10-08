# HPDL-Planner

Planificador/optimizador **HTN** (Hierarchical Task Network) con tareas compuestas de
orden parcial, planificacion temporal y numerica. El lenguaje de entrada es **HPDL**;
tambien puedes transformar dominios HDDL con
[pandaPIparser](https://github.com/panda-planner-dev/pandaPIparser).

Articulo de referencia: <https://www.aaai.org/Papers/ICAPS/2006/ICAPS06-007.pdf>

---

## Compilar y ejecutar

**Requisitos** (los unicos): `cmake` >= 3.16, `flex`, `libfl-dev`, `bison`, `g++`/`clang++`.

```bash
sudo apt-get install -y cmake flex libfl-dev bison g++
```

> `libfl-dev` aporta `FlexLexer.h`, que el escaner C++ necesita.

### Linux / WSL

```bash
./build.sh                                                                  # -> build/planner
./build/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl
```

O con `make`:

```bash
make                 # compila -> build/planner
make example         # compila y resuelve el ejemplo minimo
make run ARGS="-d mi_dominio.hpdl -p mi_problema.hpdl"
make distclean       # borra build/
```

### Windows

El codigo usa APIs POSIX (`getopt.h`, `pthread.h`), asi que se compila dentro de **WSL**
(recomendado) o de cualquier Linux/contenedor:

```powershell
wsl -e bash -lc "cd /mnt/c/Users/soler/Desktop/void/projects/HPDL-Planner && ./build.sh"
wsl -e bash -lc "cd /mnt/c/Users/soler/Desktop/void/projects/HPDL-Planner && ./build/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl"
```

---

## Uso

```
planner [opciones] --domain_file (-d) <dominio.hpdl> --problem_file (-p) <problema.hpdl>
planner --help
```

| Opcion | Efecto |
|---|---|
| `-v[1-3]` | nivel de detalle por pantalla |
| `-t` | imprime el arbol de descomposicion del plan |
| `-g` | depurador integrado |
| `-o <fichero>` | escribe el plan en texto plano |
| `-x <fichero>` | escribe el plan en XML |
| `--time_limit <s>` / `--depth_limit <n>` / `--expansions_limit <n>` | limites |
| `-s <n>` | semilla aleatoria |

El problema debe expresar su objetivo como red de tareas HTN (no admite *goals* PDDL planos):

```
(:tasks-goal
   :tasks (make-on a b))
```

`tools/format_output.py` convierte la salida de `-t` al arbol de descomposicion en el
formato del validador de pandaPIparser:

```bash
./build/planner -t -d examples/blocks.hpdl -p examples/blocks-problem.hpdl > plan.txt
python3 tools/format_output.py plan.txt
```

Los dominios/problemas de ejemplo estan en `examples/` (ver `examples/README.md`).

---

## Estructura del codigo

```
include/hpdl/<subsistema>/   cabeceras
src/<subsistema>/            implementaciones (misma subdivision que include/)
src/planner.cpp              main
yacc/                        gramatica (parser.yy) y escaner (lexer.ll)
examples/                    dominios y problemas de ejemplo
tools/                       utilidades (format_output.py)
build/                       generado por CMake (ignorado por git)
```

| Subsistema | Contenido |
|---|---|
| `common/` | base: terminos, tipos, tabla de terminos, simbolos, meta, constantes |
| `lang/` | lenguaje de dominio: literales, fluentes, funciones, axiomas |
| `lang/goals/` | tipos de objetivo (`and`, `or`, `forall`, `exists`, `imply`, `sort`, ...) |
| `lang/effects/` | tipos de efecto (`and`, `forall`, `when`, fluentes, temporales) |
| `htn/` | tareas, metodos y redes de tareas |
| `domain/` | dominio y problema |
| `planner/` | motor: plan, agenda (`stacknode`), causalidad, reglas de control |
| `constraints/` | red de restricciones temporales (TCNM/AC3) |
| `unify/` | unificacion de terminos |
| `undo/` | deshacer cambios de estado |
| `parser/` | API del parser, escaner de entrada, XML y textos |
| `py/` | interprete Python 2.7 embebido (opcional, desactivado) |
| `debug/` | depurador integrado |

Los `#include` son **cualificados** (`#include "hpdl/planner/plan.hh"`) en vez de por
nombre suelto, asi que basta con anadir `include/` al *include path*.

---

## Notas de mantenimiento

- **Sin Python 2.7 ni readline.** Se quitaron ambos del build (eran la causa principal de
  que no compilase). El interprete Python 2.7 embebido (legacy) se puede reactivar con
  `cmake -DHPDL_ENABLE_PYTHON=ON`; entonces `examples/bloques.hpdl` tambien funciona.
- Estandar **C++14**, probado con `g++ 13`, Bison 3.8 y Flex 2.6.
  (C++17 rompe por ambiguedad de `std::data` en `src/common/check.cpp`.)
- Build *out-of-source*: no deja `parser.cpp` / `lexer.cpp` dentro del arbol de fuentes.

---

## Cita

```bibtex
@inproceedings{fdez2006bringing,
  title={Bringing users and planning technology together. Experiences in SIADEX},
  author={Fdez-Olivares, Juan and Castillo, Luis and Garc{\i}a-P{\'e}rez, Oscar and Palao, Francisco},
  year={2006}
}
```
