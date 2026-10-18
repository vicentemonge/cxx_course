# 03 — Templates modernos y concepts

Nivel esperado: leer y escribir código genérico de bibliotecas (STL, Abseil, Folly) y diagnosticar errores de instanciación. Concepts [20] sustituyen casi todo el SFINAE.

**Temas core:** `@generic` `@compile-time` `@type-design` `@performance` `@abi` `@iteration`

**Firmware:** 🟢 `@emb:ok` ×2 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Fundamentos que siguen importando
    1. Lookup en dos fases, nombres dependientes, `typename` y `template` como desambiguadores · `@generic`
    2. ADL y puntos de personalización (`swap`, *niebloids*, CPOs) · `@generic` `@abi`
    3. Especialización total y parcial, sobrecarga frente a especialización · `@generic`
2. Variadic templates
    1. Packs, `sizeof...` [11], fold expressions [17] · `@generic` `@compile-time` 🟢 `@emb:ok`
    2. Expansión en lambdas y `using` [17/20], pack indexing [26] · `@generic`
3. CTAD [17], guías de deducción, CTAD para agregados y alias [20] · `@generic` `@type-design`
4. SFINAE como herencia
    1. `enable_if`, `void_t`, *detection idiom* [11/17]: leerlo en código existente · `@generic`
5. Concepts [20]
    1. `requires` (cláusulas y expresiones), requisitos simples, de tipo, compuestos y anidados · `@generic` `@type-design`
    2. Sintaxis abreviada y parámetros `auto` · `@generic`
    3. Subsunción y ordenación de sobrecargas · `@generic`
    4. `<concepts>` estándar y concepts de iteradores/ranges · `@generic` `@iteration`
    5. Concepts como interfaz de drivers: polimorfismo estático sin vtable · `@generic` `@performance` 🟢 `@emb:ok`
6. Type traits: `_t` [14], `_v` [17], `conjunction` [17], `remove_cvref`, `type_identity` [20] · `@generic` `@compile-time`
7. Coste: explosión de instanciaciones y tamaño de código (*code bloat*), técnicas de *thin template* · `@performance` 🟡 `@emb:cond` _vigilar flash con muchas instanciaciones_

## Ejercicio

Definir un concept `RegisterAccess` para drivers (lectura/escritura de 8/16/32 bits) y reescribir con él un driver genérico que hoy use SFINAE o `void*`.

## Preguntas de control (nivel entrevista)

1. Explica el lookup en dos fases. ¿Por qué a veces hace falta `this->` en una clase derivada de una plantilla?
2. ¿Qué es un *customization point object* y qué problema de ADL resuelve?
3. ¿Cómo decide el compilador entre dos sobrecargas restringidas por concepts?
4. ¿Cómo reducirías el tamaño de código de una plantilla instanciada con 20 tipos distintos?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`concepts_basicos.cpp`](examples/lang/concepts_basicos.cpp), [`ctad.cpp`](examples/lang/ctad.cpp), [`sfinae_vs_concepts.cpp`](examples/lang/sfinae_vs_concepts.cpp), [`variadic_fold.cpp`](examples/lang/variadic_fold.cpp)
- **Firmware (`examples/embedded/`):** [`register_concept.cpp`](examples/embedded/register_concept.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@generic` `@type-design` `@performance` `@compile-time`
- [02 — Programación en tiempo de compilación](../02-compile-time) · `@generic` `@compile-time` `@abi` `@performance`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@generic` `@type-design` `@abi` `@performance`
- [14 — C++26](../14-cpp26) · `@generic` `@compile-time` `@type-design` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@type-design` `@performance` `@abi` `@compile-time`
- [11 — Strings, formato, tiempo y E/S](../11-format-chrono-io) · `@type-design` `@performance` `@generic` `@abi`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/03-templates-concepts.md`](../../docs/notas/03-templates-concepts.md)
