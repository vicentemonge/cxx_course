# 09 — Concurrencia y modelo de memoria

Pregunta segura en cualquier entrevista de sistemas. El modelo de memoria [11] explica `volatile` frente a `std::atomic` y la comunicación entre ISR, tareas e hilos.

**Temas core:** `@concurrency` `@memory-model` `@safety` `@performance` `@lifetime` `@async` `@tooling`

**Firmware:** 🟢 `@emb:ok` ×3 · 🟡 `@emb:cond` ×2 · 🔴 `@emb:no` ×2

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Modelo de memoria [11]: *happens-before*, *synchronizes-with*, data races = UB · `@memory-model` `@safety`
2. `std::atomic` [11]
    1. Órdenes de memoria y cuándo basta `relaxed` · `@memory-model` `@performance` 🟢 `@emb:ok`
    2. Lock-free en Cortex-M0 frente a M3/M4/M7, `is_always_lock_free` [17] · `@memory-model` 🟡 `@emb:cond` _M0 no tiene LDREX/STREX_
    3. `atomic_ref`, `wait`/`notify`, `atomic<shared_ptr>` [20], fences · `@memory-model` `@concurrency`
3. Problemas clásicos: deadlock, livelock, inversión de prioridad, *false sharing* (`hardware_destructive_interference_size` [17]), ABA · `@concurrency` `@performance` 🟢 `@emb:ok`
4. Hilos y sincronización
    1. `thread`, `jthread`/`stop_token` [20], `thread_local` [11] · `@concurrency` `@lifetime` 🔴 `@emb:no` _bare-metal sin hilos; usar el RTOS_
    2. `mutex`, `scoped_lock` [17], `shared_mutex` [17], `condition_variable` · `@concurrency` 🟡 `@emb:cond` _vía primitivas del RTOS_
    3. `counting_semaphore`, `latch`, `barrier` [20], `call_once` · `@concurrency`
5. Tareas: `async`/`future` [11] y sus límites, `std::execution` [26] · `@concurrency` `@async` 🔴 `@emb:no`
6. RTOS: RAII sobre FreeRTOS, requisitos `Lockable` para `lock_guard`, SPSC ISR→tarea · `@concurrency` `@lifetime` 🟢 `@emb:ok`
7. Detección: ThreadSanitizer, revisión de órdenes de memoria · `@tooling` `@safety`

## Ejercicio

Implementar un ring buffer SPSC lock-free con `std::atomic` y órdenes acquire/release para pasar datos de una ISR a una tarea, y razonar formalmente su corrección.

## Preguntas de control (nivel entrevista)

1. ¿Por qué `volatile` no sirve para sincronizar hilos?
2. Explica acquire/release con un ejemplo de publicación de datos.
3. ¿Qué es el *false sharing* y cómo lo detectas y corriges?
4. ¿Cómo implementas un mutex compatible con `std::lock_guard` sobre FreeRTOS?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`async_future.cpp`](examples/lang/async_future.cpp), [`atomics.cpp`](examples/lang/atomics.cpp), [`jthread_stop_token.cpp`](examples/lang/jthread_stop_token.cpp), [`primitivas_sincronizacion.cpp`](examples/lang/primitivas_sincronizacion.cpp)
- **Firmware (`examples/embedded/`):** [`spsc_ring.cpp`](examples/embedded/spsc_ring.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@safety` `@performance` `@lifetime` `@memory-model`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@safety` `@performance` `@lifetime` `@tooling`
- [14 — C++26](../14-cpp26) · `@safety` `@concurrency` `@memory-model` `@performance`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@safety` `@performance` `@lifetime`
- [17 — Rendimiento y diseño orientado a datos](../17-rendimiento) · `@performance` `@concurrency` `@lifetime` `@tooling`
- [10 — Coroutines](../10-coroutines) · `@lifetime` `@safety` `@performance` `@async`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/09-concurrencia.md`](../../docs/notas/09-concurrencia.md)
