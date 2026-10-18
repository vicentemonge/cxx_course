cmake_minimum_required(VERSION 3.25)
project(cxx_course LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23 CACHE STRING "Estándar C++")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(COURSE_BUILD_TESTS "Compilar tests (solo host)" ON)
option(COURSE_ENABLE_CLANG_TIDY "Ejecutar clang-tidy al compilar" OFF)
option(COURSE_BUILD_FUZZERS "Compilar fuzzers libFuzzer (requiere Clang)" OFF)

include(cmake/warnings.cmake)
include(cmake/course.cmake)

if(COURSE_ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

if(COURSE_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(doctest)
  enable_testing()
endif()

add_subdirectory(common)

# Un subdirectorio por módulo. 12 (módulos C++20) y 14 (C++26) dependen
# del soporte del compilador: se activan a mano cuando el toolchain lo permita.
set(COURSE_MODULES
  01-fundamentos
  02-compile-time
  03-templates-concepts
  04-tipos-vocabulario
  05-gestion-errores
  06-lambdas
  07-ranges
  08-clases-lenguaje
  09-concurrencia
  10-coroutines
  11-format-chrono-io
  13-embedded
  15-ub-seguridad
  16-diseno-apis
  17-rendimiento
  18-calidad
)
foreach(m IN LISTS COURSE_MODULES)
  add_subdirectory(modules/${m})
endforeach()

add_subdirectory(entrevistas)

if(COURSE_BUILD_FUZZERS)
  add_subdirectory(fuzz)
endif()
