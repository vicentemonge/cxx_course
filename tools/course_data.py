"""Fuente única del temario. tools/gen_docs.py genera a partir de aquí los README de
cada módulo, docs/TAGS.md y la tabla del README raíz.

Convención de tags (en el texto, entre comillas invertidas):
  @<tema>      tema core transversal (ver CORE_TAGS)
  @emb:ok      aporte claro en firmware (sin coste oculto, recomendado)
  @emb:cond    usable con condiciones (heap, excepciones, RTTI, toolchain, tamaño)
  @emb:no      descarte en bare-metal (válido en Linux embebido)
"""

CORE_TAGS = {
    "lifetime":     "Tiempo de vida, propiedad, RAII, dangling",
    "value-sem":    "Semántica de valor: copia, movimiento, categorías de valor",
    "compile-time": "Cálculo y validación en compilación",
    "generic":      "Programación genérica: templates, concepts, deducción",
    "type-design":  "Diseño de tipos: tipos vocabulario, tipos fuertes, invariantes",
    "errors":       "Gestión de errores y contratos",
    "functional":   "Lambdas, invocables y composición",
    "iteration":    "Iteradores, ranges y algoritmos",
    "concurrency":  "Hilos, sincronización y paralelismo",
    "memory-model": "Modelo de memoria, atomics y órdenes",
    "async":        "Coroutines y ejecución asíncrona",
    "performance":  "Rendimiento: coste de abstracciones, memoria, caché",
    "safety":       "Comportamiento indefinido, seguridad de memoria, hardening",
    "abi":          "Enlace, ODR, ABI, modelo de compilación y organización",
    "interop":      "Interoperabilidad con C, Rust y otras APIs",
    "tooling":      "Build, testing, sanitizers, análisis estático",
}

EMB_TAGS = {
    "emb:ok":   "Aporte en firmware: sin coste oculto o con beneficio claro",
    "emb:cond": "Condicional: depende de heap, excepciones, RTTI, toolchain o tamaño de código",
    "emb:no":   "Descarte en bare-metal (sigue siendo válido en Linux embebido)",
}

ORDER = ["01", "15", "18", "02", "03", "04", "05", "08", "06", "07", "16",
         "09", "17", "13", "11", "10", "12", "14"]

MODULES = []

def mod(d, title, intro, topics, exercise, questions, build=True):
    MODULES.append(dict(d=d, title=title, intro=intro, topics=topics.strip("\n"),
                        exercise=exercise, questions=questions, build=build))

# ============================================================================ 01
mod("01-fundamentos", "Fundamentos del C++ moderno",
"Base de C++11/14 sobre la que se construye todo. En una entrevista de nivel senior "
"se da por supuesto: los fallos aquí (categorías de valor, reglas de miembros especiales) "
"descartan candidatos antes de llegar a templates o concurrencia.",
"""
1. Inicialización
    1. Llaves, *narrowing* y *most vexing parse* [11] · `@type-design` `@emb:ok`
    2. `std::initializer_list` y su prioridad en la resolución de sobrecarga [11] · `@generic`
    3. NSDMI [11/14], agregados [11→20], agregados con paréntesis [20] · `@type-design` `@emb:ok`
    4. Inicialización por defecto, de valor y cero; variables sin inicializar · `@safety` `@emb:ok`
2. Deducción de tipos
    1. Reglas de deducción de templates como base de `auto` [11] · `@generic`
    2. `auto`, `decltype`, `decltype(auto)`, *trailing return* [11/14] · `@generic`
    3. Trampas: proxies (`vector<bool>`), `auto x{1}` [11 vs 17], referencias perdidas · `@value-sem`
3. Semántica de movimiento
    1. Categorías de valor: lvalue, prvalue, xvalue [11/17] · `@value-sem`
    2. Forwarding references, colapso de referencias, `std::forward` [11] · `@value-sem` `@generic`
    3. *Copy elision* garantizada [17], NRVO, movimiento implícito al retornar [20/23] · `@value-sem` `@performance` `@emb:ok`
    4. `noexcept` en movimiento y su efecto en contenedores · `@errors` `@performance`
    5. Estado "movido": válido pero no especificado; diseñar el estado vacío · `@lifetime`
4. Miembros especiales y propiedad
    1. Reglas de generación implícita (tabla de Hinnant) y Rule of Zero/Five · `@lifetime` `@value-sem` `@emb:ok`
    2. `= default`, `= delete`, constructores `explicit`, delegados y heredados [11] · `@type-design`
    3. `std::unique_ptr` con *deleters* propios [11] · `@lifetime` `@emb:ok` _sin heap si envuelve handles estáticos_
    4. `shared_ptr`/`weak_ptr`, `make_shared`, coste del bloque de control · `@lifetime` `@performance` `@emb:cond` _heap y atomics_
    5. `make_unique` [14], `make_unique_for_overwrite` [20], `out_ptr`/`inout_ptr` [23] · `@lifetime` `@interop`
5. Mejoras básicas del lenguaje
    1. `enum class`, tipo subyacente [11], `using enum` [20], `to_underlying` [23] · `@type-design` `@emb:ok`
    2. `nullptr`, `override`/`final`, alias con `using` [11] · `@type-design` `@emb:ok`
    3. Raw strings, UDLs [11], literales binarios y separador `'` [14] · `@type-design` `@emb:ok` _UDLs para unidades físicas_
    4. `static_assert` [11/17], range-`for` [11/20] · `@compile-time` `@emb:ok`
""",
"Envolver un handle de periférico (UART o SPI de la HAL) en una clase RAII movible y no copiable, con `enum class` para los modos de configuración.",
["¿Qué miembros especiales genera el compilador si declaras solo un destructor? ¿Y si declaras un constructor de movimiento?",
 "¿Por qué `std::vector` copia en vez de mover al crecer si el constructor de movimiento no es `noexcept`?",
 "Diferencia entre `std::move` y `std::forward`. ¿Qué hace `std::move` exactamente?",
 "¿Qué devuelve `decltype((x))` y por qué difiere de `decltype(x)`?"])

