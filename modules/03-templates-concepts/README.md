# 03 — Templates modernos y concepts

Concepts [20] sustituyen casi todo el SFINAE: interfaces genéricas legibles y errores comprensibles.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Variadic templates
    1. Parameter packs y expansión [11], `sizeof...`
    2. Fold expressions [17]
    3. Expansión en lambdas y `using` [17/20]
    4. Pack indexing [26]
2. CTAD [17]
    1. Guías de deducción
    2. CTAD para agregados y alias [20]
3. SFINAE y su herencia
    1. `enable_if`, `void_t` [11/17]
    2. *Detection idiom*
4. Concepts [20]
    1. `requires` (cláusulas y expresiones)
    2. Concepts propios: requisitos simples, de tipo, compuestos, anidados
    3. Sintaxis abreviada
    4. Subsunción y sobrecarga
    5. `<concepts>` estándar
    6. Concepts de iteradores y ranges
    7. `requires` en miembros de templates de clase
5. Lambdas templatizadas y parámetros `auto` [14/20]
6. Type traits: `_t` [14], `_v` [17], `conjunction` [17], `remove_cvref` [20], `is_scoped_enum` [23]

## Ejercicio

Definir un concept `RegisterAccess` para drivers (lectura/escritura de 8/16/32 bits) y reescribir con él un driver genérico que hoy use SFINAE o `void*`.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/03-templates-concepts.md`](../../docs/notas/03-templates-concepts.md)

## Ejemplo inicial

`examples/register_concept.hpp`, `examples/register_concept.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
