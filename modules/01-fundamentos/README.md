# 01 — Fundamentos del C++ moderno

Base de C++11/14 sobre la que se construye todo. En una entrevista de nivel senior se da por supuesto: los fallos aquí (categorías de valor, reglas de miembros especiales) descartan candidatos antes de llegar a templates o concurrencia.

**Temas core:** `@type-design` `@value-sem` `@lifetime` `@generic` `@performance` `@safety` `@errors` `@interop` `@compile-time`

**Firmware:** 🟢 `@emb:ok` ×10 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Inicialización
    1. Llaves, *narrowing* y *most vexing parse* [11] · `@type-design` 🟢 `@emb:ok`
    2. `std::initializer_list` y su prioridad en la resolución de sobrecarga [11] · `@generic`
    3. NSDMI [11/14], agregados [11→20], agregados con paréntesis [20] · `@type-design` 🟢 `@emb:ok`
    4. Inicialización por defecto, de valor y cero; variables sin inicializar · `@safety` 🟢 `@emb:ok`
2. Deducción de tipos
    1. Reglas de deducción de templates como base de `auto` [11] · `@generic`
    2. `auto`, `decltype`, `decltype(auto)`, *trailing return* [11/14] · `@generic`
    3. Trampas: proxies (`vector<bool>`), `auto x{1}` [11 vs 17], referencias perdidas · `@value-sem`
3. Semántica de movimiento
    1. Categorías de valor: lvalue, prvalue, xvalue [11/17] · `@value-sem`
    2. Forwarding references, colapso de referencias, `std::forward` [11] · `@value-sem` `@generic`
    3. *Copy elision* garantizada [17], NRVO, movimiento implícito al retornar [20/23] · `@value-sem` `@performance` 🟢 `@emb:ok`
    4. `noexcept` en movimiento y su efecto en contenedores · `@errors` `@performance`
    5. Estado "movido": válido pero no especificado; diseñar el estado vacío · `@lifetime`
4. Miembros especiales y propiedad
    1. Reglas de generación implícita (tabla de Hinnant) y Rule of Zero/Five · `@lifetime` `@value-sem` 🟢 `@emb:ok`
    2. `= default`, `= delete`, constructores `explicit`, delegados y heredados [11] · `@type-design`
    3. `std::unique_ptr` con *deleters* propios [11] · `@lifetime` 🟢 `@emb:ok` _sin heap si envuelve handles estáticos_
    4. `shared_ptr`/`weak_ptr`, `make_shared`, coste del bloque de control · `@lifetime` `@performance` 🟡 `@emb:cond` _heap y atomics_
    5. `make_unique` [14], `make_unique_for_overwrite` [20], `out_ptr`/`inout_ptr` [23] · `@lifetime` `@interop`
5. Mejoras básicas del lenguaje
    1. `enum class`, tipo subyacente [11], `using enum` [20], `to_underlying` [23] · `@type-design` 🟢 `@emb:ok`
    2. `nullptr`, `override`/`final`, alias con `using` [11] · `@type-design` 🟢 `@emb:ok`
    3. Raw strings, UDLs [11], literales binarios y separador `'` [14] · `@type-design` 🟢 `@emb:ok` _UDLs para unidades físicas_
    4. `static_assert` [11/17], range-`for` [11/20] · `@compile-time` 🟢 `@emb:ok`

## Ejercicio

Envolver un handle de periférico (UART o SPI de la HAL) en una clase RAII movible y no copiable, con `enum class` para los modos de configuración.

## Preguntas de control (nivel entrevista)

1. ¿Qué miembros especiales genera el compilador si declaras solo un destructor? ¿Y si declaras un constructor de movimiento?
2. ¿Por qué `std::vector` copia en vez de mover al crecer si el constructor de movimiento no es `noexcept`?
3. Diferencia entre `std::move` y `std::forward`. ¿Qué hace `std::move` exactamente?
4. ¿Qué devuelve `decltype((x))` y por qué difiere de `decltype(x)`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`deduccion_tipos.cpp`](examples/lang/deduccion_tipos.cpp), [`enums_literales.cpp`](examples/lang/enums_literales.cpp), [`inicializacion.cpp`](examples/lang/inicializacion.cpp), [`move_semantics.cpp`](examples/lang/move_semantics.cpp)
- **Firmware (`examples/embedded/`):** [`raii_uart.cpp`](examples/embedded/raii_uart.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@lifetime` `@type-design` `@performance` `@safety`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@generic` `@value-sem` `@safety`
- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@type-design` `@performance` `@lifetime` `@safety`
- [08 — Clases y novedades del lenguaje](../08-clases-lenguaje) · `@type-design` `@performance` `@generic` `@lifetime`
- [11 — Strings, formato, tiempo y E/S](../11-format-chrono-io) · `@type-design` `@performance` `@generic` `@safety`
- [06 — Lambdas y estilo funcional](../06-lambdas) · `@generic` `@lifetime` `@safety` `@value-sem`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/01-fundamentos.md`](../../docs/notas/01-fundamentos.md)