# ============================================================================ 02
mod("02-compile-time", "Programación en tiempo de compilación",
"El área que más ha crecido desde C++11. En firmware convierte tablas, CRC y validaciones "
"de configuración en coste cero; en sistemas grandes reduce errores de runtime a errores de compilación.",
"""
1. `constexpr` y su evolución
    1. Una expresión [11] → bucles y variables [14] → lambdas [17] · `@compile-time` `@emb:ok`
    2. `try`, `virtual`, `union`, asignación transitoria, `vector`/`string` constexpr [20] · `@compile-time` `@emb:ok` _la memoria transitoria no llega al binario_
    3. `static` en funciones constexpr, tipos no literales [23], `<cmath>` constexpr [23/26] · `@compile-time`
    4. Límites: pasos de evaluación, diagnóstico de UB en constexpr como herramienta · `@compile-time` `@safety`
2. `if constexpr` [17] y ramas descartadas · `@compile-time` `@generic` `@emb:ok`
3. Garantías de compilación
    1. `consteval` [20], propagación [23] · `@compile-time` `@emb:ok`
    2. `if consteval` [23] vs `std::is_constant_evaluated()` [20] · `@compile-time`
    3. `constinit` [20] y el *static initialization order fiasco* · `@lifetime` `@emb:ok` _inicialización en `.data`, sin constructores en arranque_
4. Variables y templates en compilación
    1. Variable templates [14], variables `inline` [17] · `@compile-time` `@abi` `@emb:ok`
    2. NTTP `auto` [17], NTTP de clase y flotantes [20] · `@generic` `@compile-time` `@emb:ok`
5. Utilidades
    1. `std::bit_cast` [20] · `@safety` `@emb:ok`
    2. `std::index_sequence` [14] y expansión de tablas · `@generic` `@compile-time`
6. Coste de compilación: instanciaciones, `-ftime-trace`, cuándo calcular en build (script) en vez de en C++ · `@tooling` `@performance`
""",
"Generar en compilación una tabla CRC-32 o una LUT de calibración con `consteval`, colocarla en flash con `constinit`/`const` y verificar en el `.map` que no ocupa RAM.",
["¿Qué diferencia hay entre `constexpr`, `consteval` y `constinit`? Pon un caso para cada uno.",
 "¿Por qué el UB dentro de una evaluación constante es un error de compilación y cómo puedes aprovecharlo en tests?",
 "¿Qué problema resuelve `constinit` que `constexpr` no resuelve para una variable global mutable?",
 "¿Cuándo preferirías generar una tabla con un script en el build en vez de con `constexpr`?"])

# ============================================================================ 03
mod("03-templates-concepts", "Templates modernos y concepts",
"Nivel esperado: leer y escribir código genérico de bibliotecas (STL, Abseil, Folly) y "
"diagnosticar errores de instanciación. Concepts [20] sustituyen casi todo el SFINAE.",
"""
1. Fundamentos que siguen importando
    1. Lookup en dos fases, nombres dependientes, `typename` y `template` como desambiguadores · `@generic`
    2. ADL y puntos de personalización (`swap`, *niebloids*, CPOs) · `@generic` `@abi`
    3. Especialización total y parcial, sobrecarga frente a especialización · `@generic`
2. Variadic templates
    1. Packs, `sizeof...` [11], fold expressions [17] · `@generic` `@compile-time` `@emb:ok`
    2. Expansión en lambdas y `using` [17/20], pack indexing [26] · `@generic`
3. CTAD [17], guías de deducción, CTAD para agregados y alias [20] · `@generic` `@type-design`
4. SFINAE como herencia
    1. `enable_if`, `void_t`, *detection idiom* [11/17]: leerlo en código existente · `@generic`
5. Concepts [20]
    1. `requires` (cláusulas y expresiones), requisitos simples, de tipo, compuestos y anidados · `@generic` `@type-design`
    2. Sintaxis abreviada y parámetros `auto` · `@generic`
    3. Subsunción y ordenación de sobrecargas · `@generic`
    4. `<concepts>` estándar y concepts de iteradores/ranges · `@generic` `@iteration`
    5. Concepts como interfaz de drivers: polimorfismo estático sin vtable · `@generic` `@performance` `@emb:ok`
6. Type traits: `_t` [14], `_v` [17], `conjunction` [17], `remove_cvref`, `type_identity` [20] · `@generic` `@compile-time`
7. Coste: explosión de instanciaciones y tamaño de código (*code bloat*), técnicas de *thin template* · `@performance` `@emb:cond` _vigilar flash con muchas instanciaciones_
""",
"Definir un concept `RegisterAccess` para drivers (lectura/escritura de 8/16/32 bits) y reescribir con él un driver genérico que hoy use SFINAE o `void*`.",
["Explica el lookup en dos fases. ¿Por qué a veces hace falta `this->` en una clase derivada de una plantilla?",
 "¿Qué es un *customization point object* y qué problema de ADL resuelve?",
 "¿Cómo decide el compilador entre dos sobrecargas restringidas por concepts?",
 "¿Cómo reducirías el tamaño de código de una plantilla instanciada con 20 tipos distintos?"])

