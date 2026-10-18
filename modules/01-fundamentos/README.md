# 01 — Fundamentos del C++ moderno

Base de C++11/14 sobre la que se construye todo lo demás.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Inicialización
    1. Inicialización uniforme con llaves y prevención de *narrowing* [11]
    2. `std::initializer_list` y su conflicto con constructores sobrecargados [11]
    3. NSDMI [11], agregados con NSDMI [14]
    4. Reglas de agregados [11→14→17→20], agregados con paréntesis [20]
    5. *Most vexing parse*
2. Deducción de tipos
    1. Deducción de templates como base de `auto` [11]
    2. `auto`, `decltype`, `decltype(auto)` [11/14]
    3. *Trailing return type* [11], deducción del retorno [14]
    4. Trampas: proxies (`std::vector<bool>`), `auto x{1}` [11 vs 17]
3. Semántica de movimiento
    1. Categorías de valor [11] y cambios de C++17
    2. Forwarding references y colapso de referencias [11]
    3. `std::move` vs `std::forward`
    4. *Copy elision* garantizada [17] y NRVO
    5. Movimiento implícito al retornar [20/23]
    6. `noexcept` en movimiento y su efecto en contenedores
4. Gestión de recursos
    1. `std::unique_ptr` con *deleters* propios [11]
    2. `shared_ptr`, `weak_ptr`, `make_shared` [11]
    3. `make_unique` [14], `make_unique_for_overwrite` [20]
    4. Rule of Zero/Five en wrappers de periféricos
    5. `std::out_ptr` / `std::inout_ptr` [23]
5. Mejoras básicas del lenguaje
    1. `enum class` [11], `using enum` [20], `std::to_underlying` [23]
    2. `nullptr`, `override`/`final`, `= default`/`= delete` [11]
    3. Constructores delegados y heredados [11]
    4. Alias con `using` [11]
    5. Raw strings, UDLs [11], literales binarios y `'` [14]
    6. `static_assert` [11], sin mensaje [17]
    7. Range-`for` [11], con inicializador [20]

## Ejercicio

Envolver un handle de periférico (UART o SPI de la HAL) en una clase RAII movible y no copiable, con `enum class` para los modos de configuración.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/01-fundamentos.md`](../../docs/notas/01-fundamentos.md)

## Ejemplo inicial

`examples/raii_uart.hpp`, `examples/raii_uart.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
