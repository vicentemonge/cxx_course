# 06 — Lambdas y estilo funcional

Callbacks, visitantes, algoritmos y coroutines dependen de las lambdas. Entender el tipo de cierre y el coste del borrado de tipo distingue a un senior.

**Temas core:** `@functional` `@lifetime` `@generic` `@interop` `@value-sem` `@compile-time` `@safety` `@performance`

**Firmware:** 🟢 `@emb:ok` ×3 · 🟡 `@emb:cond` ×2

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Fundamentos [11]: tipo de cierre, capturas, `mutable`, conversión a puntero a función · `@functional` `@interop` 🟢 `@emb:ok`
2. Evolución
    1. *Init-capture* y lambdas genéricas [14] · `@functional` `@value-sem`
    2. `constexpr` lambdas, captura de `*this` [17] · `@functional` `@compile-time` `@lifetime`
    3. Parámetros template, lambdas sin estado construibles, en contexto no evaluado [20] · `@functional` `@generic`
    4. Lambdas `static` y recursivas con *deducing this* [23] · `@functional`
3. Riesgos de tiempo de vida: capturas por referencia que sobreviven al ámbito · `@lifetime` `@safety`
4. Wrappers de invocables
    1. `std::function` [11]: borrado de tipo y SBO · `@functional` `@performance` 🟡 `@emb:cond` _heap si el cierre no cabe en el SBO_
    2. `move_only_function` [23], `copyable_function` [26] · `@functional` 🟡 `@emb:cond`
    3. `function_ref` [26] · `@functional` 🟢 `@emb:ok`
    4. `invoke` [17], `invoke_r` [23], `bind_front` [20], `bind_back` [23] · `@functional` `@generic`
5. Patrones: IIFE, *overloaded*, callbacks de ISR con templates o `function_ref` · `@functional` 🟢 `@emb:ok`

## Ejercicio

Implementar un dispatcher de eventos sin heap que acepte lambdas con captura, comparando tamaño de código entre `std::function`, templates y `function_ref`.

## Preguntas de control (nivel entrevista)

1. ¿Qué genera el compilador para una lambda con capturas? ¿Cuál es su tamaño?
2. ¿Cuándo asigna memoria `std::function`? ¿Cómo lo evitas?
3. ¿Qué problema tiene capturar `this` en una lambda que se ejecuta en otro hilo?
4. Implementa una versión simplificada de `function_ref`.

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`capturas.cpp`](examples/lang/capturas.cpp), [`lambda_recursiva.cpp`](examples/lang/lambda_recursiva.cpp), [`lambdas_genericas.cpp`](examples/lang/lambdas_genericas.cpp), [`wrappers_invocables.cpp`](examples/lang/wrappers_invocables.cpp)
- **Firmware (`examples/embedded/`):** [`event_dispatcher.cpp`](examples/embedded/event_dispatcher.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@lifetime` `@generic` `@interop` `@value-sem`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@generic` `@functional` `@interop` `@value-sem`
- [14 — C++26](../14-cpp26) · `@generic` `@interop` `@compile-time` `@safety`
- [07 — Ranges, views y algoritmos](../07-ranges) · `@generic` `@functional` `@lifetime` `@safety`
- [05 — Gestión de errores](../05-gestion-errores) · `@lifetime` `@functional` `@interop` `@safety`
- [02 — Programación en tiempo de compilación](../02-compile-time) · `@generic` `@compile-time` `@lifetime` `@safety`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/06-lambdas.md`](../../docs/notas/06-lambdas.md)
