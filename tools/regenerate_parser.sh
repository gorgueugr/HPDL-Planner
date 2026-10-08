#!/usr/bin/env bash
# Regenera generated/{parser.cpp,parser.hh,lexer.cpp} a partir de la gramatica.
# Solo hace falta ejecutarlo si modificas yacc/parser.yy o yacc/lexer.ll.
# Requiere: flex y bison  (sudo apt-get install -y flex bison)
set -euo pipefail
cd "$(dirname "$0")/.."

bison -o generated/parser.cpp --defines=generated/parser.hh yacc/parser.yy
flex  -o generated/lexer.cpp yacc/lexer.ll
rm -f generated/parser.output

# huella de la gramatica: el build la compara para detectar generated/ obsoleto
python3 - <<'PY'
import hashlib
h = lambda p: hashlib.sha256(open(p,"rb").read()).hexdigest()
open("generated/grammar.sha256","w").write(f"{h('yacc/parser.yy')} {h('yacc/lexer.ll')}\n")
PY

echo "generated/ actualizado."
