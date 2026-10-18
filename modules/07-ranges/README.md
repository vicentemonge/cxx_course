# 07 — Ranges, views y algoritmos

Composición de transformaciones perezosas sobre secuencias [20].

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Algoritmos ampliados: `all_of`, `iota` [11], `clamp` [17], paralelos [17], `midpoint` [20]
2. Fundamentos de ranges [20]: iterador + centinela, `std::ranges::*`, proyecciones, concepts de range, *borrowed ranges*
3. Views [20]: composición con `|`, `filter`, `transform`, `take`, `drop`, `split`, `join`, `iota`; evaluación perezosa; views propias
4. C++23: `ranges::to`, `zip`, `enumerate`, `chunk`, `slide`, `stride`, `adjacent`, `fold_left`, `contains`
5. Límites en embedded: tiempo de compilación, tamaño con `-Os`, views sin heap

## Ejercicio

Reescribir el procesado de un buffer de muestras ADC (filtrado, escalado, detección de umbral) con views y comparar el ensamblador con el bucle manual.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/07-ranges.md`](../../docs/notas/07-ranges.md)

## Ejemplo inicial

`examples/adc_pipeline.hpp`, `examples/adc_pipeline.cpp`: punto de partida ejecutable y testeado. Ampliar o sustituir libremente.