# ============================================================================ 04
mod("04-tipos-vocabulario", "Tipos vocabulario",
"Tipos que expresan intención en interfaces y eliminan clases enteras de bugs "
"(nulos, uniones mal etiquetadas, puntero+longitud). Es lo primero que se revisa en un code review.",
"""
1. `std::optional` [17], monádico [23], `optional<T&>` [26] · `@type-design` `@errors` `@emb:ok`
2. `std::variant` [17]
    1. `visit`, patrón *overloaded*, `get_if`, `valueless_by_exception` · `@type-design` `@functional` `@emb:ok`
    2. Máquinas de estado con `variant` · `@type-design` `@emb:ok`
    3. Coste: tamaño = mayor alternativa + índice; `visit` y tablas de salto · `@performance`
3. `std::any` [17] · `@type-design` `@emb:no` _heap y RTTI_
4. Vistas no propietarias
    1. `string_view` [17] y *dangling* · `@lifetime` `@safety` `@emb:ok`
    2. `span` [20], extensión estática/dinámica, `as_bytes` · `@lifetime` `@type-design` `@emb:ok`
    3. `mdspan` [23] · `@type-design` `@emb:ok`
5. Contenedores
    1. `array`, `to_array` [20], `tuple`, `apply` [17], `byte` [17] · `@type-design` `@emb:ok`
    2. `flat_map`/`flat_set` [23] · `@performance` `@emb:cond` _contenedor subyacente con heap_
    3. `inplace_vector` [26] · `@type-design` `@emb:ok`
    4. `try_emplace` [17], `contains`, `erase_if`, `ssize` [20] · `@iteration`
6. Tipos fuertes (*strong typedefs*): unidades, IDs y evitar argumentos intercambiables · `@type-design` `@safety` `@emb:ok`
""",
"Sustituir las firmas `(uint8_t* buf, size_t len)` de un driver por `std::span<std::byte>` y modelar los estados de un parser de tramas con `std::variant`.",
["¿Cuándo devolverías `std::optional<T>` y cuándo `std::expected<T, E>`?",
 "¿Qué riesgos tiene guardar un `std::string_view` como miembro de clase?",
 "¿Qué es `valueless_by_exception` y cuándo puede ocurrir?",
 "Diseña un tipo fuerte `Milliseconds` que no se pueda confundir con `Hertz`."])

# ============================================================================ 05
mod("05-gestion-errores", "Gestión de errores",
"Una empresa grande exige una política de errores coherente. `std::expected` [23] permite "
"errores tipados sin excepciones; las garantías de excepción siguen siendo pregunta obligada.",
"""
1. Panorama: códigos de retorno, `errno`, excepciones, tipos resultado · `@errors` `@performance`
    1. Coste real de las excepciones: tablas de unwind, tamaño de código, determinismo · `@errors` `@emb:no` _bare-metal suele compilar con `-fno-exceptions`_
2. Garantías de excepción: nothrow, fuerte, básica; copy-and-swap · `@errors` `@lifetime`
3. RAII para limpieza: *scope guards* (`scope_exit`), `unique_resource` · `@errors` `@lifetime` `@emb:ok`
4. `std::expected<T, E>` [23]
    1. `unexpected`, acceso, `value_or` · `@errors` `@type-design` `@emb:ok`
    2. `and_then`, `transform`, `or_else`, `transform_error` · `@errors` `@functional` `@emb:ok`
    3. `expected<void, E>` y diseño del tipo de error · `@errors` `@type-design`
    4. `value()` lanza `bad_expected_access`: usar `*`/`has_value` sin excepciones · `@errors` `@emb:cond`
5. `std::error_code` / `error_category` [11] · `@errors` `@interop` `@emb:cond` _categorías con strings, revisar tamaño_
6. Atributos y especificadores
    1. `[[nodiscard]]` [17/20], `noexcept` [11/17], `[[noreturn]]`, `std::unreachable` [23] · `@errors` `@emb:ok`
    2. Política de `noexcept`: cuándo marcar, efecto en `std::terminate` · `@errors`
7. Precondiciones: `assert`, `source_location` [20], contracts [26] · `@errors` `@safety` `@emb:ok`
""",
"Convertir la API pública de un driver de códigos `int` a `std::expected<T, DriverError>` y encadenar init → configure → read con `and_then`.",
["Define las garantías básica, fuerte y nothrow. ¿Qué garantía da `vector::push_back`?",
 "¿Qué ocurre si una excepción escapa de una función `noexcept`?",
 "Compara `std::expected` con excepciones en un servicio de alto rendimiento y en firmware.",
 "¿Cómo diseñarías los tipos de error de una biblioteca usada por varios equipos?"])

