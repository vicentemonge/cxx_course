# 14 — C++26

Técnicamente completo, con soporte llegando por partes. Reflexión y contracts cambiarán cómo se escriben serialización, bindings y validación. Fuera del build por defecto.

**Temas core:** `@safety` `@compile-time` `@generic` `@concurrency` `@interop` `@errors` `@async` `@type-design` `@memory-model` `@performance`

**Firmware:** 🟢 `@emb:ok` ×3 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas · `@compile-time` `@generic` 🟢 `@emb:ok` _todo en compilación_
    1. Casos de uso: `enum` ↔ string, serialización, mapas de registros, bindings · `@compile-time` `@interop`
2. Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler · `@errors` `@safety` 🟢 `@emb:ok`
3. `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all` · `@async` `@concurrency` 🟡 `@emb:cond`
4. Biblioteca
    1. `inplace_vector`, `function_ref`, `optional<T&>`, aritmética saturada · `@type-design` 🟢 `@emb:ok`
    2. Hazard pointers, RCU · `@memory-model` `@concurrency`
    3. `std::simd`, `std::linalg` · `@performance`
    4. Hardening de la biblioteca estándar · `@safety`
5. Lenguaje: pack indexing, `#embed`, placeholder `_`, `= delete("motivo")`, comportamiento erróneo para no inicializadas · `@safety` `@generic`

## Ejercicio

Usar reflexión para generar automáticamente la conversión `enum` ↔ string de los códigos de error del módulo 05.

## Preguntas de control (nivel entrevista)

1. ¿Qué problemas de serialización resuelve la reflexión estática?
2. ¿Qué semánticas de evaluación tienen los contracts y cuál usarías en producción?
3. ¿Qué es el comportamiento erróneo y cómo cambia el riesgo de las variables sin inicializar?
4. ¿Qué aporta `std::execution` frente a `std::async`?

> Este módulo no está en el build por defecto: añadirlo a `COURSE_MODULES` en el `CMakeLists.txt` raíz cuando el compilador lo soporte.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@safety` `@compile-time` `@errors` `@type-design`
- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@generic` `@compile-time` `@interop` `@errors`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@generic` `@safety` `@interop` `@type-design`
- [09 — Concurrencia y modelo de memoria](../09-concurrencia) · `@safety` `@concurrency` `@async` `@memory-model`
- [02 — Programación en tiempo de compilación](../02-compile-time) · `@compile-time` `@generic` `@safety` `@performance`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@safety` `@interop` `@type-design` `@performance`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/14-cpp26.md`](../../docs/notas/14-cpp26.md)
