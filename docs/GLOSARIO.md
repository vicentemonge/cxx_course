# Glosario

Términos usados en el curso, con el módulo donde se tratan y sus tags principales.
Ordenados alfabéticamente. Las referencias `NN` apuntan a `modules/NN-*`.

| Término | Definición | Módulos | Tags |
|---|---|---|---|
| **ABA** | Fallo en algoritmos lock-free: un valor cambia de A a B y vuelve a A entre una lectura y un CAS, que tiene éxito sin detectar el cambio. | 09 | `@memory-model` |
| **ABI** | *Application Binary Interface*: convención binaria (layout, llamadas, nombres) que debe coincidir entre código compilado por separado. | 12, 16 | `@abi` |
| **ADL** | *Argument-Dependent Lookup*: búsqueda de funciones no cualificadas en los namespaces de los tipos de los argumentos. | 03 | `@generic` |
| **Agregado** | Clase sin constructores declarados por el usuario, sin miembros privados ni bases virtuales; se inicializa con llaves miembro a miembro. | 01, 08 | `@type-design` |
| **AoS / SoA** | *Array of Structures* frente a *Structure of Arrays*: dos formas de disponer datos en memoria con distinto comportamiento de caché y vectorización. | 17 | `@performance` |
| **Awaitable / awaiter** | Objeto que se puede usar con `co_await`; el awaiter implementa `await_ready`, `await_suspend` y `await_resume`. | 10 | `@async` |
| **Borrado de tipo** (*type erasure*) | Técnica para ocultar el tipo concreto tras una interfaz uniforme sin herencia visible, como `std::function`. | 06, 16 | `@type-design` `@functional` |
| **Borrowed range** | Range cuyos iteradores siguen siendo válidos tras destruir el objeto range (por ejemplo `span`, `string_view`). | 07 | `@iteration` `@lifetime` |
| **Categoría de valor** | Clasificación de expresiones: lvalue, prvalue, xvalue (y glvalue, rvalue). Determina sobrecargas y movimiento. | 01 | `@value-sem` |
| **Centinela** (*sentinel*) | Marca de fin de un range que puede ser de tipo distinto al iterador. | 07 | `@iteration` |
| **Concept** | Predicado con nombre sobre parámetros template que restringe plantillas y mejora los errores. | 03 | `@generic` |
| **Contract** | Precondición, postcondición o aserción declarada en el lenguaje (`pre`, `post`, `contract_assert`) [26]. | 05, 14 | `@errors` `@safety` |
| **Copy elision** | Omisión de copias y movimientos al construir desde un prvalue; garantizada desde C++17. | 01 | `@value-sem` `@performance` |
| **CPO** | *Customization Point Object*: objeto función que encapsula un punto de personalización evitando problemas de ADL. | 03 | `@generic` |
| **CRTP** | *Curiously Recurring Template Pattern*: una clase deriva de una plantilla instanciada con ella misma para polimorfismo estático. | 08, 16 | `@generic` |
| **CTAD** | *Class Template Argument Deduction*: deducción de los argumentos de una plantilla de clase desde el constructor [17]. | 03 | `@generic` |
| **Dangling** | Referencia, puntero, vista o iterador que apunta a un objeto cuyo tiempo de vida terminó. | 04, 15 | `@lifetime` `@safety` |
| **Data race** | Dos accesos concurrentes al mismo objeto, al menos uno de escritura, sin sincronización. Es UB. | 09, 15 | `@memory-model` `@safety` |
| **Deducing this** | Parámetro objeto explícito (`this Self&& self`) en funciones miembro [23]. | 08 | `@generic` |
| **Designated initializer** | Inicialización de agregados nombrando los miembros (`.campo = v`), en orden de declaración [20]. | 08 | `@type-design` |
| **Detection idiom** | Técnica SFINAE con `void_t` para comprobar si una expresión es válida para un tipo. | 03 | `@generic` |
| **Comportamiento erróneo** (*erroneous behaviour*) | Categoría de C++26 para lecturas de variables sin inicializar: bien definido pero diagnosticable, en vez de UB. | 14, 15 | `@safety` |
| **False sharing** | Degradación de rendimiento cuando hilos distintos escriben en variables que comparten línea de caché. | 09, 17 | `@concurrency` `@performance` |
| **Fold expression** | Expansión de un parameter pack con un operador binario (`(xs + ...)`) [17]. | 03 | `@generic` |
| **Forwarding reference** | Parámetro `T&&` con `T` deducido; se liga a lvalues y rvalues y se reenvía con `std::forward`. | 01 | `@value-sem` |
| **Freestanding** | Implementación de C++ sin sistema operativo, con un subconjunto de la biblioteca estándar. | 13 | `@abi` `@emb:ok` |
| **Fuzzing** | Pruebas con entradas generadas automáticamente para descubrir fallos y vulnerabilidades. | 18 | `@tooling` `@safety` |
| **Garantías de excepción** | Nothrow, fuerte (todo o nada) y básica (invariantes preservados, sin fugas). | 05 | `@errors` |
| **HALO** | *Heap Allocation eLision Optimization*: el compilador evita asignar en heap el frame de una coroutine. | 10 | `@async` `@performance` |
| **Happens-before** | Relación de orden del modelo de memoria que garantiza visibilidad entre hilos. | 09 | `@memory-model` |
| **Hardening** | Comprobaciones activadas en la biblioteca estándar (límites, precondiciones) para convertir UB en fallos controlados. | 15 | `@safety` |
| **IIFE** | *Immediately Invoked Function Expression*: lambda llamada en el acto para inicializar una constante. | 06 | `@functional` |
| **Implicit-lifetime type** | Tipo cuyos objetos pueden empezar a existir implícitamente al obtener almacenamiento (por ejemplo con `malloc` o `memcpy`) [20]. | 15 | `@lifetime` |
| **Lock-free** | Algoritmo en el que algún hilo progresa siempre, sin usar mutex. | 09 | `@memory-model` |
| **Lookup en dos fases** | Los nombres no dependientes se resuelven al definir la plantilla y los dependientes al instanciarla. | 03 | `@generic` |
| **LTO** | *Link-Time Optimization*: optimización entre unidades de traducción en el enlace. | 13, 17 | `@performance` `@tooling` |
| **MMIO** | *Memory-Mapped I/O*: registros de periféricos accesibles como direcciones de memoria. | 13 | `@emb:ok` |
| **Módulo** (C++20) | Unidad de código con interfaz exportada que sustituye al modelo de `#include`. | 12 | `@abi` |
| **Niebloid** | Objeto función de `std::ranges` que no participa en ADL. | 03, 07 | `@generic` |
| **NRVO** | *Named Return Value Optimization*: elisión de la copia de una variable local devuelta; no garantizada. | 01 | `@value-sem` |
| **NSDMI** | *Non-Static Data Member Initializer*: valor por defecto de un miembro en su declaración [11]. | 01 | `@type-design` |
| **NTTP** | *Non-Type Template Parameter*: parámetro template que es un valor (`template <int N>`). | 02 | `@generic` `@compile-time` |
| **ODR** | *One Definition Rule*: cada entidad debe tener una única definición en el programa. | 12 | `@abi` |
| **Orden de memoria** | `relaxed`, `acquire`, `release`, `acq_rel`, `seq_cst`: garantías de orden de una operación atómica. | 09 | `@memory-model` |
| **Overloaded** | Patrón que combina varias lambdas en un objeto con `operator()` sobrecargado, típico con `std::visit`. | 04, 06 | `@functional` |
| **PGO** | *Profile-Guided Optimization*: optimización guiada por perfiles de ejecución reales. | 17 | `@performance` |
| **PIMPL** | *Pointer to IMPLementation*: ocultar los miembros privados tras un puntero para estabilizar la ABI. | 16 | `@abi` |
| **pmr** | *Polymorphic Memory Resources*: contenedores que reciben un recurso de memoria en runtime [17]. | 13, 17 | `@lifetime` `@performance` |
| **Projection** | Función aplicada a los elementos antes de compararlos en un algoritmo de ranges. | 07 | `@iteration` |
| **RAII** | *Resource Acquisition Is Initialization*: el tiempo de vida de un recurso se ata al de un objeto. | 01, 05 | `@lifetime` |
| **Reflexión estática** | Inspección de entidades del programa en compilación (`^^`, `std::meta::info`) [26]. | 14 | `@compile-time` |
| **Rule of Zero / Five** | Si una clase gestiona un recurso define los cinco miembros especiales; si no, ninguno. | 01 | `@lifetime` `@value-sem` |
| **Sanitizer** | Instrumentación del compilador que detecta errores en runtime (ASan, UBSan, TSan, MSan). | 15, 18 | `@tooling` `@safety` |
| **SBO / SSO** | *Small Buffer/String Optimization*: almacenar objetos pequeños dentro del propio objeto para evitar heap. | 06, 11, 17 | `@performance` |
| **SFINAE** | *Substitution Failure Is Not An Error*: un fallo al sustituir parámetros template descarta la sobrecarga sin error. | 03 | `@generic` |
| **Slicing** | Pérdida de la parte derivada al copiar un objeto derivado en uno de la clase base. | 08 | `@type-design` |
| **SPSC** | *Single Producer, Single Consumer*: cola con un productor y un consumidor, implementable sin locks. | 09 | `@memory-model` `@emb:ok` |
| **Strict aliasing** | Regla que prohíbe acceder a un objeto a través de un tipo no compatible; violarla es UB. | 13, 15 | `@safety` |
| **Structured binding** | Desestructuración de tuplas, arrays y structs en variables con nombre (`auto [a, b] = ...`) [17]. | 08 | `@type-design` |
| **Subsunción** | Relación entre restricciones de concepts que permite elegir la sobrecarga más restringida. | 03 | `@generic` |
| **Tipo fuerte** (*strong typedef*) | Envoltorio de un tipo primitivo que impide mezclar valores con distinto significado. | 04, 16 | `@type-design` |
| **Tipo vocabulario** | Tipo estándar que expresa intención en interfaces: `optional`, `variant`, `expected`, `span`. | 04 | `@type-design` |
| **Transferencia simétrica** | Reanudar otra coroutine directamente desde `await_suspend` sin crecer la pila. | 10 | `@async` |
| **Trivialmente copiable** | Tipo que puede copiarse byte a byte con `memcpy`. | 15 | `@type-design` `@interop` |
| **UB** (comportamiento indefinido) | Operación sin requisitos en el estándar; el compilador puede asumir que nunca ocurre. | 15 | `@safety` |
| **View** | Range ligero, normalmente perezoso y no propietario, que se compone con `|`. | 07 | `@iteration` |
| **vtable** | Tabla de punteros a función usada para el despacho de funciones virtuales. | 08, 16 | `@type-design` `@performance` |
