# 02 — Programación en tiempo de compilación

El área que más ha crecido desde C++11. En firmware convierte tablas, CRC y validaciones de configuración en coste cero; en sistemas grandes reduce errores de runtime a errores de compilación.

**Temas core:** `@compile-time` `@generic` `@safety` `@lifetime` `@abi` `@tooling` `@performance`

**Firmware:** 🟢 `@emb:ok` ×8

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. `constexpr` y su evolución
    1. Una expresión [11] → bucles y variables [14] → lambdas [17] · `@compile-time` 🟢 `@emb:ok`
    2. `try`, `virtual`, `union`, asignación transitoria, `vector`/`string` constexpr [20] · `@compile-time` 🟢 `@emb:ok` _la memoria transitoria no llega al binario_
    3. `static` en funciones constexpr, tipos no literales [23], `<cmath>` constexpr [23/26] · `@compile-time`
    4. Límites: pasos de evaluación, diagnóstico de UB en constexpr como herramienta · `@compile-time` `@safety`
2. `if constexpr` [17] y ramas descartadas · `@compile-time` `@generic` 🟢 `@emb:ok`
3. Garantías de compilación
    1. `consteval` [20], propagación [23] · `@compile-time` 🟢 `@emb:ok`
    2. `if consteval` [23] vs `std::is_constant_evaluated()` [20] · `@compile-time`
    3. `constinit` [20] y el *static initialization order fiasco* · `@lifetime` 🟢 `@emb:ok` _inicialización en `.data`, sin constructores en arranque_
4. Variables y templates en compilación
    1. Variable templates [14], variables `inline` [17] · `@compile-time` `@abi` 🟢 `@emb:ok`
    2. NTTP `auto` [17], NTTP de clase y flotantes [20] · `@generic` `@compile-time` 🟢 `@emb:ok`
5. Utilidades
    1. `std::bit_cast` [20] · `@safety` 🟢 `@emb:ok`
    2. `std::index_sequence` [14] y expansión de tablas · `@generic` `@compile-time`
6. Coste de compilación: instanciaciones, `-ftime-trace`, cuándo calcular en build (script) en vez de en C++ · `@tooling` `@performance`

## Ejercicio

Generar en compilación una tabla CRC-32 o una LUT de calibración con `consteval`, colocarla en flash con `constinit`/`const` y verificar en el `.map` que no ocupa RAM.

## Preguntas de control (nivel entrevista)

1. ¿Qué diferencia hay entre `constexpr`, `consteval` y `constinit`? Pon un caso para cada uno.
2. ¿Por qué el UB dentro de una evaluación constante es un error de compilación y cómo puedes aprovecharlo en tests?
3. ¿Qué problema resuelve `constinit` que `constexpr` no resuelve para una variable global mutable?
4. ¿Cuándo preferirías generar una tabla con un script en el build en vez de con `constexpr`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`consteval_constinit.cpp`](examples/lang/consteval_constinit.cpp), [`constexpr_evolucion.cpp`](examples/lang/constexpr_evolucion.cpp), [`if_constexpr.cpp`](examples/lang/if_constexpr.cpp), [`nttp.cpp`](examples/lang/nttp.cpp)
- **Firmware (`examples/embedded/`):** [`crc32.cpp`](examples/embedded/crc32.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@safety` `@generic` `@abi` `@tooling`
- [14 — C++26](../14-cpp26) · `@compile-time` `@safety` `@generic` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@safety` `@compile-time` `@lifetime` `@abi`
- [07 — Ranges, views y algoritmos](../07-ranges) · `@generic` `@safety` `@lifetime` `@tooling`
- [03 — Templates modernos y concepts](../03-templates-concepts) · `@generic` `@compile-time` `@abi` `@performance`
- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@generic` `@compile-time` `@safety` `@lifetime`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/02-compile-time.md`](../../docs/notas/02-compile-time.md)