# ============================================================================ 06
mod("06-lambdas", "Lambdas y estilo funcional",
"Callbacks, visitantes, algoritmos y coroutines dependen de las lambdas. Entender el "
"tipo de cierre y el coste del borrado de tipo distingue a un senior.",
"""
1. Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función · `@functional` `@interop` `@emb:ok`
2. Evolución
    1. *Init-capture* y lambdas genéricas [14] · `@functional` `@value-sem`
    2. `constexpr` lambdas, captura de `*this` [17] · `@functional` `@compile-time` `@lifetime`
    3. Parámetros template, lambdas sin estado construibles, en contexto no evaluado [20] · `@functional` `@generic`
    4. Lambdas `static` y recursivas con *deducing this* [23] · `@functional`
3. Riesgos de tiempo de vida: capturas por referencia que sobreviven al ámbito · `@lifetime` `@safety`
4. Wrappers de invocables
    1. `std::function` [11]: borrado de tipo y SBO · `@functional` `@performance` `@emb:cond` _heap si el cierre no cabe en el SBO_
    2. `move_only_function` [23], `copyable_function` [26] · `@functional` `@emb:cond`
    3. `function_ref` [26] · `@functional` `@emb:ok`
    4. `invoke` [17], `invoke_r` [23], `bind_front` [20], `bind_back` [23] · `@functional` `@generic`
5. Patrones: IIFE, *overloaded*, callbacks de ISR con templates o `function_ref` · `@functional` `@emb:ok`
""",
"Implementar un dispatcher de eventos sin heap que acepte lambdas con captura, comparando tamaño de código entre `std::function`, templates y `function_ref`.",
["¿Qué genera el compilador para una lambda con capturas? ¿Cuál es su tamaño?",
 "¿Cuándo asigna memoria `std::function`? ¿Cómo lo evitas?",
 "¿Qué problema tiene capturar `this` en una lambda que se ejecuta en otro hilo?",
 "Implementa una versión simplificada de `function_ref`."])

# ============================================================================ 07
mod("07-ranges", "Ranges, views y algoritmos",
"Saber elegir algoritmo y escribir iteradores correctos sigue siendo una prueba estándar. "
"Ranges [20] cambia el estilo, pero el modelo de iteradores es la base.",
"""
1. Modelo de iteradores
    1. Categorías, `iterator_traits`, iteradores contiguos [20] · `@iteration` `@generic`
    2. Escribir un iterador y un centinela propios · `@iteration` `@generic` `@emb:ok`
    3. Invalidación de iteradores por contenedor · `@iteration` `@lifetime` `@safety`
2. Algoritmos: `all_of`, `iota` [11], `clamp`, `reduce` [17], `midpoint`, `shift_left` [20] · `@iteration` `@emb:ok`
    1. Políticas de ejecución paralela [17] · `@iteration` `@concurrency` `@emb:no` _requiere TBB o hilos_
3. Ranges [20]: centinelas, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges* · `@iteration` `@generic` `@emb:ok`
4. Views [20]: `filter`, `transform`, `take`, `split`, `join`, `iota`; pereza; views propias · `@iteration` `@functional` `@emb:ok` _sin heap; revisar tamaño con `-Os`_
5. C++23: `ranges::to`, `zip`, `enumerate`, `chunk`, `slide`, `fold_left`, `contains` · `@iteration` `@emb:cond` _`ranges::to` asigna memoria_
6. Coste: tiempo de compilación, depuración y ensamblador frente a bucles manuales · `@performance` `@tooling`
""",
"Reescribir el procesado de un buffer de muestras ADC (filtrado, escalado, detección de umbral) con views y comparar el ensamblador con el bucle manual.",
["¿Qué es un centinela y qué ventaja aporta frente a un par de iteradores?",
 "¿Por qué `filter_view` no es `const`-iterable y qué implica?",
 "¿Qué invalida los iteradores de `std::vector`? ¿Y de `std::unordered_map`?",
 "¿Qué es un *borrowed range* y para qué existe `std::ranges::dangling`?"])

# ============================================================================ 08
mod("08-clases-lenguaje", "Clases y novedades del lenguaje",
"Cambios que reducen código repetitivo y bugs en clases: comparaciones, inicialización, "
"desestructuración y deducción de `this`.",
"""
1. Structured bindings [17], tipos tuple-like, con capturas [20], como condición [26] · `@type-design` `@emb:ok`
2. `if`/`switch` con inicializador [17], range-`for` con inicializador [20] · `@lifetime` `@emb:ok`
3. Comparaciones: `<=>` [20], categorías de ordenación, `==` por defecto, reescritura · `@type-design` `@emb:ok`
4. Designated initializers [20] y configuración de periféricos · `@type-design` `@emb:ok`
5. *Deducing this* [23]: sobrecargas const/&&, CRTP sin CRTP, lambdas recursivas · `@generic` `@type-design` `@emb:ok`
6. Polimorfismo dinámico: vtables, destructores virtuales, *slicing*, `final` para devirtualizar · `@type-design` `@performance` `@emb:cond` _vtables en flash; evitar RTTI_
7. Atributos: `[[maybe_unused]]`, `[[fallthrough]]` [17], `[[likely]]`, `[[no_unique_address]]` [20], `[[assume]]` [23] · `@performance` `@emb:ok`
8. Otros: `explicit(bool)` [20], `char8_t` [20], `auto(x)` [23], `operator[]` multidimensional [23] · `@type-design`
9. `volatile`: usos deprecados [20] y revertidos [23]; solo para MMIO · `@memory-model` `@emb:ok`
10. Preprocesador: `#elifdef` [23], `#embed` [26] · `@tooling` `@emb:ok` _`#embed` para blobs de firmware_
""",
"Definir la configuración de un periférico con designated initializers y un tipo de versión de firmware comparable con `<=>`.",
["¿Qué genera `auto operator<=>(const T&) const = default;` y qué no?",
 "¿Qué es el *object slicing* y cómo se previene?",
 "¿Qué problema de CRTP resuelve *deducing this*?",
 "¿Cuándo es útil `[[no_unique_address]]`?"])

