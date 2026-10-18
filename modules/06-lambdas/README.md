# 06 — Lambdas y estilo funcional

Callbacks, visitantes, algoritmos y coroutines dependen de las lambdas.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función
2. Evolución
    1. *Init-capture* [14], lambdas genéricas [14]
    2. `constexpr` lambdas, captura de `*this` [17]
    3. Parámetros template, lambdas sin estado construibles [20]
    4. Captura de structured bindings [20], deprecación de `[=]` con `this` [20]
    5. Lambdas `static` [23], recursivas con *deducing this* [23]
3. Wrappers de invocables
    1. `std::function` [11] y su coste
    2. `std::move_only_function` [23]
    3. `std::function_ref` [26]
    4. `std::invoke` [17], `invoke_r` [23]
    5. `bind_front` [20], `bind_back` [23]
4. Patrones: IIFE, *overloaded*, callbacks de ISR sin `std::function`

## Ejercicio

Implementar un dispatcher de eventos sin heap que acepte lambdas con captura, comparando tamaño de código entre `std::function`, templates y `function_ref`.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/06-lambdas.md`](../../docs/notas/06-lambdas.md)

## Ejemplo inicial

`examples/event_dispatcher.hpp`, `examples/event_dispatcher.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
