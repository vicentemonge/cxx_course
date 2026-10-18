# Entrevista simulada — Senior C++ Engineer, Firefox Platform (Mozilla)

> **Aviso.** Entrevista ficticia, inspirada en el formato habitual de las grandes empresas
> tecnológicas: screening, coding, code review, concurrencia, diseño de sistemas, rendimiento y
> comportamiento. No reproduce el proceso real de Mozilla ni de ninguna otra empresa. El nivel
> está calibrado a propósito por encima de la media.

**Puesto ficticio:** Senior Software Engineer, C++ — equipo de IPC y procesos de contenido.
El equipo mantiene la capa que comunica el proceso principal del navegador con procesos de contenido
aislados en sandbox. Todo dato que llega de un proceso de contenido se considera **hostil**.

## Cómo usar este documento

1. Haz cada ronda con temporizador y sin consultar nada. Escribe las respuestas antes de abrir los
   bloques **Solucionario**.
2. Para el código, escribe en un fichero aparte y compílalo con los warnings del curso y con sanitizers.
3. Puntúa cada ronda con la [rúbrica](#rúbrica-y-decisión) siendo honesto: el entrevistador real no
   da puntos por "casi".
4. Variante recomendada: pídele a Claude que actúe de entrevistador y que no te dé pistas.

| Ronda | Duración | Tema | Módulos del curso |
|---|---|---|---|
| 0 | 30 min | Screening técnico | 01, 04, 08, 09 |
| 1 | 45 min | Coding: LRU cache | 03, 04, 05, 17 |
| 2 | 45 min | Code review con código hostil | 01, 05, 09, 15 |
| 3 | 45 min | Concurrencia y modelo de memoria | 09, 15 |
| 4 | 60 min | Diseño de sistema | 09, 15, 16, 17, 18 |
| 5 | 45 min | Rendimiento y sistemas embebidos | 13, 15, 17 |
| 6 | 30 min | Comportamiento y liderazgo | — |

---

## Ronda 0 — Screening técnico (30 min)

Ritmo rápido: unos dos minutos por pregunta. El entrevistador corta las respuestas vagas.

1. ¿Cuánto ocupa una clase vacía? ¿Y un miembro de tipo clase vacía marcado `[[no_unique_address]]`?
2. ¿Qué hace exactamente `std::move`? ¿Genera alguna instrucción?
3. ¿Qué sobrecarga se llama y por qué?
   ```cpp
   void f(const std::string&);
   void f(std::string&&);
   void g(std::string&& s) { f(s); }
   ```
4. En C++17, ¿es UB `i = i++ + 1;`? ¿Y en C++11?
5. ¿Qué imprime esto, o qué falla?
   ```cpp
   std::vector<std::vector<int>> v;
   v.emplace_back(10);
   v.push_back(10);
   ```
6. ¿Es seguro este código? Justifica.
   ```cpp
   std::string_view sv = std::string("abc") + "d";
   std::cout << sv;
   ```
7. ¿Es `std::shared_ptr` thread-safe? Sé preciso.
8. ¿Cuándo un destructor de clase base puede ser **no** virtual con seguridad?
9. ¿Qué garantiza el estándar sobre la inicialización de una variable `static` local en presencia de hilos?
10. ¿Por qué `std::vector<T>::push_back` puede copiar en vez de mover al crecer?
11. Diferencia entre `map::operator[]`, `at` y `find` en cuanto a efectos secundarios y requisitos sobre `T`.
12. ¿Qué ocurre si una excepción escapa de un destructor?

<details>
<summary><b>Solucionario — Ronda 0</b></summary>

1. Al menos 1 byte, para que objetos distintos tengan direcciones distintas. Con `[[no_unique_address]]` puede ocupar 0 bytes dentro de la clase contenedora (EBO sin herencia). MSVC necesita `[[msvc::no_unique_address]]`.
2. Es un `static_cast<T&&>`: convierte la expresión en xvalue para que se elija la sobrecarga de movimiento. No mueve nada ni genera código por sí mismo.
3. `f(const std::string&)`. `s` tiene nombre, así que es un lvalue aunque su tipo sea `std::string&&`. Hace falta `f(std::move(s))`. **Señal roja** si el candidato dice `&&`.
4. En C++17 está bien definido: el operando derecho de `=` se secuencia antes que el izquierdo, así que `i` acaba valiendo su valor original + 1. En C++11/14 es UB por modificaciones no secuenciadas.
5. `emplace_back(10)` construye directamente un `vector<int>` con 10 ceros (llama al constructor `explicit`). `push_back(10)` no compila, porque necesita una conversión implícita y ese constructor es `explicit`. La lección es que `emplace_back` salta `explicit`, y eso es un riesgo en revisiones de código.
6. No. El `std::string` temporal se destruye al final de la expresión completa y `sv` queda colgando: es UB. Clang avisa con `-Wdangling-gsl`.
7. El bloque de control sí lo es: los contadores son atómicos y copiar o destruir **instancias distintas** que comparten objeto desde varios hilos es seguro. El objeto apuntado no está protegido. Modificar **la misma instancia** de `shared_ptr` desde dos hilos es un data race; para eso existe `std::atomic<std::shared_ptr<T>>` [20].
8. Cuando nunca se destruye un derivado a través de un puntero a la base. La forma idiomática es un destructor `protected` y no virtual, que impide `delete base_ptr` en compilación.
9. Inicialización exactamente una vez y thread-safe ("magic statics", C++11). Los demás hilos esperan. Con `-fno-threadsafe-statics`, habitual en firmware, esta garantía desaparece.
10. Porque si el constructor de movimiento puede lanzar, mover rompería la garantía fuerte de `push_back`: elementos ya movidos no se pueden recuperar. `std::move_if_noexcept` elige copiar salvo que el movimiento sea `noexcept` o no exista copia.
11. `operator[]` inserta un elemento construido por defecto si no existe, así que exige `T` construible por defecto y no funciona en `const map`. `at` lanza `std::out_of_range`. `find` no tiene efectos secundarios. En código concurrente o con mapas `const`, `operator[]` es un bug habitual.
12. Los destructores son `noexcept` implícitamente desde C++11: se llama a `std::terminate`. Si se declara `noexcept(false)` y la excepción escapa durante el unwinding de otra, también hay `std::terminate`.

**Corte:** menos de 9 correctas → no se pasa a las siguientes rondas.
</details>

---

## Ronda 1 — Coding: LRU cache (45 min)

> Implementa `LruCache<K, V>` con capacidad fija, `get(key)` y `put(key, value)` en O(1)
> amortizado. Cuando la caché está llena, `put` de una clave nueva expulsa la menos usada
> recientemente. Escribe tests.

Dispones de 25 minutos para la implementación. El resto del tiempo es para seguimientos, que el
entrevistador plantea de uno en uno y sin avisar:

1. ¿Qué devuelve tu `get`: copia, referencia, puntero, `optional`? Defiende la decisión.
2. Haz que `put` no asigne memoria cuando la caché está llena.
3. ¿Qué garantía de excepción da tu `put`? Haz que dé la fuerte.
4. Hazla segura para varios hilos. ¿Sirve un `std::shared_mutex` con `get` como lectura?
5. Las claves son `std::string` y los llamantes tienen `std::string_view`. Evita construir un `std::string` en cada `get`.
6. ¿Qué cambiarías si fuera el caché de un proceso con 10⁸ consultas por segundo en 64 núcleos?

<details>
<summary><b>Solucionario — Ronda 1</b></summary>

Solución de referencia compilada y testeada: [`solucion/lru_cache.hpp`](solucion/lru_cache.hpp),
tests en [`solucion/test_lru_cache.cpp`](solucion/test_lru_cache.cpp).

Estructura esperada: `std::list<std::pair<K, V>>` con el más reciente al frente y
`std::unordered_map<K, list::iterator>`. `get` mueve el nodo al frente con `splice` en O(1), sin asignar.

1. **Retorno.** Una referencia o un puntero son baratos, pero quedan invalidados por el siguiente `put` que expulse ese elemento; hay que documentarlo. `optional<V>` copia, pero es seguro, y es la única opción válida en la versión concurrente. Se espera que el candidato **plantee** el trade-off sin que se lo pidan.
2. **Sin asignaciones.** Reutilizar el último nodo: `splice` al frente, `unordered_map::extract` del nodo del índice [17], cambiar la clave con `node.key()` y reinsertarlo. Ni la lista ni el mapa asignan. Muy pocos candidatos conocen los *node handles*; es una señal fuerte de nivel.
3. **Excepciones.** Insertar primero en la lista y luego en el índice; si el índice lanza, deshacer con `pop_front`. Expulsar *antes* de insertar rompe la garantía fuerte, porque se pierde un elemento si la inserción falla.
4. **Concurrencia.** `shared_mutex` **no** sirve: `get` modifica el orden de la lista, así que es una escritura. Detectarlo es la clave de la pregunta. Respuesta mínima: un `mutex` y devolver copias. Respuesta senior: *sharding* (N cachés independientes, seleccionadas por hash), o LRU aproximado (CLOCK, *segmented LRU*) para que `get` no necesite exclusión.
5. **Búsqueda heterogénea** [20]: un hash y un `equal_to<>` *transparentes* (`using is_transparent = void;`), con lo que `unordered_map::find(string_view)` funciona sin crear un `std::string`.
6. **Escala.** El LRU estricto es un punto de contención global. Hay que pasar a *sharding* por núcleo, actualizar la recencia de forma muestreada o diferida (buffers de accesos que se aplican por lotes, como Caffeine o CacheLib), usar memoria contigua en vez de `std::list` (nodos dispersos: un fallo de caché por paso) y eliminar el `shared_ptr` del camino caliente. Mencionar CacheLib (Meta) o el diseño de Caffeine suma.

**Señales rojas:** O(n) en `get`, usar `std::list::remove`, no escribir tests o no pensar en capacidad 1 y en actualizar una clave existente.
</details>

---

## Ronda 2 — Code review con código hostil (45 min)

> Este código se usa en el proceso principal del navegador para recibir mensajes de procesos de
> contenido. Los procesos de contenido pueden estar comprometidos. Encuentra todos los problemas
> que puedas, clasifícalos por gravedad y propón la corrección. Hay más de 10.

```cpp
// ipc_queue.h
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <deque>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

struct MessageHeader {
    uint32_t type;
    uint32_t count;     // número de elementos uint32_t en el payload
};

class Message {
public:
    Message(std::string_view origin, const uint8_t* data, size_t len)
        : origin_(origin), data_(new uint8_t[len]), len_(len) {
        std::memcpy(data_, data, len + 1);
    }
    ~Message() { delete data_; }

    std::string_view origin() const { return origin_; }
    const uint8_t* data() const { return data_; }
    size_t size() const { return len_; }

private:
    std::string_view origin_;
    uint8_t* data_;
    size_t len_;
};

class Handler {
public:
    virtual void on_message(const Message&) = 0;
};

class MessageQueue {
public:
    void push(Message m) {
        std::lock_guard lock(mutex_);
        queue_.push_back(std::move(m));
        cv_.notify_one();
    }

    const Message& pop() {
        std::unique_lock lock(mutex_);
        cv_.wait(lock);
        const Message& m = queue_.front();
        queue_.pop_front();
        return m;
    }

    size_t size() const { return queue_.size(); }

    void add_handler(Handler* h) { handlers_.push_back(h); }

    void dispatch_all() {
        for (size_t i = queue_.size() - 1; i >= 0; --i)
            for (Handler* h : handlers_) h->on_message(queue_[i]);
    }

    ~MessageQueue() { for (Handler* h : handlers_) delete h; }

private:
    std::deque<Message> queue_;
    std::vector<Handler*> handlers_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
};

// Deserializa un mensaje recibido de un proceso de contenido
Message parse(const uint8_t* buf, size_t buf_len, const std::string& origin) {
    auto* hdr = reinterpret_cast<const MessageHeader*>(buf);
    size_t payload = hdr->count * sizeof(uint32_t);
    return Message(origin + ":" + std::to_string(hdr->type),
                   buf + sizeof(MessageHeader), payload);
}
```

<details>
<summary><b>Solucionario — Ronda 2</b></summary>

Versión corregida y testeada: [`solucion/ipc_queue.hpp`](solucion/ipc_queue.hpp), tests en
[`solucion/test_ipc_queue.cpp`](solucion/test_ipc_queue.cpp).

| # | Gravedad | Problema | Corrección |
|---|---|---|---|
| B12 | 🔴 Crítica (seguridad) | `parse` no comprueba que `payload` quepa en `buf_len`: lectura fuera de límites con datos de un proceso hostil, lo que filtra memoria del proceso principal. Con un `count` enorme, `new uint8_t[...]` provoca `bad_alloc` o un abort: DoS del navegador. Con `size_t` de 32 bits, `count * 4` puede desbordar. | Validar `buf_len >= sizeof(header)`, poner un límite máximo de payload, usar aritmética comprobada y devolver `expected`. |
| B11 | 🔴 Crítica (seguridad/UB) | `reinterpret_cast` del buffer a `MessageHeader*`: violación de *strict aliasing*, posible desalineación y lectura sin comprobar tamaño. | `std::memcpy` a un `MessageHeader` local tras comprobar el tamaño. |
| B1 | 🔴 Crítica | `memcpy(..., len + 1)`: desbordamiento de heap de 1 byte en escritura y lectura fuera de límites del origen. | `len`, o mejor `std::vector`. |
| B3 | 🔴 Crítica | `Message` tiene destructor propio pero copia implícita (generación deprecada): `push_back(std::move(m))` **copia**, porque no hay constructor de movimiento implícito, y hay *double free*. | Rule of Zero: `std::vector<uint8_t>` y `std::string`. |
| B7 | 🔴 Crítica | `pop` devuelve una referencia a un elemento destruido por `pop_front`: uso tras liberar. | Devolver `Message` por valor. |
| B4 | 🔴 Crítica | `origin_` es un `string_view` a un temporal (`origin + ":" + ...`): colgante en cuanto `parse` retorna. | Guardar `std::string`. |
| B2 | 🟠 Alta | `delete` sobre memoria de `new[]`: UB. | `delete[]`, o mejor ningún `new`. |
| B6 | 🟠 Alta | `cv_.wait(lock)` sin predicado: despertares espurios y notificaciones perdidas (si el push ocurre antes del wait, se bloquea para siempre). | `wait(lock, pred)`. |
| B8 | 🟠 Alta | `size()` lee `queue_` sin lock: data race, UB. | Bloquear. |
| B9 | 🟠 Alta | `add_handler` y `dispatch_all` no bloquean; propiedad ambigua con un puntero crudo que se borra en el destructor. | `unique_ptr<Handler>`, todo bajo lock. |
| B10 | 🟠 Alta | `for (size_t i = size() - 1; i >= 0; --i)`: `i >= 0` siempre es cierto con `size_t`. Bucle infinito y acceso fuera de límites; con la cola vacía, `size() - 1` da la vuelta. | Iteradores inversos. |
| B5 | 🟠 Alta | `Handler` sin destructor virtual y se destruye vía `Handler*`: UB. | `virtual ~Handler() = default;`. |
| B13 | 🟡 Media | `dispatch_all`, una vez arreglado con lock, no debe llamar a los handlers con el mutex tomado: un handler que haga `push` provoca deadlock. | Sacar los mensajes bajo lock y despachar fuera de él. |
| B14 | 🟢 Baja | `notify_one` con el lock tomado: el hilo despertado se bloquea de inmediato. | Notificar tras liberar. |

**Criterio:**
- **Strong hire:** encuentra B11 y B12 en los primeros 10 minutos y los razona como problemas de seguridad entre procesos, más al menos 9 en total.
- **No hire, aunque encuentre todo lo demás:** no detecta B12.
- **Bonus:** proponer fuzzing del parser con libFuzzer (está hecho en [`fuzz/`](../../fuzz) para el parser del módulo 04), mencionar que en Firefox estas validaciones se generan desde la definición del protocolo (IPDL), o usar `std::span` en la firma.
</details>

---

## Ronda 3 — Concurrencia y modelo de memoria (45 min)

1. **Store buffering.** `x` e `y` son `std::atomic<int>` inicializados a 0.
   ```cpp
   // Hilo 1                     // Hilo 2
   x.store(1, MO);               y.store(1, MO);
   r1 = y.load(MO);              r2 = x.load(MO);
   ```
   ¿Es posible `r1 == 0 && r2 == 0` con `MO = relaxed`? ¿Con stores `release` y loads `acquire`? ¿Con `seq_cst`? Explica el porqué en términos de hardware.

2. **Publicación rota.** ¿Qué falla y cómo se arregla con el mínimo coste?
   ```cpp
   Config* g_config = nullptr;
   std::atomic<bool> g_ready{false};

   void productor() { g_config = new Config{cargar()}; g_ready.store(true, std::memory_order_relaxed); }
   void consumidor() { while (!g_ready.load(std::memory_order_relaxed)) {} usar(*g_config); }
   ```

3. **Double-checked locking.** Encuentra el bug y da tres correcciones de menor a mayor complejidad.
   ```cpp
   Servicio* instancia() {
       static Servicio* p = nullptr;
       static std::mutex m;
       if (!p) {
           std::lock_guard lk{m};
           if (!p) p = new Servicio();
       }
       return p;
   }
   ```

4. **`shared_ptr` por dentro.** Al destruir una copia, el contador se decrementa. ¿Qué orden de memoria necesita ese decremento y por qué el último propietario necesita algo más antes de `delete`?

5. En el ring buffer SPSC del [módulo 09](../../modules/09-concurrencia/examples/embedded/spsc_ring.hpp), ¿por qué el productor puede leer `head_` con `relaxed`? Encuentra un problema de rendimiento en su layout.

6. Un compañero propone `volatile bool g_stop;` para parar un hilo trabajador porque "en x86 funciona". Respuesta en dos frases para el code review.

<details>
<summary><b>Solucionario — Ronda 3</b></summary>

1. Con `relaxed`: **sí**. Con `release`/`acquire`: **también sí**, y es la trampa de la pregunta. Acquire/release solo ordena respecto a la variable que sincroniza; aquí ningún load lee el store del otro hilo, así que no hay *synchronizes-with*. Solo con `seq_cst` es imposible, porque existe un orden total único. En hardware, cada núcleo tiene un *store buffer*: el store queda en el buffer, el load se adelanta y lee el valor antiguo de la caché. Ocurre incluso en x86 (TSO), y es el único reordenamiento que TSO permite. `seq_cst` en x86 emite `mfence` o `xchg` en el store.
2. Con `relaxed` no hay *happens-before*: el consumidor puede ver `g_ready == true` y leer un `Config` a medio construir, o un `g_config` aún nulo, porque el compilador o la CPU reordenan. Además, `g_config` no atómico es un data race. Corrección mínima: `store(true, release)` y `load(acquire)`. Más limpio: un único `std::atomic<Config*>` con release/acquire. En ARM esto importa de verdad (orden débil); en x86 el bug puede no manifestarse nunca hasta que el compilador reordena.
3. Lectura no sincronizada de `p` fuera del lock: data race y UB. Puede ver el puntero antes de que el objeto esté construido. Correcciones: (a) `static Servicio s; return &s;` (magic statics, la mejor); (b) `std::call_once`; (c) `std::atomic<Servicio*>` con load `acquire` fuera del lock y store `release` dentro. Bonus: ese `new` nunca se libera, lo que puede ser intencionado para evitar el orden de destrucción de estáticos.
4. Los incrementos pueden ser `relaxed`. El decremento necesita `release`, para que las escrituras de este hilo sobre el objeto ocurran antes de que otro hilo lo destruya. El hilo que lleva el contador a 0 necesita `acquire` (una barrera `atomic_thread_fence(acquire)` tras un `fetch_sub(release)`, o un `fetch_sub(acq_rel)`) para ver todas las escrituras de los demás propietarios antes de ejecutar el destructor. Sin esto, el destructor puede leer estado obsoleto.
5. Solo el productor escribe `head_`, así que lee su propio último valor: no hay nada que sincronizar. El `release` en el store de `head_` publica el dato y el `acquire` en la lectura de `tail_` garantiza que el consumidor ya terminó de leer la ranura antes de reutilizarla. **Rendimiento:** `head_` y `tail_` comparten línea de caché (*false sharing*): cada escritura de un lado invalida la línea del otro. Se corrige con `alignas(std::hardware_destructive_interference_size)` o con 64 bytes fijos. En Cortex-M sin caché no aplica; en Cortex-A sí.
6. `volatile` no da atomicidad ni orden entre hilos: el acceso concurrente es un data race (UB) y el compilador puede seguir reordenando el resto de accesos alrededor. Usa `std::atomic<bool>` o, mejor, `std::jthread` con `std::stop_token`.

**Corte:** fallar las preguntas 1 o 2 es suficiente para un *no hire* en un equipo de IPC.
</details>

---

## Ronda 4 — Diseño de sistema (60 min)

> Diseña una biblioteca de **telemetría de rendimiento** para el navegador. Cada proceso de
> contenido (en sandbox, potencialmente comprometido) registra eventos de rendimiento: marcas de
> tiempo, tipo, hasta 64 bytes de datos. El proceso principal los recoge y los envía al servidor.
>
> Requisitos:
> - Camino caliente sin asignaciones de memoria, sin locks y por debajo de 50 ns por evento.
> - Si el proceso de contenido se cuelga o se bloquea, no se pierden los eventos ya registrados.
> - El proceso principal **no puede confiar** en nada de lo que escribe el proceso de contenido.
> - El formato debe poder evolucionar sin romper versiones antiguas del lector.
> - El lector del proceso principal se está reescribiendo en Rust.

Se espera que el candidato conduzca la conversación: preguntas de aclaración, propuesta,
alternativas, puntos de fallo y cómo lo probaría.

<details>
<summary><b>Solucionario — Ronda 4: lo que debe aparecer</b></summary>

**Arquitectura base.** Un ring buffer en **memoria compartida** por proceso de contenido, creado por
el proceso principal y mapeado en ambos. Un solo productor por buffer: uno por hilo, o un índice
atómico con `fetch_add` si hay varios hilos. El lector está en el proceso principal.

**Puntos que separan niveles:**

1. **Nada de punteros en memoria compartida**, solo offsets: el mapeo tiene direcciones distintas en cada proceso. Los registros son tipos *trivially copyable* y de *standard layout*, con `static_assert` sobre tamaño, alineación y offsets ([módulo 15](../../modules/15-ub-seguridad)).
2. **`std::atomic` en memoria compartida** solo si `is_always_lock_free`: un atómico implementado con lock no funciona entre procesos. Hay que razonar que los atómicos lock-free de 32 y 64 bits son *address-free* en la práctica.
3. **Consistencia ante caídas.** Escribir el registro y publicar después con un número de secuencia o *commit* en `release`. El lector descarta los registros sin confirmar. Que el productor muera a mitad de escritura no corrompe nada, porque la memoria sobrevive al proceso.
4. **Lector defensivo**, que es la clave para un equipo de seguridad. El productor puede escribir **cualquier cosa en cualquier momento**, incluso mientras el lector lee (TOCTOU). El lector:
   - copia cada registro a memoria privada **antes** de validarlo (validar en sitio y usar después es un TOCTOU explotable);
   - trata los índices de cabeza y cola como no confiables: comprueba rangos, usa aritmética modular y limita lo que lee por ciclo;
   - no sigue nunca offsets ni longitudes sin acotar;
   - hace fuzzing del lector con un productor adversarial ([módulo 18](../../modules/18-calidad)).
5. **Contrapresión.** Con el buffer lleno, el productor **descarta** y cuenta los descartes; nunca bloquea al proceso de contenido. Se reporta el contador de descartes como métrica.
6. **Tiempo.** Reloj monotónico (`steady_clock` o TSC con calibración), no `system_clock`. Las marcas de tiempo del proceso de contenido tampoco son de fiar: el lector añade la suya.
7. **Versionado.** Cabecera del buffer con *magic*, versión y tamaño de registro. Registros con tipo y longitud (TLV) y campos solo añadidos al final; el lector ignora tipos desconocidos. Es el mismo problema que ABI e interop ([módulo 16](../../modules/16-diseno-apis)).
8. **Interop con Rust.** El formato se define una sola vez (IDL, o una cabecera C con `static_assert`) y se generan ambos lados con `bindgen`/`cbindgen`. El lector Rust usa `read_volatile` o copias, nunca referencias `&T` a memoria compartida mutable, porque eso sería UB en Rust.
9. **Rendimiento del productor.** Sin `seq_cst` en el camino caliente, solo `release`. Cabecera y datos en líneas de caché distintas. Medido con un microbenchmark ([módulo 17](../../modules/17-rendimiento)).
10. **Pruebas.** Tests de estrés con TSan en el modo de hilos, fuzzing del lector, *fault injection* (matar el productor en cada punto de la escritura) y tests de compatibilidad entre versiones de formato.

**Strong hire:** plantea por iniciativa propia los puntos 3, 4 y 7, y discute alternativas
(un buffer por hilo frente a MPSC; `memfd`/`shm_open` frente a `mmap` anónimo heredado).

**No hire:** propone un mutex compartido entre procesos (un proceso hostil puede tomarlo y no
soltarlo nunca), usa punteros en memoria compartida o valida en sitio sin copiar.
</details>

---

## Ronda 5 — Rendimiento y sistemas embebidos (45 min)

Ronda adaptada al CV del candidato (firmware y C++ en microcontroladores).

1. Esta función no se vectoriza como esperabas con `-O3`. ¿Por qué? Da dos correcciones.
   ```cpp
   void escalar(float* out, const float* in, float k, int n) {
       for (int i = 0; i < n; ++i) out[i] = in[i] * k;
   }
   ```
2. Tras migrar un firmware de C a C++, el binario crece 40 KB y no cabe en flash. ¿Cómo lo diagnosticas, paso a paso, y cuáles son los cinco sospechosos habituales?
3. Un compañero usa una tabla de `std::function<void()>` como vectores de callbacks de interrupción. Analiza los problemas y propón una alternativa.
4. Un driver funciona con `-O0` y falla con `-O2`. Da tres causas posibles, de más a menos probable.
5. ¿Cómo medirías el número exacto de ciclos de una función en un Cortex-M4? ¿Qué puede falsear la medida?
6. ¿Usarías `std::vector` en un firmware sin heap? ¿Y `std::array`, `std::span`, `std::optional`, `std::variant`, `std::function`, `std::string`? Una frase por cada uno.

<details>
<summary><b>Solucionario — Ronda 5</b></summary>

1. **Aliasing**: `out` e `in` pueden solaparse. El compilador no puede asumir lo contrario, así que no vectoriza o genera dos versiones del bucle con una comprobación de solapamiento en runtime (coste extra y código más grande, crítico en flash). Correcciones: `__restrict` en los punteros (extensión de GCC/Clang), o `#pragma GCC ivdep` / `#pragma clang loop vectorize(assume_safety)` si se garantiza que no hay solapamiento. Bonus: verificarlo con `-fopt-info-vec-missed` (GCC) o `-Rpass-missed=loop-vectorize` (Clang), y mencionar que en Cortex-M4 no hay SIMD de coma flotante: la pregunta solo tiene sentido en Cortex-A (NEON) o M55 (Helium).
2. Diagnóstico: `arm-none-eabi-size`, comparar los `.map`, `nm --size-sort -C` o Bloaty por símbolo y por unidad de compilación. Sospechosos: (1) excepciones (tablas de unwind, `__cxa_*`); (2) RTTI y `typeinfo`; (3) `iostream`/locale, que arrastra decenas de KB; (4) `printf` con soporte de coma flotante o `std::to_string`; (5) explosión de instanciaciones de plantillas, o `-O2` frente a `-Os`. Remedios: `-fno-exceptions -fno-rtti`, `-ffunction-sections -fdata-sections -Wl,--gc-sections`, LTO, newlib-nano y revisar los inlines.
3. `std::function` puede asignar en heap, no es `noexcept` al invocar (lanza `bad_function_call` si está vacía), su copia no es segura desde una ISR y tiene una indirección extra con tamaño variable. Si se reasigna fuera de la ISR mientras se ejecuta dentro, hay data race. Alternativa: punteros a función con un `void* contexto` (ABI de C, cero coste), una tabla `constexpr` resuelta en compilación, o `function_ref`/type erasure con buffer fijo y trivialmente copiable ([módulos 06](../../modules/06-lambdas) y [16](../../modules/16-diseno-apis)). Para cambiar un callback en caliente, `std::atomic` de puntero.
4. (1) Falta `volatile` en un registro MMIO: el compilador saca la lectura del bucle o elimina escrituras "redundantes". (2) UB que `-O2` explota: aliasing de buffers, overflow con signo en un contador, desplazamientos de 32 bits, lectura de variables sin inicializar. (3) Falta de barreras de memoria o de compilador frente a DMA o ISR (`__DSB`, `std::atomic_signal_fence`), o retardos de *busy-wait* eliminados por el optimizador.
5. Contador `DWT->CYCCNT`: habilitar `TRCENA` en `CoreDebug->DEMCR` y `CYCCNTENA`, y leer antes y después. Falsean la medida: estados de espera de flash y el *ART accelerator* o la caché (primera ejecución frente a las siguientes), interrupciones durante la medida, el propio coste de leer el contador y el pipeline. Hay que repetir, deshabilitar interrupciones y descontar la sobrecarga de una medida vacía.
6. `vector`: no, salvo con `pmr` sobre un buffer estático o con `inplace_vector`/ETL. `array`: sí. `span`: sí, sustituye a puntero+longitud. `optional`: sí, sin heap. `variant`: sí, sin heap; cuidado con `visit` y el tamaño de código si hay muchas alternativas. `function`: no en general, por el heap. `string`: no salvo cadenas cortas dentro del SSO; mejor `string_view` y buffers fijos.
</details>

---

## Ronda 6 — Comportamiento y liderazgo (30 min)

El candidato lidera un equipo, así que esta ronda pesa tanto como las técnicas. Se espera el
formato STAR (situación, tarea, acción, resultado), con datos concretos y sin culpar a otros.

1. Cuéntame una decisión técnica tuya que resultó equivocada. ¿Cómo te diste cuenta y qué cambiaste?
2. Tu equipo quiere migrar el firmware de C a C++20. El ingeniero más veterano se opone con argumentos de tamaño de código y de riesgo. ¿Cómo gestionas la decisión?
3. Un bug que llegó a producción por un fallo de proceso de tu equipo. ¿Qué cambió después?
4. Cuéntame cómo has hecho crecer técnicamente a alguien que escribía "C con clases".
5. Un PM presiona para saltarse la revisión de seguridad para llegar a una fecha. ¿Qué haces?

<details>
<summary><b>Solucionario — Ronda 6: qué se evalúa</b></summary>

- **Responsabilidad:** dice "yo" en los errores y "el equipo" en los éxitos. Respuestas sin un error real son una señal roja.
- **Decisiones con datos:** en la pregunta 2, un prototipo medido (tamaño de binario con `-fno-exceptions -fno-rtti`, comparación de ensamblador, como en el [módulo 13](../../modules/13-embedded)), una adopción incremental (por ejemplo, empezar por `constexpr`, `enum class`, `span` y RAII) y criterios de reversión acordados antes de empezar. Imponer o ceder sin datos son los dos extremos negativos.
- **Mejora de procesos:** en la pregunta 3, un postmortem sin culpables y un cambio sistémico (test, fuzzer, check de CI), no "tendremos más cuidado".
- **Mentoría:** en la pregunta 4, un plan concreto (revisiones de código, pairing, lecturas, un objetivo medible) y no "le pasé un libro".
- **Firmeza en seguridad:** en la pregunta 5, no saltarse la revisión, pero ofrecer alternativas (reducir alcance, revisión prioritaria, *feature flag* desactivado) y escalar con datos de riesgo.
</details>

---

## Rúbrica y decisión

Cada ronda se puntúa de 1 a 4:

| Puntuación | Significado |
|---|---|
| 4 | Strong hire: resuelve sin ayuda, anticipa seguimientos y aporta matices que el entrevistador no esperaba |
| 3 | Hire: resuelve con pistas menores, razonamiento sólido |
| 2 | Lean no hire: lagunas importantes o necesita mucha guía |
| 1 | No hire: errores fundamentales o señales rojas |

**Decisión:**

- **Contratación:** media ≥ 3,0, ninguna ronda por debajo de 2 y al menos un 4.
- **Veto automático**, con independencia de la media:
  - no detectar B12 (lectura fuera de límites con datos hostiles) en la ronda 2;
  - afirmar que `volatile` sincroniza hilos;
  - en la ronda 4, proponer un mutex compartido con un proceso no confiable o validar datos en memoria compartida sin copiarlos.
- **Nivel:** con media ≥ 3,5 y un 4 en las rondas 2 y 4 se considera el nivel *Staff*.

## Plantilla de autoevaluación

| Ronda | Puntuación (1-4) | Qué fallé | Módulo a repasar |
|---|---|---|---|
| 0 — Screening | | | |
| 1 — Coding | | | |
| 2 — Code review | | | |
| 3 — Concurrencia | | | |
| 4 — Diseño | | | |
| 5 — Rendimiento/embedded | | | |
| 6 — Comportamiento | | | |
