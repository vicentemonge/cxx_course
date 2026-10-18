# cxx_course — C++ moderno (C++11 → C++26) orientado a embedded

Repositorio de trabajo para el plan de estudio de C++ moderno. Cada módulo tiene su
temario, ejemplos ejecutables, tests y un ejercicio orientado a firmware.

## Estructura

```
cmake/            toolchain ARM, warnings y helper course_module()
common/           utilidades compartidas (banco de registros simulado)
docs/notas/       notas personales por módulo
modules/NN-tema/
  README.md       temario y enunciado del ejercicio
  examples/       un ejecutable por fichero .cpp
  exercise/       solución del ejercicio
  tests/          tests doctest del módulo
```

## Compilar

```bash
cmake --preset host-gcc          # o host-clang, host-sanitizers
cmake --build --preset host-gcc
ctest --preset host-gcc

cmake --preset arm-cortex-m4     # requiere arm-none-eabi-gcc
cmake --build --preset arm-cortex-m4
```

Requisitos: CMake ≥ 3.25, Ninja, GCC ≥ 13 o Clang ≥ 17. Algunos ejemplos de C++23
(`std::print`, `std::generator`) necesitan GCC 14.

## Módulos

| # | Tema | Estado |
|---|------|--------|
| 01 | [Fundamentos del C++ moderno](modules/01-fundamentos) | ⬜ |
| 02 | [Programación en tiempo de compilación](modules/02-compile-time) | ⬜ |
| 03 | [Templates modernos y concepts](modules/03-templates-concepts) | ⬜ |
| 04 | [Tipos vocabulario](modules/04-tipos-vocabulario) | ⬜ |
| 05 | [Gestión de errores](modules/05-gestion-errores) | ⬜ |
| 06 | [Lambdas y estilo funcional](modules/06-lambdas) | ⬜ |
| 07 | [Ranges, views y algoritmos](modules/07-ranges) | ⬜ |
| 08 | [Clases y novedades del lenguaje](modules/08-clases-lenguaje) | ⬜ |
| 09 | [Concurrencia y modelo de memoria](modules/09-concurrencia) | ⬜ |
| 10 | [Coroutines](modules/10-coroutines) | ⬜ |
| 11 | [Strings, formato, tiempo y E/S](modules/11-format-chrono-io) | ⬜ |
| 12 | [Módulos y organización del código](modules/12-modulos) | ⬜ |
| 13 | [C++ moderno en embedded](modules/13-embedded) | ⬜ |
| 14 | [C++26](modules/14-cpp26) | ⬜ |

Orden recomendado: 01 → 02 → 03 → 04 → 05 → 08 → 06 → 07 → 13 → 09 → 11 → 10 → 12 → 14.

## Método

1. Leer el temario del módulo y estudiar cada punto (cppreference + referencias).
2. Escribir ejemplos mínimos en `examples/` y comprobarlos en Compiler Explorer
   con `arm-none-eabi-gcc -Os`, comparando con la versión C++03.
3. Resolver el ejercicio en `exercise/` con tests en `tests/`.
4. Anotar conclusiones en `docs/notas/NN-tema.md`.
