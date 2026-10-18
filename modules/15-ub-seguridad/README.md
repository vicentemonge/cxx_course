# 15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria

Módulo nuevo y prioritario. Mozilla, Google, Meta y DuckDuckGo invierten en seguridad de memoria (Rust, hardening, sanitizers). Un ingeniero top de C++ debe saber qué es UB, por qué el optimizador lo explota y cómo eliminar clases enteras de vulnerabilidades.

**Temas core:** `@safety` `@lifetime` `@performance` `@interop` `@tooling` `@type-design`

**Firmware:** 🟢 `@emb:ok` ×3 · 🟡 `@emb:cond` ×2

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Modelo de objetos
    1. Objeto, almacenamiento, tiempo de vida; inicio y fin de vida · `@lifetime` `@safety`
    2. Creación implícita de objetos [20], `start_lifetime_as` [23] · `@lifetime` `@safety` 🟢 `@emb:ok`
    3. Alineación, padding, `alignas`, `alignof`, tamaños de tipos · `@performance` 🟢 `@emb:ok`
    4. Tipos trivialmente copiables, *standard layout*, implicit-lifetime types · `@type-design` `@interop`
2. Comportamiento indefinido
    1. Catálogo: overflow con signo, desplazamientos, nulos, fuera de límites, data races, uso tras liberar · `@safety`
    2. *Strict aliasing* y `bit_cast`/`memcpy` como alternativas · `@safety` 🟢 `@emb:ok`
    3. Cómo el optimizador explota el UB (eliminación de comprobaciones) · `@safety` `@performance`
    4. Comportamiento no especificado e implementation-defined · `@safety`
    5. Comportamiento erróneo [26] · `@safety`
3. Seguridad de memoria
    1. Dangling: referencias, vistas, iteradores, lambdas, coroutines · `@lifetime` `@safety`
    2. Bounds checking: `.at()`, `span`, modos de hardening (`_GLIBCXX_ASSERTIONS`, libc++ hardening) · `@safety` 🟡 `@emb:cond` _coste de tamaño; activar en debug_
    3. Clang `-Wunsafe-buffer-usage`, `-Wdangling`, `[[clang::lifetimebound]]` · `@safety` `@tooling`
    4. Perfiles de seguridad y lifetime analysis (propuestas) · `@safety`
4. Detección: ASan, UBSan, MSan, TSan, Valgrind; constexpr como detector de UB · `@safety` `@tooling` 🟡 `@emb:cond` _en host, no en target_
5. Contexto: C++ frente a Rust en Mozilla/Google; cuándo reescribir y cuándo endurecer · `@safety` `@interop`

## Ejercicio

Reunir cinco bugs de UB típicos de firmware (aliasing de buffers, overflow en contadores, shift de 32 bits, lectura sin inicializar, dangling de `string_view`), reproducirlos con UBSan/ASan en host y corregirlos sin coste en el target.

## Preguntas de control (nivel entrevista)

1. ¿Por qué el compilador puede eliminar `if (x + 1 < x)` con `int x`?
2. ¿Qué es *strict aliasing* y cuándo es legal leer un `float` como `uint32_t`?
3. ¿Qué detecta ASan que no detecta UBSan, y viceversa?
4. ¿Cuándo empieza y termina el tiempo de vida de un objeto creado con `malloc`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`aliasing.cpp`](examples/lang/aliasing.cpp), [`dangling.cpp`](examples/lang/dangling.cpp), [`modelo_de_objetos.cpp`](examples/lang/modelo_de_objetos.cpp), [`overflow_con_signo.cpp`](examples/lang/overflow_con_signo.cpp)
- **Firmware (`examples/embedded/`):** [`ticks.cpp`](examples/embedded/ticks.cpp), [`trama_a_struct.cpp`](examples/embedded/trama_a_struct.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@safety` `@lifetime` `@performance` `@tooling`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@safety` `@interop` `@tooling` `@performance`
- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@lifetime` `@performance` `@safety` `@type-design`
- [09 — Concurrencia y modelo de memoria](../09-concurrencia) · `@lifetime` `@safety` `@performance` `@tooling`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@lifetime` `@safety` `@performance` `@type-design`
- [17 — Rendimiento y diseño orientado a datos](../17-rendimiento) · `@performance` `@tooling` `@lifetime` `@type-design`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/15-ub-seguridad.md`](../../docs/notas/15-ub-seguridad.md)
