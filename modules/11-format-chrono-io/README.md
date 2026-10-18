# 11 — Strings, formato, tiempo y E/S

`std::format` [20] y `std::print` [23] con seguridad de tipos; `<charconv>` [17] sin locale ni heap.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Formato: `format`, `format_to_n` [20], especificadores, `std::formatter` propio, comprobación en compilación, `print` [23], formato de ranges [23], coste en flash
2. Conversiones: `to_chars`/`from_chars` [17], `constexpr` [23]
3. Strings: SSO, `starts_with` [20], `contains` [23], `resize_and_overwrite` [23], literales `s`/`sv`
4. `<chrono>`: duraciones y relojes [11], literales [14], calendario y zonas [20], relojes sobre SysTick
5. Linux: `std::filesystem` [17], `std::spanstream` [23]

## Ejercicio

Implementar un logger con `format_to_n` sobre un buffer estático, un formatter para un struct de telemetría y un reloj `chrono` propio sobre SysTick.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/11-format-chrono-io.md`](../../docs/notas/11-format-chrono-io.md)

## Ejemplo inicial

`examples/static_logger.hpp`, `examples/static_logger.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
