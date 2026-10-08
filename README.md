# HPDL-Planner

Planificador/optimizador **HTN** (Hierarchical Task Network) con tareas compuestas de
orden parcial, planificación temporal y numérica. El lenguaje de entrada es **HPDL**.
Puedes transformar dominios HDDL con [pandaPIparser](https://github.com/panda-planner-dev/pandaPIparser).

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
./build.sh
./build/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl
```

O con `make`:

```bash
make                 # compila -> build/planner
make example         # compila y resuelve el ejemplo incluido
make run ARGS="-d mi_dominio.hpdl -p mi_problema.hpdl"
make distclean       # borra build/
```

### Windows

El codigo usa APIs POSIX (`getopt.h`, `pthread.h`), por lo que se compila dentro de
**WSL** (recomendado) o de cualquier Linux/contenedor:

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
| `-g` | depurador integrado |
| `-o <fichero>` | escribe el plan en texto plano |
| `-x <fichero>` | escribe el plan en XML |
| `--time_limit <s>` / `--depth_limit <n>` / `--expansions_limit <n>` | limites |
| `-s <n>` | semilla aleatoria |

El problema debe expresar su objetivo como red de tareas HTN:

```
(:tasks-goal
   :tasks (make-on a b))
```

En `examples/` hay un dominio Blocksworld HTN minimo (`blocks.hpdl` +
`blocks-problem.hpdl`) cuyo plan es `(pick-up a)` y `(stack a b)`.

---

## Notas de mantenimiento

- **Compila sin Python 2.7 ni readline.** Se eliminaron ambos del build (eran la causa
  principal de que no compilase). El interprete Python 2.7 embebido (legacy) se puede
  reactivar explicitamente con `cmake -DHPDL_ENABLE_PYTHON=ON`.
- Estandar **C++14**, probado con `g++ 13` y Bison 3.8 / Flex 2.6.
- El build es *out-of-source* (`build/`); no deja `parser.cpp`/`lexer.cpp` dentro del
  arbol de fuentes.

## Cita

```bibtex
@inproceedings{fdez2006bringing,
  title={Bringing users and planning technology together. Experiences in SIADEX},
  author={Fdez-Olivares, Juan and Castillo, Luis and Garc{\i}a-P{\'e}rez, Oscar and Palao, Francisco},
  year={2006}
}
```
