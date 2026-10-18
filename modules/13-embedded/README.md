# 13 — C++ moderno en embedded

Aplicación de todo lo anterior a targets sin heap, sin excepciones y sin RTTI.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Entorno: *freestanding* [23/26], `-fno-exceptions`/`-fno-rtti`/`-fno-threadsafe-statics`, newlib-nano, `.init_array`
2. Memoria sin heap: `std::pmr` [17], allocators y pools, `launder` [17], `construct_at` [20], `start_lifetime_as` [23], ETL, `inplace_vector` [26]
3. Bits y registros: `<bit>` [20], `byteswap` [23], MMIO tipado, bitfields vs máscaras, strict aliasing y `bit_cast`
4. Tamaño y rendimiento: `size`, `.map`, Bloaty, coste de abstracciones, LTO y `--gc-sections`
5. Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines

## Ejercicio

Construir una capa de acceso a registros tipada y `constexpr` para un periférico de STM32 y verificar que el binario es idéntico al de la versión con macros CMSIS.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/13-embedded.md`](../../docs/notas/13-embedded.md)

## Ejemplo inicial

`examples/register_field.hpp`, `examples/register_field.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
