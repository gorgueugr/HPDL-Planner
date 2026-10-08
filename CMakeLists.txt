cmake_minimum_required(VERSION 3.16)
project(hpdl_planner LANGUAGES CXX)

# ---------------------------------------------------------------------------
# HPDL-Planner -- build minimo y actualizado.
#   Requisitos: cmake >= 3.16, flex, libfl-dev, bison, g++/clang++.
#   Sin Python 2.7 ni readline.
#
#   cmake -S . -B build
#   cmake --build build -j
#   ./build/planner --help
#
# Estructura: include/hpdl/<subsistema>/ y src/<subsistema>/ (ver README).
# ---------------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)          # C++17 rompe por ambiguedad de std::data (check.cpp)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(HPDL_ENABLE_PYTHON "Soporte Python 2.7 embebido (legacy, desactivado)" OFF)

# --- Generadores de parser/lexer -------------------------------------------
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(parser "${CMAKE_CURRENT_SOURCE_DIR}/yacc/parser.yy"
             "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp"
             DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/parser.hh")
FLEX_TARGET(lexer "${CMAKE_CURRENT_SOURCE_DIR}/yacc/lexer.ll"
            "${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp")
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

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

if(NOT HPDL_ENABLE_PYTHON)
  # Estos ficheros solo tienen sentido con el interprete Python 2.7 embebido.
  list(REMOVE_ITEM SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyAPI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyLiteral.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyTerm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pyUTable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/py/pythonWrapper.cpp")
endif()

add_executable(planner
  ${BISON_parser_OUTPUTS}
  ${FLEX_lexer_OUTPUTS}
  ${SOURCES})

target_include_directories(planner PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"     # -> #include "hpdl/<subsistema>/..."
  "${CMAKE_CURRENT_BINARY_DIR}"             # -> parser.hh / lexer.cpp generados
  ${FLEX_INCLUDE_DIRS})

# Red de propagacion de restricciones temporales usada por el planificador.
target_compile_definitions(planner PRIVATE USE_AC3)

if(HPDL_ENABLE_PYTHON)
  find_package(Python2 REQUIRED COMPONENTS Development)
  target_compile_definitions(planner PRIVATE PYTHON_FOUND)
  target_link_libraries(planner PRIVATE Python2::Python)
endif()

install(TARGETS planner RUNTIME DESTINATION bin)