# ============================================================================ 09
mod("09-concurrencia", "Concurrencia y modelo de memoria",
"Pregunta segura en cualquier entrevista de sistemas. El modelo de memoria [11] explica "
"`volatile` frente a `std::atomic` y la comunicación entre ISR, tareas e hilos.",
"""
1. Modelo de memoria [11]: *happens-before*, *synchronizes-with*, data races = UB · `@memory-model` `@safety`
2. `std::atomic` [11]
    1. Órdenes de memoria y cuándo basta `relaxed` · `@memory-model` `@performance` `@emb:ok`
    2. Lock-free en Cortex-M0 frente a M3/M4/M7, `is_always_lock_free` [17] · `@memory-model` `@emb:cond` _M0 no tiene LDREX/STREX_
    3. `atomic_ref`, `wait`/`notify`, `atomic<shared_ptr>` [20], fences · `@memory-model` `@concurrency`
3. Problemas clásicos: deadlock, livelock, inversión de prioridad, *false sharing* (`hardware_destructive_interference_size` [17]), ABA · `@concurrency` `@performance` `@emb:ok`
4. Hilos y sincronización
    1. `thread`, `jthread`/`stop_token` [20], `thread_local` [11] · `@concurrency` `@lifetime` `@emb:no` _bare-metal sin hilos; usar el RTOS_
    2. `mutex`, `scoped_lock` [17], `shared_mutex` [17], `condition_variable` · `@concurrency` `@emb:cond` _vía primitivas del RTOS_
    3. `counting_semaphore`, `latch`, `barrier` [20], `call_once` · `@concurrency`
5. Tareas: `async`/`future` [11] y sus límites, `std::execution` [26] · `@concurrency` `@async` `@emb:no`
6. RTOS: RAII sobre FreeRTOS, requisitos `Lockable` para `lock_guard`, SPSC ISR→tarea · `@concurrency` `@lifetime` `@emb:ok`
7. Detección: ThreadSanitizer, revisión de órdenes de memoria · `@tooling` `@safety`
""",
"Implementar un ring buffer SPSC lock-free con `std::atomic` y órdenes acquire/release para pasar datos de una ISR a una tarea, y razonar formalmente su corrección.",
["¿Por qué `volatile` no sirve para sincronizar hilos?",
 "Explica acquire/release con un ejemplo de publicación de datos.",
 "¿Qué es el *false sharing* y cómo lo detectas y corriges?",
 "¿Cómo implementas un mutex compatible con `std::lock_guard` sobre FreeRTOS?"])

# ============================================================================ 10
mod("10-coroutines", "Coroutines",
"Mecanismo de bajo nivel [20] con `std::generator` [23] y `std::execution` [26] encima. "
"Se usa en servidores asíncronos (Folly, Seastar) y promete mucho en máquinas de estado de firmware.",
"""
1. Conceptos: stackless frente a hilos y *fibers*; `co_await`/`co_yield`/`co_return`; el frame · `@async` `@lifetime`
2. Maquinaria [20]: `promise_type`, `coroutine_handle`, awaitables, transferencia simétrica · `@async`
3. Tiempo de vida: referencias en parámetros que no sobreviven a la suspensión · `@async` `@lifetime` `@safety`
4. Tipos de alto nivel: `generator<T>` propio, `std::generator` [23], `task<T>` · `@async` `@iteration`
5. Embedded
    1. `operator new` en `promise_type`, pools estáticos, HALO · `@async` `@performance` `@emb:cond` _el frame usa heap salvo que se controle_
    2. Protocolos con timeouts y scheduler cooperativo · `@async` `@emb:ok`
""",
"Reescribir una máquina de estados de protocolo (handshake por UART con reintentos y timeout) como coroutine, con frames asignados desde un pool estático.",
["¿Dónde vive el estado de una coroutine y quién lo destruye?",
 "¿Por qué es peligroso pasar un `const std::string&` a una coroutine?",
 "¿Qué es la transferencia simétrica y qué problema evita?",
 "¿Cómo evitarías la asignación dinámica del frame en un microcontrolador?"])

# ============================================================================ 11
mod("11-format-chrono-io", "Strings, formato, tiempo y E/S",
"`std::format` [20] y `std::print` [23] con seguridad de tipos; `<charconv>` [17] rápido y sin locale; "
"`<chrono>` para que las unidades de tiempo sean tipos.",
"""
1. Formato
    1. `format`, `format_to_n` [20], especificadores, comprobación en compilación · `@type-design` `@safety` `@emb:cond` _coste en flash; `format_to_n` evita heap_
    2. `std::formatter` propio · `@generic`
    3. `print` [23], formato de rangos [23] · `@type-design` `@emb:no` _depende de stdio_
2. `to_chars`/`from_chars` [17], constexpr [23] · `@performance` `@emb:ok`
3. Strings: SSO, `starts_with` [20], `contains` [23], `resize_and_overwrite` [23], literales · `@performance` `@emb:cond` _heap fuera del SSO_
4. Texto y Unicode: `char8_t` [20], UTF-8 como codificación por defecto, por qué evitar `std::regex` · `@type-design` `@performance`
5. `<chrono>`: duraciones, relojes [11], literales [14], calendario y zonas [20] · `@type-design` `@emb:ok` _duraciones y relojes propios; zonas horarias no_
6. Linux: `filesystem` [17], `spanstream` [23], iostreams frente a format · `@abi` `@emb:no`
""",
"Implementar un logger con `format_to_n` sobre un buffer estático, un formatter para un struct de telemetría y un reloj `chrono` propio sobre SysTick.",
["¿Por qué `std::format` es más seguro que `printf`? ¿Y más rápido que iostreams?",
 "¿Qué ventajas tiene `from_chars` frente a `strtol` o `std::stoi`?",
 "Diseña un reloj `chrono` compatible sobre un contador de hardware de 32 bits con wrap-around.",
 "¿Por qué se desaconseja `std::regex` en código de producción?"])

