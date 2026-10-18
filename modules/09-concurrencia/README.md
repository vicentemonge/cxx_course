# 09 — Concurrencia y modelo de memoria

El modelo de memoria [11] explica `volatile` frente a `std::atomic` y la comunicación entre ISR, tareas e hilos.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Modelo de memoria [11]: *happens-before*, data races, `volatile` vs sincronización
2. `std::atomic` [11]
    1. Órdenes de memoria
    2. Lock-free en Cortex-M0 vs M3/M4/M7, `is_always_lock_free` [17]
    3. `atomic_ref` [20], `wait`/`notify` [20], `atomic<shared_ptr>` [20]
    4. Fences
3. Hilos: `thread` [11], `jthread`/`stop_token` [20], `mutex`, `scoped_lock` [17], `shared_mutex` [17], `condition_variable`, `counting_semaphore`/`latch`/`barrier` [20], `call_once`
4. Tareas: `async`/`future` [11], `std::execution` [26]
5. RTOS: RAII sobre FreeRTOS, `Lockable` para `lock_guard`, buffers SPSC ISR→tarea

## Ejercicio

Implementar un ring buffer SPSC lock-free con `std::atomic` y órdenes acquire/release para pasar datos de una ISR a una tarea, y razonar formalmente su corrección.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/09-concurrencia.md`](../../docs/notas/09-concurrencia.md)

## Ejemplo inicial

`examples/spsc_ring.hpp`, `examples/spsc_ring.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
