# 17 — Rendimiento y diseño orientado a datos

Módulo nuevo. Navegadores, motores de búsqueda e infraestructura a gran escala exigen razonar sobre caché, asignaciones y coste de abstracciones, y medir en vez de suponer.

**Temas core:** `@performance` `@tooling` `@type-design` `@lifetime` `@iteration` `@concurrency`

**Firmware:** 🟢 `@emb:ok` ×4 · 🟡 `@emb:cond` ×3

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Medir: benchmarks fiables (Google Benchmark), `perf`, flame graphs, contadores de hardware · `@performance` `@tooling`
2. Memoria
    1. Jerarquía de caché, localidad, prefetching · `@performance` 🟡 `@emb:cond` _MCUs sin caché: importa el acceso a flash_
    2. AoS frente a SoA, diseño orientado a datos · `@performance` `@type-design` 🟢 `@emb:ok`
    3. Asignaciones: coste, pools, arenas, `pmr`, *small buffer optimization* · `@performance` `@lifetime` 🟢 `@emb:ok`
    4. Contenedores: `vector` como opción por defecto, `unordered_map` frente a tablas abiertas · `@performance` `@iteration`
3. Coste de abstracciones: inlining, devirtualización, `std::function`, excepciones, RTTI · `@performance` 🟢 `@emb:ok`
4. Compilador: `-O2`/`-O3`/`-Os`, LTO, PGO, vectorización, `[[likely]]`, `[[assume]]` · `@performance` `@tooling` 🟡 `@emb:cond` _PGO poco práctico en target_
5. Ramas y predicción, código sin ramas, aritmética de punto fijo · `@performance` 🟢 `@emb:ok`
6. Concurrencia: false sharing, contención, lock-free frente a mutex · `@performance` `@concurrency`
7. `std::simd` [26] e intrínsecos (NEON, SSE/AVX) · `@performance` 🟡 `@emb:cond` _NEON en Cortex-A; Helium en M55_

## Ejercicio

Optimizar el procesado de un bloque de muestras de ADC: versión AoS ingenua, versión SoA, versión en punto fijo Q15; medir en host con Google Benchmark y en target con ciclos del DWT.

## Preguntas de control (nivel entrevista)

1. ¿Por qué `std::vector` suele ganar a `std::list` incluso en inserciones en medio?
2. ¿Cómo escribirías un microbenchmark que el optimizador no elimine?
3. ¿Qué es SoA y cuándo mejora el rendimiento?
4. ¿Cómo medirías ciclos de una función en un Cortex-M4?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`aos_soa.cpp`](examples/lang/aos_soa.cpp), [`asignaciones.cpp`](examples/lang/asignaciones.cpp), [`coste_abstracciones.cpp`](examples/lang/coste_abstracciones.cpp)
- **Firmware (`examples/embedded/`):** [`q15.cpp`](examples/embedded/q15.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@performance` `@tooling` `@type-design` `@lifetime`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@performance` `@tooling` `@type-design` `@lifetime`
- [09 — Concurrencia y modelo de memoria](../09-concurrencia) · `@performance` `@tooling` `@lifetime` `@concurrency`
- [08 — Clases y novedades del lenguaje](../08-clases-lenguaje) · `@performance` `@tooling` `@type-design` `@lifetime`
- [07 — Ranges, views y algoritmos](../07-ranges) · `@performance` `@tooling` `@lifetime` `@iteration`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@performance` `@type-design` `@lifetime` `@iteration`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/17-rendimiento.md`](../../docs/notas/17-rendimiento.md)
