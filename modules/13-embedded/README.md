# 13 — C++ moderno en embedded

Módulo transversal: aplica todo lo anterior a targets sin heap, sin excepciones y sin RTTI, con acceso directo a hardware. Recoge los descartes y aportes marcados con `@emb:*` en el resto del curso.

**Temas core:** `@lifetime` `@safety` `@performance` `@type-design` `@tooling` `@abi` `@errors` `@compile-time` `@memory-model`

**Firmware:** 🟢 `@emb:ok` ×13 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Entorno
    1. *Freestanding* y su ampliación [23/26] · `@abi` 🟢 `@emb:ok`
    2. `-fno-exceptions`, `-fno-rtti`, `-fno-threadsafe-statics`: qué deja de funcionar · `@errors` 🟢 `@emb:ok`
    3. newlib/newlib-nano, partes de la STL que arrastran heap o locale · `@performance` 🟡 `@emb:cond`
    4. Arranque: `.init_array`, constructores globales, `constinit` · `@lifetime` 🟢 `@emb:ok`
2. Memoria sin heap
    1. `std::pmr` [17] sobre buffers estáticos · `@lifetime` `@performance` 🟢 `@emb:ok`
    2. Allocators y pools propios · `@lifetime` 🟢 `@emb:ok`
    3. *Placement new*, `launder` [17], `construct_at` [20], `start_lifetime_as` [23] · `@lifetime` `@safety` 🟢 `@emb:ok`
    4. ETL, `inplace_vector` [26] · `@type-design` 🟢 `@emb:ok`
3. Bits y registros
    1. `<bit>` [20], `byteswap` [23] · `@compile-time` 🟢 `@emb:ok`
    2. MMIO tipado: `volatile` + templates + máscaras `constexpr` · `@type-design` `@memory-model` 🟢 `@emb:ok`
    3. Bitfields frente a máscaras, *strict aliasing* y `bit_cast` · `@safety` 🟢 `@emb:ok`
4. Tamaño y rendimiento: `size`, `.map`, Bloaty, LTO, `--gc-sections`, coste de templates y virtual · `@performance` `@tooling` 🟢 `@emb:ok`
5. Aritmética: punto fijo, enteros de ancho fijo, promociones y overflow · `@type-design` `@safety` 🟢 `@emb:ok`
6. Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines · `@safety` `@tooling` 🟢 `@emb:ok`

## Ejercicio

Construir una capa de acceso a registros tipada y `constexpr` para un periférico de STM32 y verificar que el binario es idéntico al de la versión con macros CMSIS.

## Preguntas de control (nivel entrevista)

1. ¿Qué partes de la biblioteca estándar usarías en bare-metal sin heap ni excepciones?
2. ¿Por qué reinterpretar un buffer de bytes como struct puede ser UB y cómo lo harías bien?
3. ¿Qué cuesta en flash una función virtual? ¿Y una plantilla instanciada 10 veces?
4. ¿Cómo garantizas que un objeto global no ejecuta código antes de `main`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`bit.cpp`](examples/lang/bit.cpp), [`pmr.cpp`](examples/lang/pmr.cpp), [`tiempo_de_vida.cpp`](examples/lang/tiempo_de_vida.cpp)
- **Firmware (`examples/embedded/`):** [`register_field.cpp`](examples/embedded/register_field.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@lifetime` `@performance` `@type-design` `@errors`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@safety` `@lifetime` `@performance` `@tooling`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@type-design` `@performance` `@lifetime` `@safety`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@safety` `@tooling` `@abi`
- [14 — C++26](../14-cpp26) · `@safety` `@errors` `@performance` `@type-design`
- [11 — Strings, formato, tiempo y E/S](../11-format-chrono-io) · `@performance` `@type-design` `@abi` `@safety`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/13-embedded.md`](../../docs/notas/13-embedded.md)
