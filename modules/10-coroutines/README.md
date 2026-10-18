# 10 — Coroutines

Mecanismo de bajo nivel [20], `std::generator` en [23]. Prometedor para máquinas de estado y protocolos asíncronos.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Conceptos: stackless vs hilos, `co_await`/`co_yield`/`co_return`, el frame
2. Maquinaria [20]: `promise_type`, `coroutine_handle`, awaitables, transferencia simétrica, ciclo de vida
3. Tipos de alto nivel: `generator<T>` propio, `std::generator` [23], `task<T>` simple
4. Embedded: `operator new` en `promise_type`, pools estáticos, HALO, protocolos con timeouts, scheduler cooperativo

## Ejercicio

Reescribir una máquina de estados de protocolo (handshake por UART con reintentos y timeout) como coroutine, con frames asignados desde un pool estático.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/10-coroutines.md`](../../docs/notas/10-coroutines.md)

## Ejemplo inicial

`examples/generator.hpp`, `examples/generator.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
