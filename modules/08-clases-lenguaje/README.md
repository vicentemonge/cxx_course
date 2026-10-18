# 08 — Clases y novedades del lenguaje

Menos código repetitivo: comparaciones, inicialización, desestructuración y deducción de `this`.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Structured bindings [17], tipos propios, con `static` y capturas [20], como condición [26]
2. `if`/`switch` con inicializador [17], range-`for` con inicializador [20]
3. Comparaciones: `<=>` [20], categorías de ordenación, `==` por defecto
4. Designated initializers [20] y configuración de periféricos
5. *Deducing this* [23]: sobrecargas const/no-const, CRTP sin CRTP, lambdas recursivas
6. Atributos: `[[maybe_unused]]`, `[[fallthrough]]` [17], `[[likely]]`, `[[no_unique_address]]` [20], `[[assume]]` [23]
7. Otros: `explicit(bool)` [20], `char8_t` [20], `volatile` [20/23], `auto(x)` [23], `operator[]` multidimensional [23], `#elifdef` [23], `#embed` [26], `= delete("motivo")` [26]

## Ejercicio

Definir la configuración de un periférico con designated initializers y un tipo de versión de firmware comparable con `<=>`.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/08-clases-lenguaje.md`](../../docs/notas/08-clases-lenguaje.md)

## Ejemplo inicial

`examples/firmware_version.hpp`, `examples/firmware_version.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
