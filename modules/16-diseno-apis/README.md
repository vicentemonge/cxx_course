# 16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad

Módulo nuevo. En empresas con bibliotecas compartidas por cientos de ingenieros se evalúa la capacidad de diseñar APIs estables, elegir el tipo de polimorfismo adecuado e integrar C y Rust.

**Temas core:** `@type-design` `@abi` `@interop` `@value-sem` `@generic` `@safety` `@tooling` `@functional` `@performance`

**Firmware:** 🟢 `@emb:ok` ×4 · 🟡 `@emb:cond` ×3

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Semántica de valor frente a referencia en el diseño de APIs · `@value-sem` `@type-design`
2. Polimorfismo: cuatro herramientas
    1. Dinámico (virtual) · `@type-design` 🟡 `@emb:cond` _vtables, sin RTTI_
    2. Estático (templates/concepts, CRTP, deducing this) · `@generic` 🟢 `@emb:ok`
    3. Cerrado (`std::variant`) · `@type-design` 🟢 `@emb:ok`
    4. *Type erasure* (estilo `std::function`, Sean Parent) · `@type-design` `@functional` 🟡 `@emb:cond` _sin heap con SBO fijo_
3. Diseño de interfaces
    1. Parámetros: por valor, `const&`, `&&`, vistas; devolución de valores · `@value-sem` `@performance`
    2. Invariantes, `explicit`, tipos fuertes, difícil de usar mal · `@type-design` `@safety`
    3. Inyección de dependencias con concepts para testabilidad · `@generic` `@tooling` 🟢 `@emb:ok`
4. ABI y bibliotecas
    1. Estabilidad de ABI, por qué el estándar no rompe `std::string` · `@abi`
    2. PIMPL, *fast PIMPL*, interfaces abstractas · `@abi` 🟡 `@emb:cond` _PIMPL implica heap salvo storage fijo_
    3. Visibilidad de símbolos, `-fvisibility=hidden`, versionado · `@abi`
5. Interoperabilidad
    1. APIs en C: `extern "C"`, tipos opacos, propiedad entre fronteras · `@interop` `@abi` 🟢 `@emb:ok`
    2. Rust: `cxx`, `bindgen`, cbindgen; reparto de propiedad · `@interop` `@safety`
    3. Python: pybind11/nanobind para herramientas de test · `@interop` `@tooling`

## Ejercicio

Diseñar la interfaz de un driver de sensor con tres implementaciones (virtual, concept y type erasure con buffer fijo), medir tamaño de código y RAM de cada una en ARM y exponer la API como C para su uso desde Rust o Python.

## Preguntas de control (nivel entrevista)

1. ¿Cuándo elegirías `std::variant`, una jerarquía virtual o type erasure?
2. ¿Qué cambios en una clase rompen la ABI?
3. ¿Cómo pasarías la propiedad de un objeto C++ a código Rust de forma segura?
4. Diseña una API que haga imposible confundir el orden de dos parámetros enteros.

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`api_c.cpp`](examples/lang/api_c.cpp), [`pimpl.cpp`](examples/lang/pimpl.cpp), [`tipos_fuertes.cpp`](examples/lang/tipos_fuertes.cpp), [`type_erasure.cpp`](examples/lang/type_erasure.cpp)
- **Firmware (`examples/embedded/`):** [`sensor_polimorfismo.cpp`](examples/embedded/sensor_polimorfismo.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@type-design` `@value-sem` `@generic` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@type-design` `@safety` `@tooling` `@performance`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@type-design` `@safety` `@functional` `@performance`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@safety` `@tooling` `@interop` `@type-design`
- [11 — Strings, formato, tiempo y E/S](../11-format-chrono-io) · `@type-design` `@generic` `@performance` `@safety`
- [08 — Clases y novedades del lenguaje](../08-clases-lenguaje) · `@type-design` `@generic` `@performance` `@tooling`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/16-diseno-apis.md`](../../docs/notas/16-diseno-apis.md)
