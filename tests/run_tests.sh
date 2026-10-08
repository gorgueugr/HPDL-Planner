#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# Bateria de tests de HPDL-Planner.
#
#   tests/run_tests.sh <ruta_al_binario> [nombre_test|all]
#
# Sale con 0 si todo pasa, 1 si algo falla y 77 si el test no se puede
# ejecutar en este entorno (CTest lo interpreta como SKIP).
#
# Pensada para Linux/WSL (el planificador es POSIX).
# ---------------------------------------------------------------------------
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="${1:-$ROOT/build/planner}"
ONLY="${2:-all}"
FIX="$ROOT/tests/fixtures"
EXP="$ROOT/tests/expected"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

# timeout es de POSIX; en Windows/git-bash puede no existir
if command -v timeout >/dev/null 2>&1; then TMO="timeout 60"; else TMO=""; fi

PASS=0; FAIL=0; SKIP=0
ok()   { echo "  PASS  $1"; PASS=$((PASS+1)); }
no()   { echo "  FAIL  $1"; echo "        $2"; FAIL=$((FAIL+1)); }
skip() { echo "  SKIP  $1  ($2)"; SKIP=$((SKIP+1)); }
eq()   { if [ "$2" = "$3" ]; then ok "$1"; else no "$1" "esperado:
$(printf '%s' "$3")
        obtenido:
$(printf '%s' "$2")"; fi; }
has()  { case "$2" in *"$3"*) ok "$1";; *) no "$1" "no aparece <<$3>> en:
$(printf '%s' "$2" | head -5)";; esac; }
lack() { case "$2" in *"$3"*) no "$1" "no deberia aparecer <<$3>> en:
$(printf '%s' "$2" | head -5)";; *) ok "$1";; esac }

# El planificador puede morir por señal con entradas invalidas (ver
# tests/README.md). Se ejecuta en un grupo cuyo stderr se descarta, de modo que
# el aviso "Segmentation fault" del shell no ensucie la salida de la bateria,
# pero SI se conserva la salida del propio planificador.
run()  { { $TMO "$BIN" "$@" 2>&1; } 2>/dev/null; }       # stdout+stderr
plan() { run "$@" | grep -E '^:action ' || true; }      # solo las acciones

# --------------------------------------------------------------------------
# 1-3  arranque y linea de ordenes
# --------------------------------------------------------------------------
t_binario_existe() {
    if [ -x "$BIN" ]; then ok "el binario existe y es ejecutable ($BIN)"
    else no "el binario existe" "no encontrado o sin permiso: $BIN"; fi
}
t_ayuda() {
    local out; out="$(run --help)"
    has "help: imprime la sintaxis" "$out" "Syntax:"
    has "help: lista las opciones" "$out" "--problem_file"
}
t_sin_argumentos() {
    local out; out="$(run)"
    has "sin argumentos: error de dominio" "$out" "Undefined domain file"
}

# --------------------------------------------------------------------------
# 4-5  el parser acepta los dominios validos
# --------------------------------------------------------------------------
t_parse_blocks() {
    local out; out="$(run -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    lack "blocks: parsea sin errores" "$out" "error:"
}
t_parse_move() {
    local out; out="$(run -d "$FIX/move.hpdl" -p "$FIX/move-problem.hpdl")"
    lack "move: parsea sin errores" "$out" "error:"
}

# --------------------------------------------------------------------------
# 6-8  planificacion: el plan coincide con el esperado (regresion)
# --------------------------------------------------------------------------
t_plan_blocks() {
    local got; got="$(plan -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    eq "blocks: plan esperado" "$got" "$(cat "$EXP/blocks.plan")"
}
t_plan_move() {
    local got; got="$(plan -d "$FIX/move.hpdl" -p "$FIX/move-problem.hpdl")"
    eq "move: plan esperado" "$got" "$(cat "$EXP/move.plan")"
}
t_plan_bloques() {
    local out; out="$(run -d "$ROOT/examples/bloques.hpdl" -p "$ROOT/examples/bloques-problem.hpdl")"
    if case "$out" in *"without Python support"*) true;; *) false;; esac; then
        skip "bloques: plan esperado (necesita Python embebido)" "compilado sin python3-dev"
        return
    fi
    eq "bloques: plan esperado" "$(printf '%s\n' "$out" | grep -E '^:action ')" "$(cat "$EXP/bloques.plan")"
}