# ============================================================================ 12
mod("12-modulos", "Módulos, enlace y organización del código",
"Entender el modelo de compilación (unidades de traducción, ODR, enlace) es imprescindible en "
"bases de código de millones de líneas. Los módulos [20] lo cambian, con soporte aún irregular. "
"Fuera del build por defecto hasta que el toolchain lo permita.",
"""
1. Modelo clásico
    1. Unidades de traducción, enlace interno/externo, `static` y namespaces anónimos · `@abi`
    2. ODR, `inline` (funciones y variables [17]), violaciones silenciosas · `@abi` `@safety`
    3. Coste de los headers: tiempos de build, *include-what-you-use*, *precompiled headers* · `@abi` `@tooling`
2. Módulos [20]
    1. `export module`, `import`, particiones, *global module fragment*, *header units* · `@abi`
    2. `import std;` [23] · `@abi` `@emb:cond` _soporte de toolchain cruzado_
    3. *Module linkage*, macros que no cruzan fronteras · `@abi`
3. Herramientas: CMake `FILE_SET CXX_MODULES` + Ninja, soporte en GCC/Clang/MSVC · `@tooling` `@abi`
4. Sin módulos: namespaces `inline` [11] para versionado, anidados [17], `__has_include` [17], macros `__cpp_*` [20] · `@abi` `@emb:ok`
""",
"Convertir una librería pequeña de utilidades en un módulo y compilarla con CMake + Ninja para host; documentar qué falla con el toolchain del target.",
["¿Qué es una violación de ODR y por qué el enlazador no siempre la detecta?",
 "¿Qué aporta un namespace `inline` al versionado de una biblioteca?",
 "¿Qué problemas de los headers resuelven los módulos y cuáles no?",
 "¿Cómo reducirías a la mitad el tiempo de compilación de un proyecto grande?"],
build=False)

# ============================================================================ 13
mod("13-embedded", "C++ moderno en embedded",
"Módulo transversal: aplica todo lo anterior a targets sin heap, sin excepciones y sin RTTI, "
"con acceso directo a hardware. Recoge los descartes y aportes marcados con `@emb:*` en el resto del curso.",
"""
1. Entorno
    1. *Freestanding* y su ampliación [23/26] · `@abi` `@emb:ok`
    2. `-fno-exceptions`, `-fno-rtti`, `-fno-threadsafe-statics`: qué deja de funcionar · `@errors` `@emb:ok`
    3. newlib/newlib-nano, partes de la STL que arrastran heap o locale · `@performance` `@emb:cond`
    4. Arranque: `.init_array`, constructores globales, `constinit` · `@lifetime` `@emb:ok`
2. Memoria sin heap
    1. `std::pmr` [17] sobre buffers estáticos · `@lifetime` `@performance` `@emb:ok`
    2. Allocators y pools propios · `@lifetime` `@emb:ok`
    3. *Placement new*, `launder` [17], `construct_at` [20], `start_lifetime_as` [23] · `@lifetime` `@safety` `@emb:ok`
    4. ETL, `inplace_vector` [26] · `@type-design` `@emb:ok`
3. Bits y registros
    1. `<bit>` [20], `byteswap` [23] · `@compile-time` `@emb:ok`
    2. MMIO tipado: `volatile` + templates + máscaras `constexpr` · `@type-design` `@memory-model` `@emb:ok`
    3. Bitfields frente a máscaras, *strict aliasing* y `bit_cast` · `@safety` `@emb:ok`
4. Tamaño y rendimiento: `size`, `.map`, Bloaty, LTO, `--gc-sections`, coste de templates y virtual · `@performance` `@tooling` `@emb:ok`
5. Aritmética: punto fijo, enteros de ancho fijo, promociones y overflow · `@type-design` `@safety` `@emb:ok`
6. Estándares: MISRA C++:2023, AUTOSAR C++14, Core Guidelines · `@safety` `@tooling` `@emb:ok`
""",
"Construir una capa de acceso a registros tipada y `constexpr` para un periférico de STM32 y verificar que el binario es idéntico al de la versión con macros CMSIS.",
["¿Qué partes de la biblioteca estándar usarías en bare-metal sin heap ni excepciones?",
 "¿Por qué reinterpretar un buffer de bytes como struct puede ser UB y cómo lo harías bien?",
 "¿Qué cuesta en flash una función virtual? ¿Y una plantilla instanciada 10 veces?",
 "¿Cómo garantizas que un objeto global no ejecuta código antes de `main`?"])

