# 05 — Gestión de errores

Una empresa grande exige una política de errores coherente. `std::expected` [23] permite errores tipados sin excepciones; las garantías de excepción siguen siendo pregunta obligada.

**Temas core:** `@errors` `@lifetime` `@type-design` `@performance` `@functional` `@interop` `@safety`

**Firmware:** 🟢 `@emb:ok` ×5 · 🟡 `@emb:cond` ×2 · 🔴 `@emb:no` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Panorama: códigos de retorno, `errno`, excepciones, tipos resultado · `@errors` `@performance`
    1. Coste real de las excepciones: tablas de unwind, tamaño de código, determinismo · `@errors` 🔴 `@emb:no` _bare-metal suele compilar con `-fno-exceptions`_
2. Garantías de excepción: nothrow, fuerte, básica; copy-and-swap · `@errors` `@lifetime`
3. RAII para limpieza: *scope guards* (`scope_exit`), `unique_resource` · `@errors` `@lifetime` 🟢 `@emb:ok`
4. `std::expected<T, E>` [23]
    1. `unexpected`, acceso, `value_or` · `@errors` `@type-design` 🟢 `@emb:ok`
    2. `and_then`, `transform`, `or_else`, `transform_error` · `@errors` `@functional` 🟢 `@emb:ok`
    3. `expected<void, E>` y diseño del tipo de error · `@errors` `@type-design`
    4. `value()` lanza `bad_expected_access`: usar `*`/`has_value` sin excepciones · `@errors` 🟡 `@emb:cond`
5. `std::error_code` / `error_category` [11] · `@errors` `@interop` 🟡 `@emb:cond` _categorías con strings, revisar tamaño_
6. Atributos y especificadores
    1. `[[nodiscard]]` [17/20], `noexcept` [11/17], `[[noreturn]]`, `std::unreachable` [23] · `@errors` 🟢 `@emb:ok`
    2. Política de `noexcept`: cuándo marcar, efecto en `std::terminate` · `@errors`
7. Precondiciones: `assert`, `source_location` [20], contracts [26] · `@errors` `@safety` 🟢 `@emb:ok`

## Ejercicio

Convertir la API pública de un driver de códigos `int` a `std::expected<T, DriverError>` y encadenar init → configure → read con `and_then`.

## Preguntas de control (nivel entrevista)

1. Define las garantías básica, fuerte y nothrow. ¿Qué garantía da `vector::push_back`?
2. ¿Qué ocurre si una excepción escapa de una función `noexcept`?
3. Compara `std::expected` con excepciones en un servicio de alto rendimiento y en firmware.
4. ¿Cómo diseñarías los tipos de error de una biblioteca usada por varios equipos?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`error_code.cpp`](examples/lang/error_code.cpp), [`expected_cadena.cpp`](examples/lang/expected_cadena.cpp), [`noexcept_nodiscard.cpp`](examples/lang/noexcept_nodiscard.cpp), [`source_location.cpp`](examples/lang/source_location.cpp)
- **Firmware (`examples/embedded/`):** [`expected_driver.cpp`](examples/embedded/expected_driver.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [04 — Tipos vocabulario](../04-tipos-vocabulario) · `@lifetime` `@type-design` `@errors` `@performance`
- [01 — Fundamentos del C++ moderno](../01-fundamentos) · `@lifetime` `@type-design` `@errors` `@performance`
- [13 — C++ moderno en embedded](../13-embedded) · `@lifetime` `@type-design` `@errors` `@performance`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@type-design` `@performance` `@functional` `@interop`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@lifetime` `@performance` `@type-design` `@interop`
- [06 — Lambdas y estilo funcional](../06-lambdas) · `@lifetime` `@performance` `@functional` `@interop`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/05-gestion-errores.md`](../../docs/notas/05-gestion-errores.md)
