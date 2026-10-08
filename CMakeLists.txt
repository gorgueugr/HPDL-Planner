cmake_minimum_required(VERSION 3.16)
project(hpdl_planner LANGUAGES CXX)

# ---------------------------------------------------------------------------
# HPDL-Planner -- build minimo.
#
#   Requisitos: cmake >= 3.16 + un compilador de C++ (g++ / clang++).
#   NO hacen falta flex, bison ni libfl-dev: parser.cpp/lexer.cpp van ya
#   generados en generated/, y FlexLexer.h esta en third_party/flex/.
#
#     cmake -S . -B build
#     cmake --build build -j
#     ./build/planner --help
#
#   Solo si modificas la gramatica (yacc/parser.yy o yacc/lexer.ll) hay que
#   regenerar generated/ con flex+bison:
#     tools/regenerate_parser.sh
# ---------------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)          # C++17 rompe por ambiguedad de std::data (check.cpp)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")

# --- Comprobar que generated/ corresponde a la gramatica actual -------------
# (si no, se compilaria un parser que no refleja yacc/*.yy|.ll)
file(SHA256 "${CMAKE_CURRENT_SOURCE_DIR}/yacc/parser.yy" _hp)
file(SHA256 "${CMAKE_CURRENT_SOURCE_DIR}/yacc/lexer.ll"  _hl)
file(READ "${GENERATED_DIR}/grammar.sha256" _stamp)
string(STRIP "${_stamp}" _stamp)
if(NOT _stamp STREQUAL "${_hp} ${_hl}")
  message(FATAL_ERROR
    "La gramatica (yacc/) ha cambiado pero generated/ esta obsoleto.\n"
    "Regenera con:  tools/regenerate_parser.sh   (requiere flex y bison)")
endif()

# --- Fuentes ----------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Variantes alternativas de propagacion temporal: solo se usa la de AC3
# (USE_AC3, mas abajo). Las PC2/PC2-CL no se compilan nunca.
list(REMOVE_ITEM SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/constraints/tcnm-pc2.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/constraints/tcnm-pc2-cl.cpp"
  # restos de flex/bison generados dentro del arbol de fuentes
  "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp")

# El interprete Python 2.7 embebido es legacy y esta desactivado por defecto.
option(HPDL_ENABLE_PYTHON "Compilar el interprete Python 2.7 embebido (legacy)" OFF)

if(NOT HPDL_ENABLE_PYTHON)
  list(REMOVE_ITEM SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyAPI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyLiteral.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyTerm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyUTable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pythonWrapper.cpp")
endif()

add_executable(planner
  "${GENERATED_DIR}/parser.cpp"
  "${GENERATED_DIR}/lexer.cpp"
  ${SOURCES})

target_include_directories(planner PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"          # -> #include "hpdl/<subsistema>/..."
  "${GENERATED_DIR}"                             # -> parser.hh
  "${CMAKE_CURRENT_SOURCE_DIR}/third_party/flex" # -> FlexLexer.h
  )

# Red de propagacion de restricciones temporales usada por el planificador.
target_compile_definitions(planner PRIVATE USE_AC3)

if(HPDL_ENABLE_PYTHON)
  find_package(Python2 REQUIRED COMPONENTS Development)
  target_compile_definitions(planner PRIVATE PYTHON_FOUND)
  target_link_libraries(planner PRIVATE Python2::Python)
endif()

install(TARGETS planner RUNTIME DESTINATION bin)