# ============================================================================ 14
mod("14-cpp26", "C++26",
"Técnicamente completo, con soporte llegando por partes. Reflexión y contracts cambiarán cómo se "
"escriben serialización, bindings y validación. Fuera del build por defecto.",
"""
1. Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas · `@compile-time` `@generic` `@emb:ok` _todo en compilación_
    1. Casos de uso: `enum` ↔ string, serialización, mapas de registros, bindings · `@compile-time` `@interop`
2. Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler · `@errors` `@safety` `@emb:ok`
3. `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all` · `@async` `@concurrency` `@emb:cond`
4. Biblioteca
    1. `inplace_vector`, `function_ref`, `optional<T&>`, aritmética saturada · `@type-design` `@emb:ok`
    2. Hazard pointers, RCU · `@memory-model` `@concurrency`
    3. `std::simd`, `std::linalg` · `@performance`
    4. Hardening de la biblioteca estándar · `@safety`
5. Lenguaje: pack indexing, `#embed`, placeholder `_`, `= delete("motivo")`, comportamiento erróneo para no inicializadas · `@safety` `@generic`
""",
"Usar reflexión para generar automáticamente la conversión `enum` ↔ string de los códigos de error del módulo 05.",
["¿Qué problemas de serialización resuelve la reflexión estática?",
 "¿Qué semánticas de evaluación tienen los contracts y cuál usarías en producción?",
 "¿Qué es el comportamiento erróneo y cómo cambia el riesgo de las variables sin inicializar?",
 "¿Qué aporta `std::execution` frente a `std::async`?"],
build=False)

# ============================================================================ 15  NUEVO
mod("15-ub-seguridad", "Modelo de objetos, comportamiento indefinido y seguridad de memoria",
"Módulo nuevo y prioritario. Mozilla, Google, Meta y DuckDuckGo invierten en seguridad de memoria "
"(Rust, hardening, sanitizers). Un ingeniero top de C++ debe saber qué es UB, por qué el optimizador "
"lo explota y cómo eliminar clases enteras de vulnerabilidades.",
"""
1. Modelo de objetos
    1. Objeto, almacenamiento, tiempo de vida; inicio y fin de vida · `@lifetime` `@safety`
    2. Creación implícita de objetos [20], `start_lifetime_as` [23] · `@lifetime` `@safety` `@emb:ok`
    3. Alineación, padding, `alignas`, `alignof`, tamaños de tipos · `@performance` `@emb:ok`
    4. Tipos trivialmente copiables, *standard layout*, implicit-lifetime types · `@type-design` `@interop`
2. Comportamiento indefinido
    1. Catálogo: overflow con signo, desplazamientos, nulos, fuera de límites, data races, uso tras liberar · `@safety`
    2. *Strict aliasing* y `bit_cast`/`memcpy` como alternativas · `@safety` `@emb:ok`
    3. Cómo el optimizador explota el UB (eliminación de comprobaciones) · `@safety` `@performance`
    4. Comportamiento no especificado e implementation-defined · `@safety`
    5. Comportamiento erróneo [26] · `@safety`
3. Seguridad de memoria
    1. Dangling: referencias, vistas, iteradores, lambdas, coroutines · `@lifetime` `@safety`
    2. Bounds checking: `.at()`, `span`, modos de hardening (`_GLIBCXX_ASSERTIONS`, libc++ hardening) · `@safety` `@emb:cond` _coste de tamaño; activar en debug_
    3. Clang `-Wunsafe-buffer-usage`, `-Wdangling`, `[[clang::lifetimebound]]` · `@safety` `@tooling`
    4. Perfiles de seguridad y lifetime analysis (propuestas) · `@safety`
4. Detección: ASan, UBSan, MSan, TSan, Valgrind; constexpr como detector de UB · `@safety` `@tooling` `@emb:cond` _en host, no en target_
5. Contexto: C++ frente a Rust en Mozilla/Google; cuándo reescribir y cuándo endurecer · `@safety` `@interop`
""",
"Reunir cinco bugs de UB típicos de firmware (aliasing de buffers, overflow en contadores, shift de 32 bits, lectura sin inicializar, dangling de `string_view`), reproducirlos con UBSan/ASan en host y corregirlos sin coste en el target.",
["¿Por qué el compilador puede eliminar `if (x + 1 < x)` con `int x`?",
 "¿Qué es *strict aliasing* y cuándo es legal leer un `float` como `uint32_t`?",
 "¿Qué detecta ASan que no detecta UBSan, y viceversa?",
 "¿Cuándo empieza y termina el tiempo de vida de un objeto creado con `malloc`?"])

# ============================================================================ 16  NUEVO
mod("16-diseno-apis", "Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad",
"Módulo nuevo. En empresas con bibliotecas compartidas por cientos de ingenieros se evalúa la capacidad "
"de diseñar APIs estables, elegir el tipo de polimorfismo adecuado e integrar C y Rust.",
"""
1. Semántica de valor frente a referencia en el diseño de APIs · `@value-sem` `@type-design`
2. Polimorfismo: cuatro herramientas
    1. Dinámico (virtual) · `@type-design` `@emb:cond` _vtables, sin RTTI_
    2. Estático (templates/concepts, CRTP, deducing this) · `@generic` `@emb:ok`
    3. Cerrado (`std::variant`) · `@type-design` `@emb:ok`
    4. *Type erasure* (estilo `std::function`, Sean Parent) · `@type-design` `@functional` `@emb:cond` _sin heap con SBO fijo_
3. Diseño de interfaces
    1. Parámetros: por valor, `const&`, `&&`, vistas; devolución de valores · `@value-sem` `@performance`
    2. Invariantes, `explicit`, tipos fuertes, difícil de usar mal · `@type-design` `@safety`
    3. Inyección de dependencias con concepts para testabilidad · `@generic` `@tooling` `@emb:ok`
4. ABI y bibliotecas
    1. Estabilidad de ABI, por qué el estándar no rompe `std::string` · `@abi`
    2. PIMPL, *fast PIMPL*, interfaces abstractas · `@abi` `@emb:cond` _PIMPL implica heap salvo storage fijo_
    3. Visibilidad de símbolos, `-fvisibility=hidden`, versionado · `@abi`
5. Interoperabilidad
    1. APIs en C: `extern "C"`, tipos opacos, propiedad entre fronteras · `@interop` `@abi` `@emb:ok`
    2. Rust: `cxx`, `bindgen`, cbindgen; reparto de propiedad · `@interop` `@safety`
    3. Python: pybind11/nanobind para herramientas de test · `@interop` `@tooling`
""",
"Diseñar la interfaz de un driver de sensor con tres implementaciones (virtual, concept y type erasure con buffer fijo), medir tamaño de código y RAM de cada una en ARM y exponer la API como C para su uso desde Rust o Python.",
["¿Cuándo elegirías `std::variant`, una jerarquía virtual o type erasure?",
 "¿Qué cambios en una clase rompen la ABI?",
 "¿Cómo pasarías la propiedad de un objeto C++ a código Rust de forma segura?",
 "Diseña una API que haga imposible confundir el orden de dos parámetros enteros."])

