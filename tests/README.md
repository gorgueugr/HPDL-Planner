# Batería de tests

Verifica que los cambios del proyecto (build modernizado, reorganización en
subsistemas, eliminación de dependencias, port a Python 3) no han alterado el
comportamiento del planificador.

## Cómo se ejecuta

```bash
# con CTest (22 tests, granulares)
./build.sh && ctest --test-dir build --output-on-failure

# o compilar y ejecutar de una vez
make check

# o directamente, sin cmake
tests/run_tests.sh build/planner            # toda la batería
tests/run_tests.sh build/planner plan_blocks  # un test concreto
```

`run_tests.sh` sale con 0 si todo pasa, 1 si algo falla y 77 si el test no se
puede ejecutar en este entorno (CTest lo marca como *skipped* en vez de como
fallo).

## Qué cubre

| Grupo | Tests | Protege contra |
|---|---|---|
| Arranque y CLI | `binario_existe`, `ayuda`, `sin_argumentos` | que el binario no arranque o cambie la interfaz de línea de órdenes |
| Parser | `parse_blocks`, `parse_move` | que un dominio válido deje de parsear |
| Planificación (golden) | `plan_blocks`, `plan_move`, `plan_bloques`, `determinismo` | que el motor devuelva **otro plan** sin querer |
| Entradas inválidas | `rechaza_goal_plano`, `rechaza_sintaxis`, `rechaza_dominio_incorrecto` | que se acepten dominios/problemas mal formados o que se genere un plan con ellos |
| Formatos de salida | `salida_texto` (`-o`), `salida_xml` (`-x`), `arbol` (`-t`), `format_output` | que se rompa la salida en texto, XML o el árbol de descomposición |
| Python embebido | `plan_bloques` | que el intérprete embebido deje de funcionar (se omite si se compiló sin `python3-dev`) |
| Invariantes del repo | `includes_resueltos`, `gramatica_sincronizada`, `sin_python2`, `layout`, `sin_flex_bison_en_cmake`, `parser_reproducible` | regresiones del refactor: includes huérfanos, `generated/` desincronizado, vuelta a la API de Python 2, pérdida de la estructura de subsistemas, vuelta a exigir flex/bison |

Los tests de planificación se comparan contra ficheros *golden* en
`tests/expected/`, generados a partir de ejecuciones verificadas a mano. Si un
cambio altera un plan de forma deliberada, hay que actualizar el golden.

## Añadir un test

1. Añade el fixture en `tests/fixtures/`.
2. Escribe la función `t_mi_test()` en `tests/run_tests.sh` (usa los ayudantes
   `ok`, `no`, `skip`, `eq`, `has`, `lack`).
3. Añade el nombre a la lista `TESTS` del script y a `HPDL_TESTS` en
   `CMakeLists.txt`.

## Limitaciones conocidas

- **Segfault con *goals* PDDL planos** (`(:goal (and ...))`). El planificador
  imprime `Los goal 'planos' de pddl no están soportados.` y a continuación
  muere por señal. Es un fallo **preexistente**, no introducido por estos
  cambios: la rama de la gramática avisa por `errflow` pero no llama a
  `yyerror`, así que el error no se contabiliza y el proceso sigue con el
  objetivo sin definir. El test `rechaza_goal_plano` comprueba el contrato (se
  avisa y **no** se genera plan), no el fallo.
- **El código de salida del planificador es 0 aunque haya errores de parseo**
  (lo decide así su `main`). Por eso los tests de rechazo comprueban el texto de
  error en lugar del código de retorno.
- El planificador es POSIX: la batería está pensada para Linux/WSL.
