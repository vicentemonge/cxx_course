# cxx_course — C++ moderno (C++11 → C++26)

Curso para llevar a un ingeniero con experiencia en C++ clásico al nivel que exigen los equipos
de sistemas de empresas como Mozilla, Meta o DuckDuckGo, con atención específica a firmware embebido.

Cada módulo incluye temario etiquetado, ejemplos ejecutables de lenguaje y de firmware, tests,
un ejercicio práctico y preguntas de control de nivel entrevista.

## Perfil objetivo

Al terminar el curso se espera poder:

- Razonar sobre tiempo de vida, propiedad y comportamiento indefinido en cualquier fragmento de código.
- Diseñar APIs genéricas con concepts, tipos vocabulario y una política de errores coherente.
- Escribir código concurrente correcto y justificar cada orden de memoria.
- Medir y optimizar con datos, y explicar el coste de cada abstracción.
- Trabajar con la cadena de calidad completa: CMake moderno, tests, sanitizers, fuzzing y análisis estático.
- Decidir qué partes del lenguaje y de la biblioteca estándar usar en un microcontrolador y por qué.

## Módulos

<!-- modules:start -->
| # | Módulo | Temas core principales | 🟢 | 🟡 | 🔴 |
|---|---|---|---|---|---|
| 01 | [Fundamentos del C++ moderno](modules/01-fundamentos) | `@type-design` `@value-sem` `@lifetime` `@generic` | 10 | 1 |  |
| 02 | [Programación en tiempo de compilación](modules/02-compile-time) | `@compile-time` `@generic` `@safety` `@lifetime` | 8 |  |  |
| 03 | [Templates modernos y concepts](modules/03-templates-concepts) | `@generic` `@compile-time` `@type-design` `@performance` | 2 | 1 |  |
| 04 | [Tipos vocabulario](modules/04-tipos-vocabulario) | `@type-design` `@performance` `@lifetime` `@safety` | 9 | 1 | 1 |
| 05 | [Gestión de errores](modules/05-gestion-errores) | `@errors` `@lifetime` `@type-design` `@performance` | 5 | 2 | 1 |
| 06 | [Lambdas y estilo funcional](modules/06-lambdas) | `@functional` `@lifetime` `@generic` `@interop` | 3 | 2 |  |
| 07 | [Ranges, views y algoritmos](modules/07-ranges) | `@iteration` `@generic` `@lifetime` `@safety` | 4 | 1 | 1 |
| 08 | [Clases y novedades del lenguaje](modules/08-clases-lenguaje) | `@type-design` `@performance` `@lifetime` `@generic` | 8 | 1 |  |
| 09 | [Concurrencia y modelo de memoria](modules/09-concurrencia) | `@concurrency` `@memory-model` `@safety` `@performance` | 3 | 2 | 2 |
| 10 | [Coroutines](modules/10-coroutines) | `@async` `@lifetime` `@safety` `@iteration` | 1 | 1 |  |
| 11 | [Strings, formato, tiempo y E/S](modules/11-format-chrono-io) | `@type-design` `@performance` `@safety` `@generic` | 2 | 2 | 2 |
| 12 | [Módulos, enlace y organización del código](modules/12-modulos) | `@abi` `@tooling` `@safety` | 1 | 1 |  |
| 13 | [C++ moderno en embedded](modules/13-embedded) | `@lifetime` `@safety` `@performance` `@type-design` | 13 | 1 |  |
| 14 | [C++26](modules/14-cpp26) | `@safety` `@compile-time` `@generic` `@concurrency` | 3 | 1 |  |
| 15 | [Modelo de objetos, comportamiento indefinido y seguridad de memoria](modules/15-ub-seguridad) 🆕 | `@safety` `@lifetime` `@performance` `@interop` | 3 | 2 |  |
| 16 | [Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](modules/16-diseno-apis) 🆕 | `@type-design` `@abi` `@interop` `@value-sem` | 4 | 3 |  |
| 17 | [Rendimiento y diseño orientado a datos](modules/17-rendimiento) 🆕 | `@performance` `@tooling` `@type-design` `@lifetime` | 4 | 3 |  |
| 18 | [Calidad: testing, sanitizers, fuzzing, análisis estático y build](modules/18-calidad) 🆕 | `@tooling` `@safety` `@abi` `@generic` | 6 |  |  |

Orden recomendado: 01 → 15 → 18 → 02 → 03 → 04 → 05 → 08 → 06 → 07 → 16 → 09 → 17 → 13 → 11 → 10 → 12 → 14
<!-- modules:end -->

Columnas 🟢/🟡/🔴: número de puntos del temario marcados como aporte, condicional o descarte en firmware.

## Tags

Cada punto del temario lleva tags que permiten seguir un tema a través del curso:

- **Core** (`@lifetime`, `@value-sem`, `@generic`, `@safety`…): hilos conductores entre módulos.
  Cada README de módulo lista sus conexiones con otros módulos según los tags compartidos.
- **Firmware**: 🟢 `@emb:ok` aporte · 🟡 `@emb:cond` condicional · 🔴 `@emb:no` descarte en bare-metal.

Índice completo, matriz módulo × tema y búsqueda por tag en [`docs/TAGS.md`](docs/TAGS.md).
Glosario de términos en [`docs/GLOSARIO.md`](docs/GLOSARIO.md).

## Entrevistas simuladas

- [Senior C++ Engineer — Firefox Platform (Mozilla, ficticia)](entrevistas/mozilla-senior-cpp):
  siete rondas (screening, coding, code review con código hostil, concurrencia, diseño de sistema,
  rendimiento/embedded y liderazgo), con solucionario, rúbrica y soluciones compiladas y testeadas.

## Estructura

```
cmake/              toolchain ARM, warnings y helper course_module()
common/             utilidades compartidas (banco de registros simulado)
docs/               TAGS.md (generado), GLOSARIO.md, notas/ por módulo
tools/              course_data.py (temario, fuente única) y gen_docs.py
modules/NN-tema/
  README.md         generado: temario, ejercicio, preguntas, conexiones
  examples/lang/    ejemplos de conocimiento del lenguaje
  examples/embedded/ ejemplos orientados a firmware
  exercise/         solución del ejercicio
  tests/            tests doctest del módulo
entrevistas/        entrevistas simuladas con solucionario y soluciones testeadas
fuzz/               fuzzers libFuzzer (opcional, Clang)
```

## Compilar

```bash
cmake --preset host-gcc          # o host-clang, host-sanitizers
cmake --build --preset host-gcc
ctest --preset host-gcc          # ejecuta ejemplos y tests

cmake --preset arm-cortex-m4     # requiere arm-none-eabi-gcc
cmake --build --preset arm-cortex-m4
```

Requisitos: CMake ≥ 3.25, Ninja, GCC ≥ 13 o Clang ≥ 19. Algunos ejemplos de C++23
(`std::print`, `std::generator`, deducing this) se activan solo si el compilador los soporta.

## Editar el temario

El temario vive en `tools/course_data.py`. Tras modificarlo:

```bash
python3 tools/gen_docs.py
```

regenera los README de los módulos, `docs/TAGS.md` y la tabla de este README.

## Método

1. Leer el temario del módulo y estudiar cada punto (cppreference + referencias).
2. Ejecutar y modificar los ejemplos de `examples/lang/` y `examples/embedded/`.
3. Comparar en Compiler Explorer con `arm-none-eabi-gcc -Os` los puntos marcados `@emb:*`.
4. Resolver el ejercicio con tests y responder las preguntas de control.
5. Anotar conclusiones en `docs/notas/`.
