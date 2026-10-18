# 05 — Gestión de errores

`std::expected` [23]: errores tipados, imposibles de ignorar y sin coste oculto con `-fno-exceptions`.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Panorama: códigos de retorno, `errno`, excepciones, tipos resultado; coste en Cortex-M
2. `std::expected<T, E>` [23]
    1. `std::unexpected`
    2. `value`, `error`, `value_or`, `operator*`
    3. `and_then`, `transform`, `or_else`, `transform_error`
    4. `expected<void, E>`
    5. Diseño del tipo de error
3. `std::error_code` / `std::error_category` [11]
4. Atributos: `[[nodiscard]]` [17/20], `noexcept` [11/17], `[[noreturn]]`, `std::unreachable` [23]
5. Precondiciones: `assert`, `std::source_location` [20], contracts [26]

## Ejercicio

Convertir la API pública de un driver de códigos `int` a `std::expected<T, DriverError>` y encadenar init → configure → read con `and_then`.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/05-gestion-errores.md`](../../docs/notas/05-gestion-errores.md)

## Ejemplo inicial

`examples/expected_driver.hpp`, `examples/expected_driver.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
