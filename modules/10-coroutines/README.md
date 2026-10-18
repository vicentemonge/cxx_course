# 10 — Coroutines

Mecanismo de bajo nivel [20] con `std::generator` [23] y `std::execution` [26] encima. Se usa en servidores asíncronos (Folly, Seastar) y promete mucho en máquinas de estado de firmware.

**Temas core:** `@async` `@lifetime` `@safety` `@iteration` `@performance`

**Firmware:** 🟢 `@emb:ok` ×1 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Conceptos: stackless frente a hilos y *fibers*; `co_await`/`co_yield`/`co_return`; el frame · `@async` `@lifetime`
2. Maquinaria [20]: `promise_type`, `coroutine_handle`, awaitables, transferencia simétrica · `@async`
3. Tiempo de vida: referencias en parámetros que no sobreviven a la suspensión · `@async` `@lifetime` `@safety`
4. Tipos de alto nivel: `generator<T>` propio, `std::generator` [23], `task<T>` · `@async` `@iteration`
5. Embedded
    1. `operator new` en `promise_type`, pools estáticos, HALO · `@async` `@performance` 🟡 `@emb:cond` _el frame usa heap salvo que se controle_
    2. Protocolos con timeouts y scheduler cooperativo · `@async` 🟢 `@emb:ok`

## Ejercicio

Reescribir una máquina de estados de protocolo (handshake por UART con reintentos y timeout) como coroutine, con frames asignados desde un pool estático.

## Preguntas de control (nivel entrevista)

1. ¿Dónde vive el estado de una coroutine y quién lo destruye?
2. ¿Por qué es peligroso pasar un `const std::string&` a una coroutine?
3. ¿Qué es la transferencia simétrica y qué problema evita?
4. ¿Cómo evitarías la asignación dinámica del frame en un microcontrolador?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`ciclo_de_vida.cpp`](examples/lang/ciclo_de_vida.cpp), [`std_generator.cpp`](examples/lang/std_generator.cpp)
- **Firmware (`examples/embedded/`):** [`generator.cpp`](examples/embedded/generator.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [09 — Concurrencia y modelo de memoria](../09-concurrencia) · `@lifetime` `@async` `@safety` `@performance`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@lifetime` `@safety` `@iteration` `@performance`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@lifetime` `@safety` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@lifetime` `@safety` `@performance`
- [07 — Ranges, views y algoritmos](../07-ranges) · `@lifetime` `@safety` `@iteration` `@performance`
- [06 — Lambdas y estilo funcional](../06-lambdas) · `@lifetime` `@safety` `@performance`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/10-coroutines.md`](../../docs/notas/10-coroutines.md)
