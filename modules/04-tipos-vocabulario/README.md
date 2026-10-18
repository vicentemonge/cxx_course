# 04 — Tipos vocabulario

Tipos que expresan intención y sustituyen punteros nulos, uniones manuales y pares puntero+longitud.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. `std::optional` [17], operaciones monádicas [23], `optional<T&>` [26]
2. `std::variant` [17]
    1. `std::visit` y patrón *overloaded*
    2. `get_if`, `holds_alternative`, `valueless_by_exception`
    3. Máquinas de estado con `variant`
3. `std::any` [17] y por qué casi nunca en embedded
4. Vistas no propietarias
    1. `std::string_view` [17] y *dangling*
    2. `std::span` [20]: extensión estática/dinámica, `as_bytes`
    3. `std::mdspan` [23]
5. Contenedores y utilidades
    1. `std::array`, `std::to_array` [20]
    2. `tuple`, `apply`, `make_from_tuple` [17]
    3. `std::byte` [17]
    4. `flat_map` / `flat_set` [23]
    5. `inplace_vector` [26]
6. Funciones de contenedores: `try_emplace` [17], `contains` [20], `std::erase_if` [20], `std::ssize` [20]

## Ejercicio

Sustituir las firmas `(uint8_t* buf, size_t len)` de un driver por `std::span<std::byte>` y modelar los estados de un parser de tramas con `std::variant`.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/04-tipos-vocabulario.md`](../../docs/notas/04-tipos-vocabulario.md)

## Ejemplo inicial

`examples/frame_parser.hpp`, `examples/frame_parser.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
