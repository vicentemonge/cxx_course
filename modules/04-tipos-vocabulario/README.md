# 04 — Tipos vocabulario

Tipos que expresan intención en interfaces y eliminan clases enteras de bugs (nulos, uniones mal etiquetadas, puntero+longitud). Es lo primero que se revisa en un code review.

**Temas core:** `@type-design` `@performance` `@lifetime` `@safety` `@errors` `@functional` `@iteration`

**Firmware:** 🟢 `@emb:ok` ×9 · 🟡 `@emb:cond` ×1 · 🔴 `@emb:no` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. `std::optional` [17], monádico [23], `optional<T&>` [26] · `@type-design` `@errors` 🟢 `@emb:ok`
2. `std::variant` [17]
    1. `visit`, patrón *overloaded*, `get_if`, `valueless_by_exception` · `@type-design` `@functional` 🟢 `@emb:ok`
    2. Máquinas de estado con `variant` · `@type-design` 🟢 `@emb:ok`
    3. Coste: tamaño = mayor alternativa + índice; `visit` y tablas de salto · `@performance`
3. `std::any` [17] · `@type-design` 🔴 `@emb:no` _heap y RTTI_
4. Vistas no propietarias
    1. `string_view` [17] y *dangling* · `@lifetime` `@safety` 🟢 `@emb:ok`
    2. `span` [20], extensión estática/dinámica, `as_bytes` · `@lifetime` `@type-design` 🟢 `@emb:ok`
    3. `mdspan` [23] · `@type-design` 🟢 `@emb:ok`
5. Contenedores
    1. `array`, `to_array` [20], `tuple`, `apply` [17], `byte` [17] · `@type-design` 🟢 `@emb:ok`
    2. `flat_map`/`flat_set` [23] · `@performance` 🟡 `@emb:cond` _contenedor subyacente con heap_
    3. `inplace_vector` [26] · `@type-design` 🟢 `@emb:ok`
    4. `try_emplace` [17], `contains`, `erase_if`, `ssize` [20] · `@iteration`
6. Tipos fuertes (*strong typedefs*): unidades, IDs y evitar argumentos intercambiables · `@type-design` `@safety` 🟢 `@emb:ok`

## Ejercicio

Sustituir las firmas `(uint8_t* buf, size_t len)` de un driver por `std::span<std::byte>` y modelar los estados de un parser de tramas con `std::variant`.

## Preguntas de control (nivel entrevista)

1. ¿Cuándo devolverías `std::optional<T>` y cuándo `std::expected<T, E>`?
2. ¿Qué riesgos tiene guardar un `std::string_view` como miembro de clase?
3. ¿Qué es `valueless_by_exception` y cuándo puede ocurrir?
4. Diseña un tipo fuerte `Milliseconds` que no se pueda confundir con `Hertz`.

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`contenedores.cpp`](examples/lang/contenedores.cpp), [`optional_monadico.cpp`](examples/lang/optional_monadico.cpp), [`string_view_span.cpp`](examples/lang/string_view_span.cpp), [`variant_visit.cpp`](examples/lang/variant_visit.cpp)
- **Firmware (`examples/embedded/`):** [`frame_parser.cpp`](examples/embedded/frame_parser.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@type-design` `@performance` `@lifetime` `@errors`
- [13 — C++ moderno en embedded](../13-embedded) · `@type-design` `@performance` `@lifetime` `@safety`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@safety` `@functional` `@performance`
- [08 — Clases y novedades del lenguaje](../08-clases-lenguaje) · `@type-design` `@performance` `@lifetime`
- [05 — Gestión de errores](../05-gestion-errores) · `@type-design` `@lifetime` `@errors` `@functional`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@performance` `@lifetime` `@safety` `@type-design`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/04-tipos-vocabulario.md`](../../docs/notas/04-tipos-vocabulario.md)
