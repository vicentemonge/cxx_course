# 11 — Strings, formato, tiempo y E/S

`std::format` [20] y `std::print` [23] con seguridad de tipos; `<charconv>` [17] rápido y sin locale; `<chrono>` para que las unidades de tiempo sean tipos.

**Temas core:** `@type-design` `@performance` `@safety` `@generic` `@abi`

**Firmware:** 🟢 `@emb:ok` ×2 · 🟡 `@emb:cond` ×2 · 🔴 `@emb:no` ×2

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Formato
    1. `format`, `format_to_n` [20], especificadores, comprobación en compilación · `@type-design` `@safety` 🟡 `@emb:cond` _coste en flash; `format_to_n` evita heap_
    2. `std::formatter` propio · `@generic`
    3. `print` [23], formato de rangos [23] · `@type-design` 🔴 `@emb:no` _depende de stdio_
2. `to_chars`/`from_chars` [17], constexpr [23] · `@performance` 🟢 `@emb:ok`
3. Strings: SSO, `starts_with` [20], `contains` [23], `resize_and_overwrite` [23], literales · `@performance` 🟡 `@emb:cond` _heap fuera del SSO_
4. Texto y Unicode: `char8_t` [20], UTF-8 como codificación por defecto, por qué evitar `std::regex` · `@type-design` `@performance`
5. `<chrono>`: duraciones, relojes [11], literales [14], calendario y zonas [20] · `@type-design` 🟢 `@emb:ok` _duraciones y relojes propios; zonas horarias no_
6. Linux: `filesystem` [17], `spanstream` [23], iostreams frente a format · `@abi` 🔴 `@emb:no`

## Ejercicio

Implementar un logger con `format_to_n` sobre un buffer estático, un formatter para un struct de telemetría y un reloj `chrono` propio sobre SysTick.

## Preguntas de control (nivel entrevista)

1. ¿Por qué `std::format` es más seguro que `printf`? ¿Y más rápido que iostreams?
2. ¿Qué ventajas tiene `from_chars` frente a `strtol` o `std::stoi`?
3. Diseña un reloj `chrono` compatible sobre un contador de hardware de 32 bits con wrap-around.
4. ¿Por qué se desaconseja `std::regex` en código de producción?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`charconv.cpp`](examples/lang/charconv.cpp), [`chrono_basico.cpp`](examples/lang/chrono_basico.cpp), [`format_basico.cpp`](examples/lang/format_basico.cpp), [`print.cpp`](examples/lang/print.cpp), [`strings.cpp`](examples/lang/strings.cpp)
- **Firmware (`examples/embedded/`):** [`static_logger.cpp`](examples/embedded/static_logger.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@type-design` `@performance` `@safety` `@generic`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@safety` `@generic` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@type-design` `@performance` `@safety` `@abi`
- [08 — Clases y novedades del lenguaje](../08-clases-lenguaje) · `@type-design` `@performance` `@generic`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@type-design` `@performance` `@safety`
- [03 — Templates modernos y concepts](../03-templates-concepts) · `@type-design` `@performance` `@generic` `@abi`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/11-format-chrono-io.md`](../../docs/notas/11-format-chrono-io.md)
