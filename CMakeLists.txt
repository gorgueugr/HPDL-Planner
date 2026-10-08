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

# --- Interprete Python embebido (opcional) ----------------------------------
# AUTO: se activa solo si estan las cabeceras de desarrollo de Python 3.
set(HPDL_PYTHON "AUTO" CACHE STRING "Soporte Python embebido: AUTO | ON | OFF")
set_property(CACHE HPDL_PYTHON PROPERTY STRINGS AUTO ON OFF)

set(HAVE_PYTHON FALSE)
if(HPDL_PYTHON STREQUAL "ON")
  find_package(Python3 REQUIRED COMPONENTS Development)
  set(HAVE_PYTHON TRUE)
elseif(HPDL_PYTHON STREQUAL "AUTO")
  find_package(Python3 COMPONENTS Development QUIET)
  if(Python3_Development_FOUND)
    set(HAVE_PYTHON TRUE)
  endif()
endif()

# pythonWrapper.cpp incluye a pyAPI/pyLiteral/pyUTable/pyTerm (una sola unidad de
# traduccion), asi que esos cuatro no deben compilarse por separado: darian
# definiciones duplicadas al enlazar.
list(REMOVE_ITEM SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyAPI.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyLiteral.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyTerm.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyUTable.cpp")

if(NOT HAVE_PYTHON)
  list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pythonWrapper.cpp")
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

if(HAVE_PYTHON)
  target_compile_definitions(planner PRIVATE PYTHON_FOUND=1)
  target_link_libraries(planner PRIVATE Python3::Python)
  message(STATUS "Python embebido: ACTIVADO (Python ${Python3_VERSION})")
else()
  message(STATUS "Python embebido: desactivado (examples/bloques.hpdl no funcionara; "
                 "instala python3-dev y reconfigura, o usa -DHPDL_PYTHON=ON)")
endif()

install(TARGETS planner RUNTIME DESTINATION bin)
