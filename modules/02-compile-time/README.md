# 02 — Programación en tiempo de compilación

Tablas, CRC, configuraciones y validaciones calculadas sin coste en runtime.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. `constexpr` y su evolución
    1. Una sola expresión [11]
    2. Relajado: bucles, variables locales [14]
    3. Lambdas `constexpr` [17]
    4. `try`/`catch`, `virtual`, `union`, asignación transitoria [20]
    5. `std::vector` y `std::string` `constexpr` [20]
    6. Variables `static` y tipos no literales [23]
    7. Algoritmos `constexpr` [20], `<cmath>` `constexpr` [23/26]
2. `if constexpr` [17]
    1. Sustituto de *tag dispatching* y SFINAE
    2. Ramas descartadas e instanciación
3. Funciones inmediatas
    1. `consteval` [20], propagación [23]
    2. `if consteval` [23] vs `std::is_constant_evaluated()` [20]
    3. `constinit` [20] y el *static initialization order fiasco*
4. Variables y templates
    1. Variable templates [14]
    2. Variables `inline` [17]
    3. NTTP con `auto` [17]
    4. NTTP de clase y coma flotante [20]
5. Utilidades
    1. `std::bit_cast` [20]
    2. `std::index_sequence` [14]

## Ejercicio

Generar en compilación una tabla CRC-32 o una LUT de calibración con `consteval`, colocarla en flash con `constinit`/`const` y verificar en el `.map` que no ocupa RAM.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/02-compile-time.md`](../../docs/notas/02-compile-time.md)

## Ejemplo inicial

`examples/crc32.hpp`, `examples/crc32.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
