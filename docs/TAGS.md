# Tags del curso

Generado por `tools/gen_docs.py` desde `tools/course_data.py`. No editar a mano.

Los tags aparecen al final de cada punto del temario. Los **core** marcan los hilos conductores que conectan módulos; los **firmware** indican si una característica aporta, es condicional o se descarta en bare-metal.

## Tags core

| Tag | Significado | Módulos (apariciones) |
|---|---|---|
| [`@lifetime`](#lifetime) | Tiempo de vida, propiedad, RAII, dangling | [01](#lifetime)×5 [15](#lifetime)×3 [02](#lifetime)×1 [04](#lifetime)×2 [05](#lifetime)×2 [08](#lifetime)×1 [06](#lifetime)×2 [07](#lifetime)×1 [09](#lifetime)×2 [17](#lifetime)×1 [13](#lifetime)×4 [10](#lifetime)×2 |
| [`@value-sem`](#value-sem) | Semántica de valor: copia, movimiento, categorías de valor | [01](#value-sem)×5 [06](#value-sem)×1 [16](#value-sem)×2 |
| [`@compile-time`](#compile-time) | Cálculo y validación en compilación | [01](#compile-time)×1 [18](#compile-time)×1 [02](#compile-time)×10 [03](#compile-time)×2 [06](#compile-time)×1 [13](#compile-time)×1 [14](#compile-time)×2 |
| [`@generic`](#generic) | Programación genérica: templates, concepts, deducción | [01](#generic)×4 [18](#generic)×1 [02](#generic)×3 [03](#generic)×13 [08](#generic)×1 [06](#generic)×2 [07](#generic)×3 [16](#generic)×2 [11](#generic)×1 [14](#generic)×2 |
| [`@type-design`](#type-design) | Diseño de tipos: tipos vocabulario, tipos fuertes, invariantes | [01](#type-design)×6 [15](#type-design)×1 [03](#type-design)×2 [04](#type-design)×9 [05](#type-design)×2 [08](#type-design)×6 [16](#type-design)×5 [17](#type-design)×1 [13](#type-design)×3 [11](#type-design)×4 [14](#type-design)×1 |
| [`@errors`](#errors) | Gestión de errores y contratos | [01](#errors)×1 [04](#errors)×1 [05](#errors)×12 [13](#errors)×1 [14](#errors)×1 |
| [`@functional`](#functional) | Lambdas, invocables y composición | [04](#functional)×1 [05](#functional)×1 [06](#functional)×10 [07](#functional)×1 [16](#functional)×1 |
| [`@iteration`](#iteration) | Iteradores, ranges y algoritmos | [03](#iteration)×1 [04](#iteration)×1 [07](#iteration)×8 [17](#iteration)×1 [10](#iteration)×1 |
| [`@concurrency`](#concurrency) | Hilos, sincronización y paralelismo | [07](#concurrency)×1 [09](#concurrency)×7 [17](#concurrency)×1 [14](#concurrency)×2 |
| [`@memory-model`](#memory-model) | Modelo de memoria, atomics y órdenes | [08](#memory-model)×1 [09](#memory-model)×4 [13](#memory-model)×1 [14](#memory-model)×1 |
| [`@async`](#async) | Coroutines y ejecución asíncrona | [09](#async)×1 [10](#async)×6 [14](#async)×1 |
| [`@performance`](#performance) | Rendimiento: coste de abstracciones, memoria, caché | [01](#performance)×3 [15](#performance)×2 [02](#performance)×1 [03](#performance)×2 [04](#performance)×2 [05](#performance)×1 [08](#performance)×2 [06](#performance)×1 [07](#performance)×1 [16](#performance)×1 [09](#performance)×2 [17](#performance)×10 [13](#performance)×3 [11](#performance)×3 [10](#performance)×1 [14](#performance)×1 |
| [`@safety`](#safety) | Comportamiento indefinido, seguridad de memoria, hardening | [01](#safety)×1 [15](#safety)×13 [18](#safety)×3 [02](#safety)×2 [04](#safety)×2 [05](#safety)×1 [06](#safety)×1 [07](#safety)×1 [16](#safety)×2 [09](#safety)×2 [13](#safety)×4 [11](#safety)×1 [10](#safety)×1 [12](#safety)×1 [14](#safety)×3 |
| [`@abi`](#abi) | Enlace, ODR, ABI, modelo de compilación y organización | [18](#abi)×1 [02](#abi)×1 [03](#abi)×1 [16](#abi)×4 [13](#abi)×1 [11](#abi)×1 [12](#abi)×8 |
| [`@interop`](#interop) | Interoperabilidad con C, Rust y otras APIs | [01](#interop)×1 [15](#interop)×2 [05](#interop)×1 [06](#interop)×1 [16](#interop)×3 [14](#interop)×1 |
| [`@tooling`](#tooling) | Build, testing, sanitizers, análisis estático | [15](#tooling)×2 [18](#tooling)×11 [02](#tooling)×1 [08](#tooling)×1 [07](#tooling)×1 [16](#tooling)×2 [09](#tooling)×1 [17](#tooling)×2 [13](#tooling)×2 [12](#tooling)×2 |

## Tags de firmware

| Tag | Significado | Puntos |
|---|---|---|
| 🟢 [`@emb:ok`](#embok) | Aporte en firmware: sin coste oculto o con beneficio claro | 89 |
| 🟡 [`@emb:cond`](#embcond) | Condicional: depende de heap, excepciones, RTTI, toolchain o tamaño de código | 25 |
| 🔴 [`@emb:no`](#embno) | Descarte en bare-metal (sigue siendo válido en Linux embebido) | 7 |

## Matriz módulo × tag core

| Módulo | `lifetime` | `value-sem` | `compile-time` | `generic` | `type-design` | `errors` | `functional` | `iteration` | `concurrency` | `memory-model` | `async` | `performance` | `safety` | `abi` | `interop` | `tooling` |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| [01](../modules/01-fundamentos) | 5 | 5 | 1 | 4 | 6 | 1 |  |  |  |  |  | 3 | 1 |  | 1 |  |
| [15](../modules/15-ub-seguridad) | 3 |  |  |  | 1 |  |  |  |  |  |  | 2 | 13 |  | 2 | 2 |
| [18](../modules/18-calidad) |  |  | 1 | 1 |  |  |  |  |  |  |  |  | 3 | 1 |  | 11 |
| [02](../modules/02-compile-time) | 1 |  | 10 | 3 |  |  |  |  |  |  |  | 1 | 2 | 1 |  | 1 |
| [03](../modules/03-templates-concepts) |  |  | 2 | 13 | 2 |  |  | 1 |  |  |  | 2 |  | 1 |  |  |
| [04](../modules/04-tipos-vocabulario) | 2 |  |  |  | 9 | 1 | 1 | 1 |  |  |  | 2 | 2 |  |  |  |
| [05](../modules/05-gestion-errores) | 2 |  |  |  | 2 | 12 | 1 |  |  |  |  | 1 | 1 |  | 1 |  |
| [08](../modules/08-clases-lenguaje) | 1 |  |  | 1 | 6 |  |  |  |  | 1 |  | 2 |  |  |  | 1 |
| [06](../modules/06-lambdas) | 2 | 1 | 1 | 2 |  |  | 10 |  |  |  |  | 1 | 1 |  | 1 |  |
| [07](../modules/07-ranges) | 1 |  |  | 3 |  |  | 1 | 8 | 1 |  |  | 1 | 1 |  |  | 1 |
| [16](../modules/16-diseno-apis) |  | 2 |  | 2 | 5 |  | 1 |  |  |  |  | 1 | 2 | 4 | 3 | 2 |
| [09](../modules/09-concurrencia) | 2 |  |  |  |  |  |  |  | 7 | 4 | 1 | 2 | 2 |  |  | 1 |
| [17](../modules/17-rendimiento) | 1 |  |  |  | 1 |  |  | 1 | 1 |  |  | 10 |  |  |  | 2 |
| [13](../modules/13-embedded) | 4 |  | 1 |  | 3 | 1 |  |  |  | 1 |  | 3 | 4 | 1 |  | 2 |
| [11](../modules/11-format-chrono-io) |  |  |  | 1 | 4 |  |  |  |  |  |  | 3 | 1 | 1 |  |  |
| [10](../modules/10-coroutines) | 2 |  |  |  |  |  |  | 1 |  |  | 6 | 1 | 1 |  |  |  |
| [12](../modules/12-modulos) |  |  |  |  |  |  |  |  |  |  |  |  | 1 | 8 |  | 2 |
| [14](../modules/14-cpp26) |  |  | 2 | 2 | 1 | 1 |  |  | 2 | 1 | 1 | 1 | 3 |  | 1 |  |

## Índice por tag

<a id="lifetime"></a>
### `@lifetime`

- [01](../modules/01-fundamentos) §3.5 — Estado "movido": válido pero no especificado; diseñar el estado vacío
- [01](../modules/01-fundamentos) §4.1 — Reglas de generación implícita (tabla de Hinnant) y Rule of Zero/Five
- [01](../modules/01-fundamentos) §4.3 — `std::unique_ptr` con *deleters* propios [11]   _sin heap si envuelve handles estáticos_
- [01](../modules/01-fundamentos) §4.4 — `shared_ptr`/`weak_ptr`, `make_shared`, coste del bloque de control    _heap y atomics_
- [01](../modules/01-fundamentos) §4.5 — `make_unique` [14], `make_unique_for_overwrite` [20], `out_ptr`/`inout_ptr` [23]
- [15](../modules/15-ub-seguridad) §1.1 — Objeto, almacenamiento, tiempo de vida; inicio y fin de vida
- [15](../modules/15-ub-seguridad) §1.2 — Creación implícita de objetos [20], `start_lifetime_as` [23]
- [15](../modules/15-ub-seguridad) §3.1 — Dangling: referencias, vistas, iteradores, lambdas, coroutines
- [02](../modules/02-compile-time) §3.3 — `constinit` [20] y el *static initialization order fiasco*   _inicialización en `.data`, sin constructores en arranque_
- [04](../modules/04-tipos-vocabulario) §4.1 — `string_view` [17] y *dangling*
- [04](../modules/04-tipos-vocabulario) §4.2 — `span` [20], extensión estática/dinámica, `as_bytes`
- [05](../modules/05-gestion-errores) §2 — Garantías de excepción: nothrow, fuerte, básica; copy-and-swap
- [05](../modules/05-gestion-errores) §3 — RAII para limpieza: *scope guards* (`scope_exit`), `unique_resource`
- [08](../modules/08-clases-lenguaje) §2 — `if`/`switch` con inicializador [17], range-`for` con inicializador [20]
- [06](../modules/06-lambdas) §2.2 — `constexpr` lambdas, captura de `*this` [17]
- [06](../modules/06-lambdas) §3 — Riesgos de tiempo de vida: capturas por referencia que sobreviven al ámbito
- [07](../modules/07-ranges) §1.3 — Invalidación de iteradores por contenedor
- [09](../modules/09-concurrencia) §4.1 — `thread`, `jthread`/`stop_token` [20], `thread_local` [11]    _bare-metal sin hilos; usar el RTOS_
- [09](../modules/09-concurrencia) §6 — RTOS: RAII sobre FreeRTOS, requisitos `Lockable` para `lock_guard`, SPSC ISR→tarea
- [17](../modules/17-rendimiento) §2.3 — Asignaciones: coste, pools, arenas, `pmr`, *small buffer optimization*
- [13](../modules/13-embedded) §1.4 — Arranque: `.init_array`, constructores globales, `constinit`
- [13](../modules/13-embedded) §2.1 — `std::pmr` [17] sobre buffers estáticos
- [13](../modules/13-embedded) §2.2 — Allocators y pools propios
- [13](../modules/13-embedded) §2.3 — *Placement new*, `launder` [17], `construct_at` [20], `start_lifetime_as` [23]
- [10](../modules/10-coroutines) §1 — Conceptos: stackless frente a hilos y *fibers*; `co_await`/`co_yield`/`co_return`; el frame
- [10](../modules/10-coroutines) §3 — Tiempo de vida: referencias en parámetros que no sobreviven a la suspensión

<a id="value-sem"></a>
### `@value-sem`

- [01](../modules/01-fundamentos) §2.3 — Trampas: proxies (`vector<bool>`), `auto x{1}` [11 vs 17], referencias perdidas
- [01](../modules/01-fundamentos) §3.1 — Categorías de valor: lvalue, prvalue, xvalue [11/17]
- [01](../modules/01-fundamentos) §3.2 — Forwarding references, colapso de referencias, `std::forward` [11]
- [01](../modules/01-fundamentos) §3.3 — *Copy elision* garantizada [17], NRVO, movimiento implícito al retornar [20/23]
- [01](../modules/01-fundamentos) §4.1 — Reglas de generación implícita (tabla de Hinnant) y Rule of Zero/Five
- [06](../modules/06-lambdas) §2.1 — *Init-capture* y lambdas genéricas [14]
- [16](../modules/16-diseno-apis) §1 — Semántica de valor frente a referencia en el diseño de APIs
- [16](../modules/16-diseno-apis) §3.1 — Parámetros: por valor, `const&`, `&&`, vistas; devolución de valores

<a id="compile-time"></a>
### `@compile-time`

- [01](../modules/01-fundamentos) §5.4 — `static_assert` [11/17], range-`for` [11/20]
- [18](../modules/18-calidad) §3.3 — `static_assert` como test en compilación
- [02](../modules/02-compile-time) §1.1 — Una expresión [11] → bucles y variables [14] → lambdas [17]
- [02](../modules/02-compile-time) §1.2 — `try`, `virtual`, `union`, asignación transitoria, `vector`/`string` constexpr [20]   _la memoria transitoria no llega al binario_
- [02](../modules/02-compile-time) §1.3 — `static` en funciones constexpr, tipos no literales [23], `<cmath>` constexpr [23/26]
- [02](../modules/02-compile-time) §1.4 — Límites: pasos de evaluación, diagnóstico de UB en constexpr como herramienta
- [02](../modules/02-compile-time) §2 — `if constexpr` [17] y ramas descartadas
- [02](../modules/02-compile-time) §3.1 — `consteval` [20], propagación [23]
- [02](../modules/02-compile-time) §3.2 — `if consteval` [23] vs `std::is_constant_evaluated()` [20]
- [02](../modules/02-compile-time) §4.1 — Variable templates [14], variables `inline` [17]
- [02](../modules/02-compile-time) §4.2 — NTTP `auto` [17], NTTP de clase y flotantes [20]
- [02](../modules/02-compile-time) §5.2 — `std::index_sequence` [14] y expansión de tablas
- [03](../modules/03-templates-concepts) §2.1 — Packs, `sizeof...` [11], fold expressions [17]
- [03](../modules/03-templates-concepts) §6 — Type traits: `_t` [14], `_v` [17], `conjunction` [17], `remove_cvref`, `type_identity` [20]
- [06](../modules/06-lambdas) §2.2 — `constexpr` lambdas, captura de `*this` [17]
- [13](../modules/13-embedded) §3.1 — `<bit>` [20], `byteswap` [23]
- [14](../modules/14-cpp26) §1 — Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas    _todo en compilación_
- [14](../modules/14-cpp26) §1.1 — Casos de uso: `enum` ↔ string, serialización, mapas de registros, bindings

<a id="generic"></a>
### `@generic`

- [01](../modules/01-fundamentos) §1.2 — `std::initializer_list` y su prioridad en la resolución de sobrecarga [11]
- [01](../modules/01-fundamentos) §2.1 — Reglas de deducción de templates como base de `auto` [11]
- [01](../modules/01-fundamentos) §2.2 — `auto`, `decltype`, `decltype(auto)`, *trailing return* [11/14]
- [01](../modules/01-fundamentos) §3.2 — Forwarding references, colapso de referencias, `std::forward` [11]
- [18](../modules/18-calidad) §3.2 — Diseño testable: dependencias inyectadas, HAL simulada en host
- [02](../modules/02-compile-time) §2 — `if constexpr` [17] y ramas descartadas
- [02](../modules/02-compile-time) §4.2 — NTTP `auto` [17], NTTP de clase y flotantes [20]
- [02](../modules/02-compile-time) §5.2 — `std::index_sequence` [14] y expansión de tablas
- [03](../modules/03-templates-concepts) §1.1 — Lookup en dos fases, nombres dependientes, `typename` y `template` como desambiguadores
- [03](../modules/03-templates-concepts) §1.2 — ADL y puntos de personalización (`swap`, *niebloids*, CPOs)
- [03](../modules/03-templates-concepts) §1.3 — Especialización total y parcial, sobrecarga frente a especialización
- [03](../modules/03-templates-concepts) §2.1 — Packs, `sizeof...` [11], fold expressions [17]
- [03](../modules/03-templates-concepts) §2.2 — Expansión en lambdas y `using` [17/20], pack indexing [26]
- [03](../modules/03-templates-concepts) §3 — CTAD [17], guías de deducción, CTAD para agregados y alias [20]
- [03](../modules/03-templates-concepts) §4.1 — `enable_if`, `void_t`, *detection idiom* [11/17]: leerlo en código existente
- [03](../modules/03-templates-concepts) §5.1 — `requires` (cláusulas y expresiones), requisitos simples, de tipo, compuestos y anidados
- [03](../modules/03-templates-concepts) §5.2 — Sintaxis abreviada y parámetros `auto`
- [03](../modules/03-templates-concepts) §5.3 — Subsunción y ordenación de sobrecargas
- [03](../modules/03-templates-concepts) §5.4 — `<concepts>` estándar y concepts de iteradores/ranges
- [03](../modules/03-templates-concepts) §5.5 — Concepts como interfaz de drivers: polimorfismo estático sin vtable
- [03](../modules/03-templates-concepts) §6 — Type traits: `_t` [14], `_v` [17], `conjunction` [17], `remove_cvref`, `type_identity` [20]
- [08](../modules/08-clases-lenguaje) §5 — *Deducing this* [23]: sobrecargas const/&&, CRTP sin CRTP, lambdas recursivas
- [06](../modules/06-lambdas) §2.3 — Parámetros template, lambdas sin estado construibles, en contexto no evaluado [20]
- [06](../modules/06-lambdas) §4.4 — `invoke` [17], `invoke_r` [23], `bind_front` [20], `bind_back` [23]
- [07](../modules/07-ranges) §1.1 — Categorías, `iterator_traits`, iteradores contiguos [20]
- [07](../modules/07-ranges) §1.2 — Escribir un iterador y un centinela propios
- [07](../modules/07-ranges) §3 — Ranges [20]: centinelas, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges*
- [16](../modules/16-diseno-apis) §2.2 — Estático (templates/concepts, CRTP, deducing this)
- [16](../modules/16-diseno-apis) §3.3 — Inyección de dependencias con concepts para testabilidad
- [11](../modules/11-format-chrono-io) §1.2 — `std::formatter` propio
- [14](../modules/14-cpp26) §1 — Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas    _todo en compilación_
- [14](../modules/14-cpp26) §5 — Lenguaje: pack indexing, `#embed`, placeholder `_`, `= delete("motivo")`, comportamiento erróneo para no inicializadas

<a id="type-design"></a>
### `@type-design`

- [01](../modules/01-fundamentos) §1.1 — Llaves, *narrowing* y *most vexing parse* [11]
- [01](../modules/01-fundamentos) §1.3 — NSDMI [11/14], agregados [11→20], agregados con paréntesis [20]
- [01](../modules/01-fundamentos) §4.2 — `= default`, `= delete`, constructores `explicit`, delegados y heredados [11]
- [01](../modules/01-fundamentos) §5.1 — `enum class`, tipo subyacente [11], `using enum` [20], `to_underlying` [23]
- [01](../modules/01-fundamentos) §5.2 — `nullptr`, `override`/`final`, alias con `using` [11]
- [01](../modules/01-fundamentos) §5.3 — Raw strings, UDLs [11], literales binarios y separador `'` [14]   _UDLs para unidades físicas_
- [15](../modules/15-ub-seguridad) §1.4 — Tipos trivialmente copiables, *standard layout*, implicit-lifetime types
- [03](../modules/03-templates-concepts) §3 — CTAD [17], guías de deducción, CTAD para agregados y alias [20]
- [03](../modules/03-templates-concepts) §5.1 — `requires` (cláusulas y expresiones), requisitos simples, de tipo, compuestos y anidados
- [04](../modules/04-tipos-vocabulario) §1 — `std::optional` [17], monádico [23], `optional<T&>` [26]
- [04](../modules/04-tipos-vocabulario) §2.1 — `visit`, patrón *overloaded*, `get_if`, `valueless_by_exception`
- [04](../modules/04-tipos-vocabulario) §2.2 — Máquinas de estado con `variant`
- [04](../modules/04-tipos-vocabulario) §3 — `std::any` [17]   _heap y RTTI_
- [04](../modules/04-tipos-vocabulario) §4.2 — `span` [20], extensión estática/dinámica, `as_bytes`
- [04](../modules/04-tipos-vocabulario) §4.3 — `mdspan` [23]
- [04](../modules/04-tipos-vocabulario) §5.1 — `array`, `to_array` [20], `tuple`, `apply` [17], `byte` [17]
- [04](../modules/04-tipos-vocabulario) §5.3 — `inplace_vector` [26]
- [04](../modules/04-tipos-vocabulario) §6 — Tipos fuertes (*strong typedefs*): unidades, IDs y evitar argumentos intercambiables
- [05](../modules/05-gestion-errores) §4.1 — `unexpected`, acceso, `value_or`
- [05](../modules/05-gestion-errores) §4.3 — `expected<void, E>` y diseño del tipo de error
- [08](../modules/08-clases-lenguaje) §1 — Structured bindings [17], tipos tuple-like, con capturas [20], como condición [26]
- [08](../modules/08-clases-lenguaje) §3 — Comparaciones: `<=>` [20], categorías de ordenación, `==` por defecto, reescritura
- [08](../modules/08-clases-lenguaje) §4 — Designated initializers [20] y configuración de periféricos
- [08](../modules/08-clases-lenguaje) §5 — *Deducing this* [23]: sobrecargas const/&&, CRTP sin CRTP, lambdas recursivas
- [08](../modules/08-clases-lenguaje) §6 — Polimorfismo dinámico: vtables, destructores virtuales, *slicing*, `final` para devirtualizar    _vtables en flash; evitar RTTI_
- [08](../modules/08-clases-lenguaje) §8 — Otros: `explicit(bool)` [20], `char8_t` [20], `auto(x)` [23], `operator[]` multidimensional [23]
- [16](../modules/16-diseno-apis) §1 — Semántica de valor frente a referencia en el diseño de APIs
- [16](../modules/16-diseno-apis) §2.1 — Dinámico (virtual)   _vtables, sin RTTI_
- [16](../modules/16-diseno-apis) §2.3 — Cerrado (`std::variant`)
- [16](../modules/16-diseno-apis) §2.4 — *Type erasure* (estilo `std::function`, Sean Parent)    _sin heap con SBO fijo_
- [16](../modules/16-diseno-apis) §3.2 — Invariantes, `explicit`, tipos fuertes, difícil de usar mal
- [17](../modules/17-rendimiento) §2.2 — AoS frente a SoA, diseño orientado a datos
- [13](../modules/13-embedded) §2.4 — ETL, `inplace_vector` [26]
- [13](../modules/13-embedded) §3.2 — MMIO tipado: `volatile` + templates + máscaras `constexpr`
- [13](../modules/13-embedded) §5 — Aritmética: punto fijo, enteros de ancho fijo, promociones y overflow
- [11](../modules/11-format-chrono-io) §1.1 — `format`, `format_to_n` [20], especificadores, comprobación en compilación    _coste en flash; `format_to_n` evita heap_
- [11](../modules/11-format-chrono-io) §1.3 — `print` [23], formato de rangos [23]   _depende de stdio_
- [11](../modules/11-format-chrono-io) §4 — Texto y Unicode: `char8_t` [20], UTF-8 como codificación por defecto, por qué evitar `std::regex`
- [11](../modules/11-format-chrono-io) §5 — `<chrono>`: duraciones, relojes [11], literales [14], calendario y zonas [20]   _duraciones y relojes propios; zonas horarias no_
- [14](../modules/14-cpp26) §4.1 — `inplace_vector`, `function_ref`, `optional<T&>`, aritmética saturada

<a id="errors"></a>
### `@errors`

- [01](../modules/01-fundamentos) §3.4 — `noexcept` en movimiento y su efecto en contenedores
- [04](../modules/04-tipos-vocabulario) §1 — `std::optional` [17], monádico [23], `optional<T&>` [26]
- [05](../modules/05-gestion-errores) §1 — Panorama: códigos de retorno, `errno`, excepciones, tipos resultado
- [05](../modules/05-gestion-errores) §1.1 — Coste real de las excepciones: tablas de unwind, tamaño de código, determinismo   _bare-metal suele compilar con `-fno-exceptions`_
- [05](../modules/05-gestion-errores) §2 — Garantías de excepción: nothrow, fuerte, básica; copy-and-swap
- [05](../modules/05-gestion-errores) §3 — RAII para limpieza: *scope guards* (`scope_exit`), `unique_resource`
- [05](../modules/05-gestion-errores) §4.1 — `unexpected`, acceso, `value_or`
- [05](../modules/05-gestion-errores) §4.2 — `and_then`, `transform`, `or_else`, `transform_error`
- [05](../modules/05-gestion-errores) §4.3 — `expected<void, E>` y diseño del tipo de error
- [05](../modules/05-gestion-errores) §4.4 — `value()` lanza `bad_expected_access`: usar `*`/`has_value` sin excepciones
- [05](../modules/05-gestion-errores) §5 — `std::error_code` / `error_category` [11]    _categorías con strings, revisar tamaño_
- [05](../modules/05-gestion-errores) §6.1 — `[[nodiscard]]` [17/20], `noexcept` [11/17], `[[noreturn]]`, `std::unreachable` [23]
- [05](../modules/05-gestion-errores) §6.2 — Política de `noexcept`: cuándo marcar, efecto en `std::terminate`
- [05](../modules/05-gestion-errores) §7 — Precondiciones: `assert`, `source_location` [20], contracts [26]
- [13](../modules/13-embedded) §1.2 — `-fno-exceptions`, `-fno-rtti`, `-fno-threadsafe-statics`: qué deja de funcionar
- [14](../modules/14-cpp26) §2 — Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler

<a id="functional"></a>
### `@functional`

- [04](../modules/04-tipos-vocabulario) §2.1 — `visit`, patrón *overloaded*, `get_if`, `valueless_by_exception`
- [05](../modules/05-gestion-errores) §4.2 — `and_then`, `transform`, `or_else`, `transform_error`
- [06](../modules/06-lambdas) §1 — Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función
- [06](../modules/06-lambdas) §2.1 — *Init-capture* y lambdas genéricas [14]
- [06](../modules/06-lambdas) §2.2 — `constexpr` lambdas, captura de `*this` [17]
- [06](../modules/06-lambdas) §2.3 — Parámetros template, lambdas sin estado construibles, en contexto no evaluado [20]
- [06](../modules/06-lambdas) §2.4 — Lambdas `static` y recursivas con *deducing this* [23]
- [06](../modules/06-lambdas) §4.1 — `std::function` [11]: borrado de tipo y SBO    _heap si el cierre no cabe en el SBO_
- [06](../modules/06-lambdas) §4.2 — `move_only_function` [23], `copyable_function` [26]
- [06](../modules/06-lambdas) §4.3 — `function_ref` [26]
- [06](../modules/06-lambdas) §4.4 — `invoke` [17], `invoke_r` [23], `bind_front` [20], `bind_back` [23]
- [06](../modules/06-lambdas) §5 — Patrones: IIFE, *overloaded*, callbacks de ISR con templates o `function_ref`
- [07](../modules/07-ranges) §4 — Views [20]: `filter`, `transform`, `take`, `split`, `join`, `iota`; pereza; views propias    _sin heap; revisar tamaño con `-Os`_
- [16](../modules/16-diseno-apis) §2.4 — *Type erasure* (estilo `std::function`, Sean Parent)    _sin heap con SBO fijo_

<a id="iteration"></a>
### `@iteration`

- [03](../modules/03-templates-concepts) §5.4 — `<concepts>` estándar y concepts de iteradores/ranges
- [04](../modules/04-tipos-vocabulario) §5.4 — `try_emplace` [17], `contains`, `erase_if`, `ssize` [20]
- [07](../modules/07-ranges) §1.1 — Categorías, `iterator_traits`, iteradores contiguos [20]
- [07](../modules/07-ranges) §1.2 — Escribir un iterador y un centinela propios
- [07](../modules/07-ranges) §1.3 — Invalidación de iteradores por contenedor
- [07](../modules/07-ranges) §2 — Algoritmos: `all_of`, `iota` [11], `clamp`, `reduce` [17], `midpoint`, `shift_left` [20]
- [07](../modules/07-ranges) §2.1 — Políticas de ejecución paralela [17]    _requiere TBB o hilos_
- [07](../modules/07-ranges) §3 — Ranges [20]: centinelas, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges*
- [07](../modules/07-ranges) §4 — Views [20]: `filter`, `transform`, `take`, `split`, `join`, `iota`; pereza; views propias    _sin heap; revisar tamaño con `-Os`_
- [07](../modules/07-ranges) §5 — C++23: `ranges::to`, `zip`, `enumerate`, `chunk`, `slide`, `fold_left`, `contains`   _`ranges::to` asigna memoria_
- [17](../modules/17-rendimiento) §2.4 — Contenedores: `vector` como opción por defecto, `unordered_map` frente a tablas abiertas
- [10](../modules/10-coroutines) §4 — Tipos de alto nivel: `generator<T>` propio, `std::generator` [23], `task<T>`

<a id="concurrency"></a>
### `@concurrency`

- [07](../modules/07-ranges) §2.1 — Políticas de ejecución paralela [17]    _requiere TBB o hilos_
- [09](../modules/09-concurrencia) §2.3 — `atomic_ref`, `wait`/`notify`, `atomic<shared_ptr>` [20], fences
- [09](../modules/09-concurrencia) §3 — Problemas clásicos: deadlock, livelock, inversión de prioridad, *false sharing* (`hardware_destructive_interference_size` [17]), ABA
- [09](../modules/09-concurrencia) §4.1 — `thread`, `jthread`/`stop_token` [20], `thread_local` [11]    _bare-metal sin hilos; usar el RTOS_
- [09](../modules/09-concurrencia) §4.2 — `mutex`, `scoped_lock` [17], `shared_mutex` [17], `condition_variable`   _vía primitivas del RTOS_
- [09](../modules/09-concurrencia) §4.3 — `counting_semaphore`, `latch`, `barrier` [20], `call_once`
- [09](../modules/09-concurrencia) §5 — Tareas: `async`/`future` [11] y sus límites, `std::execution` [26]
- [09](../modules/09-concurrencia) §6 — RTOS: RAII sobre FreeRTOS, requisitos `Lockable` para `lock_guard`, SPSC ISR→tarea
- [17](../modules/17-rendimiento) §6 — Concurrencia: false sharing, contención, lock-free frente a mutex
- [14](../modules/14-cpp26) §3 — `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all`
- [14](../modules/14-cpp26) §4.2 — Hazard pointers, RCU

<a id="memory-model"></a>
### `@memory-model`

- [08](../modules/08-clases-lenguaje) §9 — `volatile`: usos deprecados [20] y revertidos [23]; solo para MMIO
- [09](../modules/09-concurrencia) §1 — Modelo de memoria [11]: *happens-before*, *synchronizes-with*, data races = UB
- [09](../modules/09-concurrencia) §2.1 — Órdenes de memoria y cuándo basta `relaxed`
- [09](../modules/09-concurrencia) §2.2 — Lock-free en Cortex-M0 frente a M3/M4/M7, `is_always_lock_free` [17]   _M0 no tiene LDREX/STREX_
- [09](../modules/09-concurrencia) §2.3 — `atomic_ref`, `wait`/`notify`, `atomic<shared_ptr>` [20], fences
- [13](../modules/13-embedded) §3.2 — MMIO tipado: `volatile` + templates + máscaras `constexpr`
- [14](../modules/14-cpp26) §4.2 — Hazard pointers, RCU

<a id="async"></a>
### `@async`

- [09](../modules/09-concurrencia) §5 — Tareas: `async`/`future` [11] y sus límites, `std::execution` [26]
- [10](../modules/10-coroutines) §1 — Conceptos: stackless frente a hilos y *fibers*; `co_await`/`co_yield`/`co_return`; el frame
- [10](../modules/10-coroutines) §2 — Maquinaria [20]: `promise_type`, `coroutine_handle`, awaitables, transferencia simétrica
- [10](../modules/10-coroutines) §3 — Tiempo de vida: referencias en parámetros que no sobreviven a la suspensión
- [10](../modules/10-coroutines) §4 — Tipos de alto nivel: `generator<T>` propio, `std::generator` [23], `task<T>`
- [10](../modules/10-coroutines) §5.1 — `operator new` en `promise_type`, pools estáticos, HALO    _el frame usa heap salvo que se controle_
- [10](../modules/10-coroutines) §5.2 — Protocolos con timeouts y scheduler cooperativo
- [14](../modules/14-cpp26) §3 — `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all`

<a id="performance"></a>
### `@performance`

- [01](../modules/01-fundamentos) §3.3 — *Copy elision* garantizada [17], NRVO, movimiento implícito al retornar [20/23]
- [01](../modules/01-fundamentos) §3.4 — `noexcept` en movimiento y su efecto en contenedores
- [01](../modules/01-fundamentos) §4.4 — `shared_ptr`/`weak_ptr`, `make_shared`, coste del bloque de control    _heap y atomics_
- [15](../modules/15-ub-seguridad) §1.3 — Alineación, padding, `alignas`, `alignof`, tamaños de tipos
- [15](../modules/15-ub-seguridad) §2.3 — Cómo el optimizador explota el UB (eliminación de comprobaciones)
- [02](../modules/02-compile-time) §6 — Coste de compilación: instanciaciones, `-ftime-trace`, cuándo calcular en build (script) en vez de en C++
- [03](../modules/03-templates-concepts) §5.5 — Concepts como interfaz de drivers: polimorfismo estático sin vtable
- [03](../modules/03-templates-concepts) §7 — Coste: explosión de instanciaciones y tamaño de código (*code bloat*), técnicas de *thin template*   _vigilar flash con muchas instanciaciones_
- [04](../modules/04-tipos-vocabulario) §2.3 — Coste: tamaño = mayor alternativa + índice; `visit` y tablas de salto
- [04](../modules/04-tipos-vocabulario) §5.2 — `flat_map`/`flat_set` [23]   _contenedor subyacente con heap_
- [05](../modules/05-gestion-errores) §1 — Panorama: códigos de retorno, `errno`, excepciones, tipos resultado
- [08](../modules/08-clases-lenguaje) §6 — Polimorfismo dinámico: vtables, destructores virtuales, *slicing*, `final` para devirtualizar    _vtables en flash; evitar RTTI_
- [08](../modules/08-clases-lenguaje) §7 — Atributos: `[[maybe_unused]]`, `[[fallthrough]]` [17], `[[likely]]`, `[[no_unique_address]]` [20], `[[assume]]` [23]
- [06](../modules/06-lambdas) §4.1 — `std::function` [11]: borrado de tipo y SBO    _heap si el cierre no cabe en el SBO_
- [07](../modules/07-ranges) §6 — Coste: tiempo de compilación, depuración y ensamblador frente a bucles manuales
- [16](../modules/16-diseno-apis) §3.1 — Parámetros: por valor, `const&`, `&&`, vistas; devolución de valores
- [09](../modules/09-concurrencia) §2.1 — Órdenes de memoria y cuándo basta `relaxed`
- [09](../modules/09-concurrencia) §3 — Problemas clásicos: deadlock, livelock, inversión de prioridad, *false sharing* (`hardware_destructive_interference_size` [17]), ABA
- [17](../modules/17-rendimiento) §1 — Medir: benchmarks fiables (Google Benchmark), `perf`, flame graphs, contadores de hardware
- [17](../modules/17-rendimiento) §2.1 — Jerarquía de caché, localidad, prefetching   _MCUs sin caché: importa el acceso a flash_
- [17](../modules/17-rendimiento) §2.2 — AoS frente a SoA, diseño orientado a datos
- [17](../modules/17-rendimiento) §2.3 — Asignaciones: coste, pools, arenas, `pmr`, *small buffer optimization*
- [17](../modules/17-rendimiento) §2.4 — Contenedores: `vector` como opción por defecto, `unordered_map` frente a tablas abiertas
- [17](../modules/17-rendimiento) §3 — Coste de abstracciones: inlining, devirtualización, `std::function`, excepciones, RTTI
- [17](../modules/17-rendimiento) §4 — Compilador: `-O2`/`-O3`/`-Os`, LTO, PGO, vectorización, `[[likely]]`, `[[assume]]`    _PGO poco práctico en target_
- [17](../modules/17-rendimiento) §5 — Ramas y predicción, código sin ramas, aritmética de punto fijo
- [17](../modules/17-rendimiento) §6 — Concurrencia: false sharing, contención, lock-free frente a mutex
- [17](../modules/17-rendimiento) §7 — `std::simd` [26] e intrínsecos (NEON, SSE/AVX)   _NEON en Cortex-A; Helium en M55_
- [13](../modules/13-embedded) §1.3 — newlib/newlib-nano, partes de la STL que arrastran heap o locale
- [13](../modules/13-embedded) §2.1 — `std::pmr` [17] sobre buffers estáticos
- [13](../modules/13-embedded) §4 — Tamaño y rendimiento: `size`, `.map`, Bloaty, LTO, `--gc-sections`, coste de templates y virtual
- [11](../modules/11-format-chrono-io) §2 — `to_chars`/`from_chars` [17], constexpr [23]
- [11](../modules/11-format-chrono-io) §3 — Strings: SSO, `starts_with` [20], `contains` [23], `resize_and_overwrite` [23], literales   _heap fuera del SSO_
- [11](../modules/11-format-chrono-io) §4 — Texto y Unicode: `char8_t` [20], UTF-8 como codificación por defecto, por qué evitar `std::regex`
- [10](../modules/10-coroutines) §5.1 — `operator new` en `promise_type`, pools estáticos, HALO    _el frame usa heap salvo que se controle_
- [14](../modules/14-cpp26) §4.3 — `std::simd`, `std::linalg`

<a id="safety"></a>
### `@safety`

- [01](../modules/01-fundamentos) §1.4 — Inicialización por defecto, de valor y cero; variables sin inicializar
- [15](../modules/15-ub-seguridad) §1.1 — Objeto, almacenamiento, tiempo de vida; inicio y fin de vida
- [15](../modules/15-ub-seguridad) §1.2 — Creación implícita de objetos [20], `start_lifetime_as` [23]
- [15](../modules/15-ub-seguridad) §2.1 — Catálogo: overflow con signo, desplazamientos, nulos, fuera de límites, data races, uso tras liberar
- [15](../modules/15-ub-seguridad) §2.2 — *Strict aliasing* y `bit_cast`/`memcpy` como alternativas
- [15](../modules/15-ub-seguridad) §2.3 — Cómo el optimizador explota el UB (eliminación de comprobaciones)
- [15](../modules/15-ub-seguridad) §2.4 — Comportamiento no especificado e implementation-defined
- [15](../modules/15-ub-seguridad) §2.5 — Comportamiento erróneo [26]
- [15](../modules/15-ub-seguridad) §3.1 — Dangling: referencias, vistas, iteradores, lambdas, coroutines
- [15](../modules/15-ub-seguridad) §3.2 — Bounds checking: `.at()`, `span`, modos de hardening (`_GLIBCXX_ASSERTIONS`, libc++ hardening)   _coste de tamaño; activar en debug_
- [15](../modules/15-ub-seguridad) §3.3 — Clang `-Wunsafe-buffer-usage`, `-Wdangling`, `[[clang::lifetimebound]]`
- [15](../modules/15-ub-seguridad) §3.4 — Perfiles de seguridad y lifetime analysis (propuestas)
- [15](../modules/15-ub-seguridad) §4 — Detección: ASan, UBSan, MSan, TSan, Valgrind; constexpr como detector de UB    _en host, no en target_
- [15](../modules/15-ub-seguridad) §5 — Contexto: C++ frente a Rust en Mozilla/Google; cuándo reescribir y cuándo endurecer
- [18](../modules/18-calidad) §4 — Sanitizers: ASan, UBSan, TSan, MSan; integración en CI
- [18](../modules/18-calidad) §5 — Fuzzing: libFuzzer, AFL++, OSS-Fuzz; fuzzing de parsers de protocolo    _en host sobre el mismo código_
- [18](../modules/18-calidad) §6 — Análisis estático: clang-tidy, cppcheck, `-Wall -Wextra`, análisis de flujo, MISRA
- [02](../modules/02-compile-time) §1.4 — Límites: pasos de evaluación, diagnóstico de UB en constexpr como herramienta
- [02](../modules/02-compile-time) §5.1 — `std::bit_cast` [20]
- [04](../modules/04-tipos-vocabulario) §4.1 — `string_view` [17] y *dangling*
- [04](../modules/04-tipos-vocabulario) §6 — Tipos fuertes (*strong typedefs*): unidades, IDs y evitar argumentos intercambiables
- [05](../modules/05-gestion-errores) §7 — Precondiciones: `assert`, `source_location` [20], contracts [26]
- [06](../modules/06-lambdas) §3 — Riesgos de tiempo de vida: capturas por referencia que sobreviven al ámbito
- [07](../modules/07-ranges) §1.3 — Invalidación de iteradores por contenedor
- [16](../modules/16-diseno-apis) §3.2 — Invariantes, `explicit`, tipos fuertes, difícil de usar mal
- [16](../modules/16-diseno-apis) §5.2 — Rust: `cxx`, `bindgen`, cbindgen; reparto de propiedad
- [09](../modules/09-concurrencia) §1 — Modelo de memoria [11]: *happens-before*, *synchronizes-with*, data races = UB
- [09](../modules/09-concurrencia) §7 — Detección: ThreadSanitizer, revisión de órdenes de memoria
- [13](../modules/13-embedded) §2.3 — *Placement new*, `launder` [17], `construct_at` [20], `start_lifetime_as` [23]
- [13](../modules/13-embedded) §3.3 — Bitfields frente a máscaras, *strict aliasing* y `bit_cast`
- [13](../modules/13-embedded) §5 — Aritmética: punto fijo, enteros de ancho fijo, promociones y overflow
- [13](../modules/13-embedded) §6 — Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines
- [11](../modules/11-format-chrono-io) §1.1 — `format`, `format_to_n` [20], especificadores, comprobación en compilación    _coste en flash; `format_to_n` evita heap_
- [10](../modules/10-coroutines) §3 — Tiempo de vida: referencias en parámetros que no sobreviven a la suspensión
- [12](../modules/12-modulos) §1.2 — ODR, `inline` (funciones y variables [17]), violaciones silenciosas
- [14](../modules/14-cpp26) §2 — Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler
- [14](../modules/14-cpp26) §4.4 — Hardening de la biblioteca estándar
- [14](../modules/14-cpp26) §5 — Lenguaje: pack indexing, `#embed`, placeholder `_`, `= delete("motivo")`, comportamiento erróneo para no inicializadas

<a id="abi"></a>
### `@abi`

- [18](../modules/18-calidad) §1 — CMake moderno: targets, propiedades `PUBLIC`/`PRIVATE`/`INTERFACE`, presets, toolchains, FetchContent
- [02](../modules/02-compile-time) §4.1 — Variable templates [14], variables `inline` [17]
- [03](../modules/03-templates-concepts) §1.2 — ADL y puntos de personalización (`swap`, *niebloids*, CPOs)
- [16](../modules/16-diseno-apis) §4.1 — Estabilidad de ABI, por qué el estándar no rompe `std::string`
- [16](../modules/16-diseno-apis) §4.2 — PIMPL, *fast PIMPL*, interfaces abstractas   _PIMPL implica heap salvo storage fijo_
- [16](../modules/16-diseno-apis) §4.3 — Visibilidad de símbolos, `-fvisibility=hidden`, versionado
- [16](../modules/16-diseno-apis) §5.1 — APIs en C: `extern "C"`, tipos opacos, propiedad entre fronteras
- [13](../modules/13-embedded) §1.1 — *Freestanding* y su ampliación [23/26]
- [11](../modules/11-format-chrono-io) §6 — Linux: `filesystem` [17], `spanstream` [23], iostreams frente a format
- [12](../modules/12-modulos) §1.1 — Unidades de traducción, enlace interno/externo, `static` y namespaces anónimos
- [12](../modules/12-modulos) §1.2 — ODR, `inline` (funciones y variables [17]), violaciones silenciosas
- [12](../modules/12-modulos) §1.3 — Coste de los headers: tiempos de build, *include-what-you-use*, *precompiled headers*
- [12](../modules/12-modulos) §2.1 — `export module`, `import`, particiones, *global module fragment*, *header units*
- [12](../modules/12-modulos) §2.2 — `import std;` [23]   _soporte de toolchain cruzado_
- [12](../modules/12-modulos) §2.3 — *Module linkage*, macros que no cruzan fronteras
- [12](../modules/12-modulos) §3 — Herramientas: CMake `FILE_SET CXX_MODULES` + Ninja, soporte en GCC/Clang/MSVC
- [12](../modules/12-modulos) §4 — Sin módulos: namespaces `inline` [11] para versionado, anidados [17], `__has_include` [17], macros `__cpp_*` [20]

<a id="interop"></a>
### `@interop`

- [01](../modules/01-fundamentos) §4.5 — `make_unique` [14], `make_unique_for_overwrite` [20], `out_ptr`/`inout_ptr` [23]
- [15](../modules/15-ub-seguridad) §1.4 — Tipos trivialmente copiables, *standard layout*, implicit-lifetime types
- [15](../modules/15-ub-seguridad) §5 — Contexto: C++ frente a Rust en Mozilla/Google; cuándo reescribir y cuándo endurecer
- [05](../modules/05-gestion-errores) §5 — `std::error_code` / `error_category` [11]    _categorías con strings, revisar tamaño_
- [06](../modules/06-lambdas) §1 — Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función
- [16](../modules/16-diseno-apis) §5.1 — APIs en C: `extern "C"`, tipos opacos, propiedad entre fronteras
- [16](../modules/16-diseno-apis) §5.2 — Rust: `cxx`, `bindgen`, cbindgen; reparto de propiedad
- [16](../modules/16-diseno-apis) §5.3 — Python: pybind11/nanobind para herramientas de test
- [14](../modules/14-cpp26) §1.1 — Casos de uso: `enum` ↔ string, serialización, mapas de registros, bindings

<a id="tooling"></a>
### `@tooling`

- [15](../modules/15-ub-seguridad) §3.3 — Clang `-Wunsafe-buffer-usage`, `-Wdangling`, `[[clang::lifetimebound]]`
- [15](../modules/15-ub-seguridad) §4 — Detección: ASan, UBSan, MSan, TSan, Valgrind; constexpr como detector de UB    _en host, no en target_
- [18](../modules/18-calidad) §1 — CMake moderno: targets, propiedades `PUBLIC`/`PRIVATE`/`INTERFACE`, presets, toolchains, FetchContent
- [18](../modules/18-calidad) §2 — Gestión de dependencias: vcpkg, Conan, CPM
- [18](../modules/18-calidad) §3.1 — Frameworks: doctest, Catch2, GoogleTest; tests parametrizados
- [18](../modules/18-calidad) §3.2 — Diseño testable: dependencias inyectadas, HAL simulada en host
- [18](../modules/18-calidad) §3.3 — `static_assert` como test en compilación
- [18](../modules/18-calidad) §3.4 — Tests en hardware (HIL) y en emulador (QEMU, Renode)
- [18](../modules/18-calidad) §4 — Sanitizers: ASan, UBSan, TSan, MSan; integración en CI
- [18](../modules/18-calidad) §5 — Fuzzing: libFuzzer, AFL++, OSS-Fuzz; fuzzing de parsers de protocolo    _en host sobre el mismo código_
- [18](../modules/18-calidad) §6 — Análisis estático: clang-tidy, cppcheck, `-Wall -Wextra`, análisis de flujo, MISRA
- [18](../modules/18-calidad) §7 — Cobertura: gcov/llvm-cov, criterios útiles
- [18](../modules/18-calidad) §8 — Revisión de código y estilo: clang-format, Core Guidelines, guías de Google/Mozilla
- [02](../modules/02-compile-time) §6 — Coste de compilación: instanciaciones, `-ftime-trace`, cuándo calcular en build (script) en vez de en C++
- [08](../modules/08-clases-lenguaje) §10 — Preprocesador: `#elifdef` [23], `#embed` [26]   _`#embed` para blobs de firmware_
- [07](../modules/07-ranges) §6 — Coste: tiempo de compilación, depuración y ensamblador frente a bucles manuales
- [16](../modules/16-diseno-apis) §3.3 — Inyección de dependencias con concepts para testabilidad
- [16](../modules/16-diseno-apis) §5.3 — Python: pybind11/nanobind para herramientas de test
- [09](../modules/09-concurrencia) §7 — Detección: ThreadSanitizer, revisión de órdenes de memoria
- [17](../modules/17-rendimiento) §1 — Medir: benchmarks fiables (Google Benchmark), `perf`, flame graphs, contadores de hardware
- [17](../modules/17-rendimiento) §4 — Compilador: `-O2`/`-O3`/`-Os`, LTO, PGO, vectorización, `[[likely]]`, `[[assume]]`    _PGO poco práctico en target_
- [13](../modules/13-embedded) §4 — Tamaño y rendimiento: `size`, `.map`, Bloaty, LTO, `--gc-sections`, coste de templates y virtual
- [13](../modules/13-embedded) §6 — Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines
- [12](../modules/12-modulos) §1.3 — Coste de los headers: tiempos de build, *include-what-you-use*, *precompiled headers*
- [12](../modules/12-modulos) §3 — Herramientas: CMake `FILE_SET CXX_MODULES` + Ninja, soporte en GCC/Clang/MSVC

<a id="embok"></a>
### 🟢 `@emb:ok`

- [01](../modules/01-fundamentos) §1.1 — Llaves, *narrowing* y *most vexing parse* [11]
- [01](../modules/01-fundamentos) §1.3 — NSDMI [11/14], agregados [11→20], agregados con paréntesis [20]
- [01](../modules/01-fundamentos) §1.4 — Inicialización por defecto, de valor y cero; variables sin inicializar
- [01](../modules/01-fundamentos) §3.3 — *Copy elision* garantizada [17], NRVO, movimiento implícito al retornar [20/23]
- [01](../modules/01-fundamentos) §4.1 — Reglas de generación implícita (tabla de Hinnant) y Rule of Zero/Five
- [01](../modules/01-fundamentos) §4.3 — `std::unique_ptr` con *deleters* propios [11]   _sin heap si envuelve handles estáticos_
- [01](../modules/01-fundamentos) §5.1 — `enum class`, tipo subyacente [11], `using enum` [20], `to_underlying` [23]
- [01](../modules/01-fundamentos) §5.2 — `nullptr`, `override`/`final`, alias con `using` [11]
- [01](../modules/01-fundamentos) §5.3 — Raw strings, UDLs [11], literales binarios y separador `'` [14]   _UDLs para unidades físicas_
- [01](../modules/01-fundamentos) §5.4 — `static_assert` [11/17], range-`for` [11/20]
- [15](../modules/15-ub-seguridad) §1.2 — Creación implícita de objetos [20], `start_lifetime_as` [23]
- [15](../modules/15-ub-seguridad) §1.3 — Alineación, padding, `alignas`, `alignof`, tamaños de tipos
- [15](../modules/15-ub-seguridad) §2.2 — *Strict aliasing* y `bit_cast`/`memcpy` como alternativas
- [18](../modules/18-calidad) §1 — CMake moderno: targets, propiedades `PUBLIC`/`PRIVATE`/`INTERFACE`, presets, toolchains, FetchContent
- [18](../modules/18-calidad) §3.2 — Diseño testable: dependencias inyectadas, HAL simulada en host
- [18](../modules/18-calidad) §3.3 — `static_assert` como test en compilación
- [18](../modules/18-calidad) §3.4 — Tests en hardware (HIL) y en emulador (QEMU, Renode)
- [18](../modules/18-calidad) §5 — Fuzzing: libFuzzer, AFL++, OSS-Fuzz; fuzzing de parsers de protocolo    _en host sobre el mismo código_
- [18](../modules/18-calidad) §6 — Análisis estático: clang-tidy, cppcheck, `-Wall -Wextra`, análisis de flujo, MISRA
- [02](../modules/02-compile-time) §1.1 — Una expresión [11] → bucles y variables [14] → lambdas [17]
- [02](../modules/02-compile-time) §1.2 — `try`, `virtual`, `union`, asignación transitoria, `vector`/`string` constexpr [20]   _la memoria transitoria no llega al binario_
- [02](../modules/02-compile-time) §2 — `if constexpr` [17] y ramas descartadas
- [02](../modules/02-compile-time) §3.1 — `consteval` [20], propagación [23]
- [02](../modules/02-compile-time) §3.3 — `constinit` [20] y el *static initialization order fiasco*   _inicialización en `.data`, sin constructores en arranque_
- [02](../modules/02-compile-time) §4.1 — Variable templates [14], variables `inline` [17]
- [02](../modules/02-compile-time) §4.2 — NTTP `auto` [17], NTTP de clase y flotantes [20]
- [02](../modules/02-compile-time) §5.1 — `std::bit_cast` [20]
- [03](../modules/03-templates-concepts) §2.1 — Packs, `sizeof...` [11], fold expressions [17]
- [03](../modules/03-templates-concepts) §5.5 — Concepts como interfaz de drivers: polimorfismo estático sin vtable
- [04](../modules/04-tipos-vocabulario) §1 — `std::optional` [17], monádico [23], `optional<T&>` [26]
- [04](../modules/04-tipos-vocabulario) §2.1 — `visit`, patrón *overloaded*, `get_if`, `valueless_by_exception`
- [04](../modules/04-tipos-vocabulario) §2.2 — Máquinas de estado con `variant`
- [04](../modules/04-tipos-vocabulario) §4.1 — `string_view` [17] y *dangling*
- [04](../modules/04-tipos-vocabulario) §4.2 — `span` [20], extensión estática/dinámica, `as_bytes`
- [04](../modules/04-tipos-vocabulario) §4.3 — `mdspan` [23]
- [04](../modules/04-tipos-vocabulario) §5.1 — `array`, `to_array` [20], `tuple`, `apply` [17], `byte` [17]
- [04](../modules/04-tipos-vocabulario) §5.3 — `inplace_vector` [26]
- [04](../modules/04-tipos-vocabulario) §6 — Tipos fuertes (*strong typedefs*): unidades, IDs y evitar argumentos intercambiables
- [05](../modules/05-gestion-errores) §3 — RAII para limpieza: *scope guards* (`scope_exit`), `unique_resource`
- [05](../modules/05-gestion-errores) §4.1 — `unexpected`, acceso, `value_or`
- [05](../modules/05-gestion-errores) §4.2 — `and_then`, `transform`, `or_else`, `transform_error`
- [05](../modules/05-gestion-errores) §6.1 — `[[nodiscard]]` [17/20], `noexcept` [11/17], `[[noreturn]]`, `std::unreachable` [23]
- [05](../modules/05-gestion-errores) §7 — Precondiciones: `assert`, `source_location` [20], contracts [26]
- [08](../modules/08-clases-lenguaje) §1 — Structured bindings [17], tipos tuple-like, con capturas [20], como condición [26]
- [08](../modules/08-clases-lenguaje) §10 — Preprocesador: `#elifdef` [23], `#embed` [26]   _`#embed` para blobs de firmware_
- [08](../modules/08-clases-lenguaje) §2 — `if`/`switch` con inicializador [17], range-`for` con inicializador [20]
- [08](../modules/08-clases-lenguaje) §3 — Comparaciones: `<=>` [20], categorías de ordenación, `==` por defecto, reescritura
- [08](../modules/08-clases-lenguaje) §4 — Designated initializers [20] y configuración de periféricos
- [08](../modules/08-clases-lenguaje) §5 — *Deducing this* [23]: sobrecargas const/&&, CRTP sin CRTP, lambdas recursivas
- [08](../modules/08-clases-lenguaje) §7 — Atributos: `[[maybe_unused]]`, `[[fallthrough]]` [17], `[[likely]]`, `[[no_unique_address]]` [20], `[[assume]]` [23]
- [08](../modules/08-clases-lenguaje) §9 — `volatile`: usos deprecados [20] y revertidos [23]; solo para MMIO
- [06](../modules/06-lambdas) §1 — Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función
- [06](../modules/06-lambdas) §4.3 — `function_ref` [26]
- [06](../modules/06-lambdas) §5 — Patrones: IIFE, *overloaded*, callbacks de ISR con templates o `function_ref`
- [07](../modules/07-ranges) §1.2 — Escribir un iterador y un centinela propios
- [07](../modules/07-ranges) §2 — Algoritmos: `all_of`, `iota` [11], `clamp`, `reduce` [17], `midpoint`, `shift_left` [20]
- [07](../modules/07-ranges) §3 — Ranges [20]: centinelas, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges*
- [07](../modules/07-ranges) §4 — Views [20]: `filter`, `transform`, `take`, `split`, `join`, `iota`; pereza; views propias    _sin heap; revisar tamaño con `-Os`_
- [16](../modules/16-diseno-apis) §2.2 — Estático (templates/concepts, CRTP, deducing this)
- [16](../modules/16-diseno-apis) §2.3 — Cerrado (`std::variant`)
- [16](../modules/16-diseno-apis) §3.3 — Inyección de dependencias con concepts para testabilidad
- [16](../modules/16-diseno-apis) §5.1 — APIs en C: `extern "C"`, tipos opacos, propiedad entre fronteras
- [09](../modules/09-concurrencia) §2.1 — Órdenes de memoria y cuándo basta `relaxed`
- [09](../modules/09-concurrencia) §3 — Problemas clásicos: deadlock, livelock, inversión de prioridad, *false sharing* (`hardware_destructive_interference_size` [17]), ABA
- [09](../modules/09-concurrencia) §6 — RTOS: RAII sobre FreeRTOS, requisitos `Lockable` para `lock_guard`, SPSC ISR→tarea
- [17](../modules/17-rendimiento) §2.2 — AoS frente a SoA, diseño orientado a datos
- [17](../modules/17-rendimiento) §2.3 — Asignaciones: coste, pools, arenas, `pmr`, *small buffer optimization*
- [17](../modules/17-rendimiento) §3 — Coste de abstracciones: inlining, devirtualización, `std::function`, excepciones, RTTI
- [17](../modules/17-rendimiento) §5 — Ramas y predicción, código sin ramas, aritmética de punto fijo
- [13](../modules/13-embedded) §1.1 — *Freestanding* y su ampliación [23/26]
- [13](../modules/13-embedded) §1.2 — `-fno-exceptions`, `-fno-rtti`, `-fno-threadsafe-statics`: qué deja de funcionar
- [13](../modules/13-embedded) §1.4 — Arranque: `.init_array`, constructores globales, `constinit`
- [13](../modules/13-embedded) §2.1 — `std::pmr` [17] sobre buffers estáticos
- [13](../modules/13-embedded) §2.2 — Allocators y pools propios
- [13](../modules/13-embedded) §2.3 — *Placement new*, `launder` [17], `construct_at` [20], `start_lifetime_as` [23]
- [13](../modules/13-embedded) §2.4 — ETL, `inplace_vector` [26]
- [13](../modules/13-embedded) §3.1 — `<bit>` [20], `byteswap` [23]
- [13](../modules/13-embedded) §3.2 — MMIO tipado: `volatile` + templates + máscaras `constexpr`
- [13](../modules/13-embedded) §3.3 — Bitfields frente a máscaras, *strict aliasing* y `bit_cast`
- [13](../modules/13-embedded) §4 — Tamaño y rendimiento: `size`, `.map`, Bloaty, LTO, `--gc-sections`, coste de templates y virtual
- [13](../modules/13-embedded) §5 — Aritmética: punto fijo, enteros de ancho fijo, promociones y overflow
- [13](../modules/13-embedded) §6 — Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines
- [11](../modules/11-format-chrono-io) §2 — `to_chars`/`from_chars` [17], constexpr [23]
- [11](../modules/11-format-chrono-io) §5 — `<chrono>`: duraciones, relojes [11], literales [14], calendario y zonas [20]   _duraciones y relojes propios; zonas horarias no_
- [10](../modules/10-coroutines) §5.2 — Protocolos con timeouts y scheduler cooperativo
- [12](../modules/12-modulos) §4 — Sin módulos: namespaces `inline` [11] para versionado, anidados [17], `__has_include` [17], macros `__cpp_*` [20]
- [14](../modules/14-cpp26) §1 — Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas    _todo en compilación_
- [14](../modules/14-cpp26) §2 — Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler
- [14](../modules/14-cpp26) §4.1 — `inplace_vector`, `function_ref`, `optional<T&>`, aritmética saturada

<a id="embcond"></a>
### 🟡 `@emb:cond`

- [01](../modules/01-fundamentos) §4.4 — `shared_ptr`/`weak_ptr`, `make_shared`, coste del bloque de control    _heap y atomics_
- [15](../modules/15-ub-seguridad) §3.2 — Bounds checking: `.at()`, `span`, modos de hardening (`_GLIBCXX_ASSERTIONS`, libc++ hardening)   _coste de tamaño; activar en debug_
- [15](../modules/15-ub-seguridad) §4 — Detección: ASan, UBSan, MSan, TSan, Valgrind; constexpr como detector de UB    _en host, no en target_
- [03](../modules/03-templates-concepts) §7 — Coste: explosión de instanciaciones y tamaño de código (*code bloat*), técnicas de *thin template*   _vigilar flash con muchas instanciaciones_
- [04](../modules/04-tipos-vocabulario) §5.2 — `flat_map`/`flat_set` [23]   _contenedor subyacente con heap_
- [05](../modules/05-gestion-errores) §4.4 — `value()` lanza `bad_expected_access`: usar `*`/`has_value` sin excepciones
- [05](../modules/05-gestion-errores) §5 — `std::error_code` / `error_category` [11]    _categorías con strings, revisar tamaño_
- [08](../modules/08-clases-lenguaje) §6 — Polimorfismo dinámico: vtables, destructores virtuales, *slicing*, `final` para devirtualizar    _vtables en flash; evitar RTTI_
- [06](../modules/06-lambdas) §4.1 — `std::function` [11]: borrado de tipo y SBO    _heap si el cierre no cabe en el SBO_
- [06](../modules/06-lambdas) §4.2 — `move_only_function` [23], `copyable_function` [26]
- [07](../modules/07-ranges) §5 — C++23: `ranges::to`, `zip`, `enumerate`, `chunk`, `slide`, `fold_left`, `contains`   _`ranges::to` asigna memoria_
- [16](../modules/16-diseno-apis) §2.1 — Dinámico (virtual)   _vtables, sin RTTI_
- [16](../modules/16-diseno-apis) §2.4 — *Type erasure* (estilo `std::function`, Sean Parent)    _sin heap con SBO fijo_
- [16](../modules/16-diseno-apis) §4.2 — PIMPL, *fast PIMPL*, interfaces abstractas   _PIMPL implica heap salvo storage fijo_
- [09](../modules/09-concurrencia) §2.2 — Lock-free en Cortex-M0 frente a M3/M4/M7, `is_always_lock_free` [17]   _M0 no tiene LDREX/STREX_
- [09](../modules/09-concurrencia) §4.2 — `mutex`, `scoped_lock` [17], `shared_mutex` [17], `condition_variable`   _vía primitivas del RTOS_
- [17](../modules/17-rendimiento) §2.1 — Jerarquía de caché, localidad, prefetching   _MCUs sin caché: importa el acceso a flash_
- [17](../modules/17-rendimiento) §4 — Compilador: `-O2`/`-O3`/`-Os`, LTO, PGO, vectorización, `[[likely]]`, `[[assume]]`    _PGO poco práctico en target_
- [17](../modules/17-rendimiento) §7 — `std::simd` [26] e intrínsecos (NEON, SSE/AVX)   _NEON en Cortex-A; Helium en M55_
- [13](../modules/13-embedded) §1.3 — newlib/newlib-nano, partes de la STL que arrastran heap o locale
- [11](../modules/11-format-chrono-io) §1.1 — `format`, `format_to_n` [20], especificadores, comprobación en compilación    _coste en flash; `format_to_n` evita heap_
- [11](../modules/11-format-chrono-io) §3 — Strings: SSO, `starts_with` [20], `contains` [23], `resize_and_overwrite` [23], literales   _heap fuera del SSO_
- [10](../modules/10-coroutines) §5.1 — `operator new` en `promise_type`, pools estáticos, HALO    _el frame usa heap salvo que se controle_
- [12](../modules/12-modulos) §2.2 — `import std;` [23]   _soporte de toolchain cruzado_
- [14](../modules/14-cpp26) §3 — `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all`

<a id="embno"></a>
### 🔴 `@emb:no`

- [04](../modules/04-tipos-vocabulario) §3 — `std::any` [17]   _heap y RTTI_
- [05](../modules/05-gestion-errores) §1.1 — Coste real de las excepciones: tablas de unwind, tamaño de código, determinismo   _bare-metal suele compilar con `-fno-exceptions`_
- [07](../modules/07-ranges) §2.1 — Políticas de ejecución paralela [17]    _requiere TBB o hilos_
- [09](../modules/09-concurrencia) §4.1 — `thread`, `jthread`/`stop_token` [20], `thread_local` [11]    _bare-metal sin hilos; usar el RTOS_
- [09](../modules/09-concurrencia) §5 — Tareas: `async`/`future` [11] y sus límites, `std::execution` [26]
- [11](../modules/11-format-chrono-io) §1.3 — `print` [23], formato de rangos [23]   _depende de stdio_
- [11](../modules/11-format-chrono-io) §6 — Linux: `filesystem` [17], `spanstream` [23], iostreams frente a format