# --------------------------------------------------------------------------
# 9  determinismo con semilla fija
# --------------------------------------------------------------------------
t_determinismo() {
    local a b
    a="$(plan -s 7 -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    b="$(plan -s 7 -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    eq "misma semilla -> mismo plan" "$a" "$b"
}

# --------------------------------------------------------------------------
# 10-12  entradas invalidas: se rechazan y no se produce plan
# --------------------------------------------------------------------------
t_rechaza_goal_plano() {
    local out; out="$(run -d "$ROOT/examples/blocks.hpdl" -p "$FIX/flat-goal-problem.hpdl")"
    has  "goal plano: se avisa" "$out" "planos"
    lack "goal plano: no se genera plan" "$out" ":action "
}
t_rechaza_sintaxis() {
    local out; out="$(run -d "$FIX/broken.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    has  "sintaxis: error detectado" "$out" "syntax error"
    has  "sintaxis: se contabiliza el error" "$out" "1 errors"
    lack "sintaxis: no se genera plan" "$out" ":action "
}
t_rechaza_dominio_incorrecto() {
    local out; out="$(run -d "$ROOT/examples/blocks.hpdl" -p "$FIX/mismatch-problem.hpdl")"
    has  "dominio incorrecto: se avisa" "$out" "The problem requires the domain"
    lack "dominio incorrecto: no se genera plan" "$out" ":action "
}

# --------------------------------------------------------------------------
# 13-15  formatos de salida
# --------------------------------------------------------------------------
t_salida_texto() {
    run -o "$TMP/plan.txt" -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl" >/dev/null
    if [ ! -f "$TMP/plan.txt" ]; then no "salida -o: se crea el fichero" "no existe $TMP/plan.txt"; return; fi
    local got; got="$(grep -E '^:action ' "$TMP/plan.txt" || true)"
    eq "salida -o: mismo plan que por pantalla" "$got" "$(cat "$EXP/blocks.plan")"
}
t_salida_xml() {
    run -x "$TMP/plan.xml" -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl" >/dev/null
    if [ ! -f "$TMP/plan.xml" ]; then no "salida -x: se crea el fichero" "no existe $TMP/plan.xml"; return; fi
    local out; out="$(cat "$TMP/plan.xml")"
    has "salida -x: es XML" "$out" "<plan "
    has "salida -x: refleja las 2 acciones del plan" "$out" 'primitives="2"'
}
t_arbol() {
    local out; out="$(run -t -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl")"
    has "arbol -t: cabecera Root" "$out" "Root:"
    has "arbol -t: separador para format_output.py" "$out" "###"
}

# --------------------------------------------------------------------------
# 16  tools/format_output.py
# --------------------------------------------------------------------------
t_format_output() {
    if ! command -v python3 >/dev/null 2>&1; then
        skip "format_output.py" "no hay python3"; return
    fi
    run -t -d "$ROOT/examples/blocks.hpdl" -p "$ROOT/examples/blocks-problem.hpdl" > "$TMP/tree.txt"
    local got; got="$(python3 "$ROOT/tools/format_output.py" "$TMP/tree.txt" 2>&1 || true)"
    eq "format_output.py: arbol en formato pandaPIparser" "$got" "$(cat "$EXP/format_output.blocks")"
}