# ============================================================================ 17  NUEVO
mod("17-rendimiento", "Rendimiento y diseño orientado a datos",
"Módulo nuevo. Navegadores, motores de búsqueda e infraestructura a gran escala exigen razonar sobre "
"caché, asignaciones y coste de abstracciones, y medir en vez de suponer.",
"""
1. Medir: benchmarks fiables (Google Benchmark), `perf`, flame graphs, contadores de hardware · `@performance` `@tooling`
2. Memoria
    1. Jerarquía de caché, localidad, prefetching · `@performance` `@emb:cond` _MCUs sin caché: importa el acceso a flash_
    2. AoS frente a SoA, diseño orientado a datos · `@performance` `@type-design` `@emb:ok`
    3. Asignaciones: coste, pools, arenas, `pmr`, *small buffer optimization* · `@performance` `@lifetime` `@emb:ok`
    4. Contenedores: `vector` como opción por defecto, `unordered_map` frente a tablas abiertas · `@performance` `@iteration`
3. Coste de abstracciones: inlining, devirtualización, `std::function`, excepciones, RTTI · `@performance` `@emb:ok`
4. Compilador: `-O2`/`-O3`/`-Os`, LTO, PGO, vectorización, `[[likely]]`, `[[assume]]` · `@performance` `@tooling` `@emb:cond` _PGO poco práctico en target_
5. Ramas y predicción, código sin ramas, aritmética de punto fijo · `@performance` `@emb:ok`
6. Concurrencia: false sharing, contención, lock-free frente a mutex · `@performance` `@concurrency`
7. `std::simd` [26] e intrínsecos (NEON, SSE/AVX) · `@performance` `@emb:cond` _NEON en Cortex-A; Helium en M55_
""",
"Optimizar el procesado de un bloque de muestras de ADC: versión AoS ingenua, versión SoA, versión en punto fijo Q15; medir en host con Google Benchmark y en target con ciclos del DWT.",
["¿Por qué `std::vector` suele ganar a `std::list` incluso en inserciones en medio?",
 "¿Cómo escribirías un microbenchmark que el optimizador no elimine?",
 "¿Qué es SoA y cuándo mejora el rendimiento?",
 "¿Cómo medirías ciclos de una función en un Cortex-M4?"])

# ============================================================================ 18  NUEVO
mod("18-calidad", "Calidad: testing, sanitizers, fuzzing, análisis estático y build",
"Módulo nuevo y transversal: empezar en paralelo al 01. En empresas grandes la calidad está "
"automatizada; se espera dominar CMake moderno, tests, sanitizers y fuzzing.",
"""
1. CMake moderno: targets, propiedades `PUBLIC`/`PRIVATE`/`INTERFACE`, presets, toolchains, FetchContent · `@tooling` `@abi` `@emb:ok`
2. Gestión de dependencias: vcpkg, Conan, CPM · `@tooling`
3. Testing
    1. Frameworks: doctest, Catch2, GoogleTest; tests parametrizados · `@tooling`
    2. Diseño testable: dependencias inyectadas, HAL simulada en host · `@tooling` `@generic` `@emb:ok`
    3. `static_assert` como test en compilación · `@tooling` `@compile-time` `@emb:ok`
    4. Tests en hardware (HIL) y en emulador (QEMU, Renode) · `@tooling` `@emb:ok`
4. Sanitizers: ASan, UBSan, TSan, MSan; integración en CI · `@tooling` `@safety`
5. Fuzzing: libFuzzer, AFL++, OSS-Fuzz; fuzzing de parsers de protocolo · `@tooling` `@safety` `@emb:ok` _en host sobre el mismo código_
6. Análisis estático: clang-tidy, cppcheck, `-Wall -Wextra`, análisis de flujo, MISRA · `@tooling` `@safety` `@emb:ok`
7. Cobertura: gcov/llvm-cov, criterios útiles · `@tooling`
8. Revisión de código y estilo: clang-format, Core Guidelines, guías de Google/Mozilla · `@tooling`
""",
"Añadir a este repo un fuzzer libFuzzer para el parser de tramas del módulo 04, un preset con UBSan+ASan y un objetivo de cobertura; corregir lo que encuentren.",
["¿Qué diferencia hay entre `target_link_libraries(... PUBLIC ...)` y `PRIVATE`?",
 "¿Cómo testearías en host un driver que escribe en registros de hardware?",
 "¿Qué tipo de bugs encuentra el fuzzing que los tests unitarios no?",
 "¿Por qué no puedes combinar ASan y TSan en el mismo binario?"])
