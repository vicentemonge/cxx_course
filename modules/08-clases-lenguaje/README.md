# 08 — Clases y novedades del lenguaje

Cambios que reducen código repetitivo y bugs en clases: comparaciones, inicialización, desestructuración y deducción de `this`.

**Temas core:** `@type-design` `@performance` `@lifetime` `@generic` `@memory-model` `@tooling`

**Firmware:** 🟢 `@emb:ok` ×8 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Structured bindings [17], tipos tuple-like, con capturas [20], como condición [26] · `@type-design` 🟢 `@emb:ok`
2. `if`/`switch` con inicializador [17], range-`for` con inicializador [20] · `@lifetime` 🟢 `@emb:ok`
3. Comparaciones: `<=>` [20], categorías de ordenación, `==` por defecto, reescritura · `@type-design` 🟢 `@emb:ok`
4. Designated initializers [20] y configuración de periféricos · `@type-design` 🟢 `@emb:ok`
5. *Deducing this* [23]: sobrecargas const/&&, CRTP sin CRTP, lambdas recursivas · `@generic` `@type-design` 🟢 `@emb:ok`
6. Polimorfismo dinámico: vtables, destructores virtuales, *slicing*, `final` para devirtualizar · `@type-design` `@performance` 🟡 `@emb:cond` _vtables en flash; evitar RTTI_
7. Atributos: `[[maybe_unused]]`, `[[fallthrough]]` [17], `[[likely]]`, `[[no_unique_address]]` [20], `[[assume]]` [23] · `@performance` 🟢 `@emb:ok`
8. Otros: `explicit(bool)` [20], `char8_t` [20], `auto(x)` [23], `operator[]` multidimensional [23] · `@type-design`
9. `volatile`: usos deprecados [20] y revertidos [23]; solo para MMIO · `@memory-model` 🟢 `@emb:ok`
10. Preprocesador: `#elifdef` [23], `#embed` [26] · `@tooling` 🟢 `@emb:ok` _`#embed` para blobs de firmware_

## Ejercicio

Definir la configuración de un periférico con designated initializers y un tipo de versión de firmware comparable con `<=>`.

## Preguntas de control (nivel entrevista)

1. ¿Qué genera `auto operator<=>(const T&) const = default;` y qué no?
2. ¿Qué es el *object slicing* y cómo se previene?
3. ¿Qué problema de CRTP resuelve *deducing this*?
4. ¿Cuándo es útil `[[no_unique_address]]`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`deducing_this.cpp`](examples/lang/deducing_this.cpp), [`inicializadores_atributos.cpp`](examples/lang/inicializadores_atributos.cpp), [`spaceship.cpp`](examples/lang/spaceship.cpp), [`structured_bindings.cpp`](examples/lang/structured_bindings.cpp)
- **Firmware (`examples/embedded/`):** [`firmware_version.cpp`](examples/embedded/firmware_version.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@type-design` `@performance` `@lifetime` `@generic`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@type-design` `@performance` `@lifetime`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@generic` `@performance` `@tooling`
- [13 — C++ moderno en embedded](../13-embedded) · `@type-design` `@performance` `@lifetime` `@memory-model`
- [11 — Strings, formato, tiempo y E/S](../11-format-chrono-io) · `@type-design` `@performance` `@generic`
- [17 — Rendimiento y diseño orientado a datos](../17-rendimiento) · `@performance` `@type-design` `@lifetime` `@tooling`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/08-clases-lenguaje.md`](../../docs/notas/08-clases-lenguaje.md)