# --------------------------------------------------------------------------
# 17-21  invariantes estructurales (protegen el refactor y la limpieza)
# --------------------------------------------------------------------------
t_includes_resueltos() {
    local bad=""
    while IFS= read -r inc; do
        [ -f "$ROOT/include/$inc" ] || bad="$bad $inc"
    done < <(grep -rhoE '#include "hpdl/[^"]+"' "$ROOT/src" "$ROOT/include" "$ROOT/yacc" 2>/dev/null \
             | sed 's/#include "//; s/"$//' | sort -u)
    if [ -z "$bad" ]; then ok "todos los #include \"hpdl/...\" resuelven"
    else no "todos los #include \"hpdl/...\" resuelven" "huerfanos:$bad"; fi
}
t_gramatica_sincronizada() {
    local stamp hp hl
    stamp="$(cat "$ROOT/generated/grammar.sha256" 2>/dev/null | tr -d '\r\n ')"
    hp="$(sha256sum "$ROOT/yacc/parser.yy" | cut -d' ' -f1)"
    hl="$(sha256sum "$ROOT/yacc/lexer.ll"  | cut -d' ' -f1)"
    eq "generated/ corresponde a la gramatica" "$stamp" "$hp$hl"
}
t_sin_python2() {
    local hits
    hits="$(grep -rlE 'python2\.7|PyString_|PyInt_|Py_InitModule|PyObject_HEAD_INIT' \
            "$ROOT/src" "$ROOT/include" "$ROOT/yacc" 2>/dev/null | sed "s|$ROOT/||" | tr '\n' ' ')"
    eq "sin restos de la API de Python 2" "$hits" ""
}
t_layout() {
    local missing="" d
    for d in common lang lang/goals lang/effects htn domain planner constraints unify undo parser py debug; do
        [ -d "$ROOT/include/hpdl/$d" ] || missing="$missing include/hpdl/$d"
        [ -d "$ROOT/src/$d" ]          || missing="$missing src/$d"
    done
    if [ -z "$missing" ]; then ok "los 13 subsistemas existen en include/ y src/"
    else no "los 13 subsistemas existen en include/ y src/" "faltan:$missing"; fi
}
t_sin_flex_bison_en_cmake() {
    if grep -qE 'find_package\(\s*(FLEX|BISON)' "$ROOT/CMakeLists.txt"; then
        no "el build no exige flex ni bison" "CMakeLists.txt los busca"
    else ok "el build no exige flex ni bison (usa generated/)"; fi
}

# --------------------------------------------------------------------------
# 22  el parser versionado es reproducible con flex+bison
# --------------------------------------------------------------------------
t_parser_reproducible() {
    if ! command -v flex >/dev/null 2>&1 || ! command -v bison >/dev/null 2>&1; then
        skip "generated/ reproducible con flex+bison" "no hay flex/bison"; return
    fi
    # Se regenera en una copia con las MISMAS rutas relativas que usa
    # tools/regenerate_parser.sh: bison/flex graban la ruta de salida en las
    # directivas #line, asi que comparar contra otra ruta daria falsos fallos.
    mkdir -p "$TMP/repo/generated"
    cp -r "$ROOT/yacc" "$TMP/repo/"
    ( cd "$TMP/repo" \
      && bison -o generated/parser.cpp --defines=generated/parser.hh yacc/parser.yy 2>/dev/null \
      && flex  -o generated/lexer.cpp yacc/lexer.ll 2>/dev/null ) \
      || { no "generated/ reproducible con flex+bison" "fallo al regenerar"; return; }
    local bad="" f
    for f in parser.cpp parser.hh lexer.cpp; do
        diff -q "$TMP/repo/generated/$f" "$ROOT/generated/$f" >/dev/null || bad="$bad $f"
    done
    if [ -z "$bad" ]; then ok "generated/ es byte a byte lo que produce flex+bison"
    else no "generated/ es byte a byte lo que produce flex+bison" "difieren:$bad"; fi
}

# --------------------------------------------------------------------------
TESTS="binario_existe ayuda sin_argumentos parse_blocks parse_move plan_blocks plan_move
plan_bloques determinismo rechaza_goal_plano rechaza_sintaxis rechaza_dominio_incorrecto
salida_texto salida_xml arbol format_output includes_resueltos gramatica_sincronizada
sin_python2 layout sin_flex_bison_en_cmake parser_reproducible"

if [ "$ONLY" = "all" ]; then
    echo "== HPDL-Planner: bateria de tests =="
    echo "   binario: $BIN"
    for t in $TESTS; do "t_$t"; done
    echo
    echo "== resultados: $PASS ok, $FAIL fallos, $SKIP omitidos =="
    [ "$FAIL" -eq 0 ] || exit 1
    [ "$SKIP" -gt 0 ] && [ "$PASS" -eq 0 ] && exit 77
    exit 0
else
    if ! echo "$TESTS" | grep -qw "$ONLY"; then
        echo "test desconocido: $ONLY"; exit 2
    fi
    "t_$ONLY"
    [ "$FAIL" -eq 0 ] || exit 1
    [ "$SKIP" -gt 0 ] && [ "$PASS" -eq 0 ] && exit 77
    exit 0
fi
