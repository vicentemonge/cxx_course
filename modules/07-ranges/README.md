# 07 — Ranges, views y algoritmos

Saber elegir algoritmo y escribir iteradores correctos sigue siendo una prueba estándar. Ranges [20] cambia el estilo, pero el modelo de iteradores es la base.

**Temas core:** `@iteration` `@generic` `@lifetime` `@safety` `@concurrency` `@functional` `@performance` `@tooling`

**Firmware:** 🟢 `@emb:ok` ×4 · 🟡 `@emb:cond` ×1 · 🔴 `@emb:no` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Modelo de iteradores
    1. Categorías, `iterator_traits`, iteradores contiguos [20] · `@iteration` `@generic`
    2. Escribir un iterador y un centinela propios · `@iteration` `@generic` 🟢 `@emb:ok`
    3. Invalidación de iteradores por contenedor · `@iteration` `@lifetime` `@safety`
2. Algoritmos: `all_of`, `iota` [11], `clamp`, `reduce` [17], `midpoint`, `shift_left` [20] · `@iteration` 🟢 `@emb:ok`
    1. Políticas de ejecución paralela [17] · `@iteration` `@concurrency` 🔴 `@emb:no` _requiere TBB o hilos_
3. Ranges [20]: centinelas, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges* · `@iteration` `@generic` 🟢 `@emb:ok`
4. Views [20]: `filter`, `transform`, `take`, `split`, `join`, `iota`; pereza; views propias · `@iteration` `@functional` 🟢 `@emb:ok` _sin heap; revisar tamaño con `-Os`_
5. C++23: `ranges::to`, `zip`, `enumerate`, `chunk`, `slide`, `fold_left`, `contains` · `@iteration` 🟡 `@emb:cond` _`ranges::to` asigna memoria_
6. Coste: tiempo de compilación, depuración y ensamblador frente a bucles manuales · `@performance` `@tooling`

## Ejercicio

Reescribir el procesado de un buffer de muestras ADC (filtrado, escalado, detección de umbral) con views y comparar el ensamblador con el bucle manual.

## Preguntas de control (nivel entrevista)

1. ¿Qué es un centinela y qué ventaja aporta frente a un par de iteradores?
2. ¿Por qué `filter_view` no es `const`-iterable y qué implica?
3. ¿Qué invalida los iteradores de `std::vector`? ¿Y de `std::unordered_map`?
4. ¿Qué es un *borrowed range* y para qué existe `std::ranges::dangling`?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`algoritmos.cpp`](examples/lang/algoritmos.cpp), [`ranges_basico.cpp`](examples/lang/ranges_basico.cpp), [`views_cpp23.cpp`](examples/lang/views_cpp23.cpp), [`views_perezosas.cpp`](examples/lang/views_perezosas.cpp)
- **Firmware (`examples/embedded/`):** [`adc_pipeline.cpp`](examples/embedded/adc_pipeline.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [02 — Programación en tiempo de compilación](../02-compile-time) · `@generic` `@lifetime` `@safety` `@performance`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@generic` `@safety` `@functional` `@performance`
- [06 — Lambdas y estilo funcional](../06-lambdas) · `@generic` `@lifetime` `@safety` `@functional`
- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@generic` `@lifetime` `@safety` `@performance`
- [17 — Rendimiento y diseño orientado a datos](../17-rendimiento) · `@iteration` `@lifetime` `@concurrency` `@performance`
- [14 — C++26](../14-cpp26) · `@generic` `@safety` `@concurrency` `@performance`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/07-ranges.md`](../../docs/notas/07-ranges.md)
