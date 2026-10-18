# 18 — Calidad: testing, sanitizers, fuzzing, análisis estático y build

Módulo nuevo y transversal: empezar en paralelo al 01. En empresas grandes la calidad está automatizada; se espera dominar CMake moderno, tests, sanitizers y fuzzing.

**Temas core:** `@tooling` `@safety` `@abi` `@generic` `@compile-time`

**Firmware:** 🟢 `@emb:ok` ×6

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. CMake moderno: targets, propiedades `PUBLIC`/`PRIVATE`/`INTERFACE`, presets, toolchains, FetchContent · `@tooling` `@abi` 🟢 `@emb:ok`
2. Gestión de dependencias: vcpkg, Conan, CPM · `@tooling`
3. Testing
    1. Frameworks: doctest, Catch2, GoogleTest; tests parametrizados · `@tooling`
    2. Diseño testable: dependencias inyectadas, HAL simulada en host · `@tooling` `@generic` 🟢 `@emb:ok`
    3. `static_assert` como test en compilación · `@tooling` `@compile-time` 🟢 `@emb:ok`
    4. Tests en hardware (HIL) y en emulador (QEMU, Renode) · `@tooling` 🟢 `@emb:ok`
4. Sanitizers: ASan, UBSan, TSan, MSan; integración en CI · `@tooling` `@safety`
5. Fuzzing: libFuzzer, AFL++, OSS-Fuzz; fuzzing de parsers de protocolo · `@tooling` `@safety` 🟢 `@emb:ok` _en host sobre el mismo código_
6. Análisis estático: clang-tidy, cppcheck, `-Wall -Wextra`, análisis de flujo, MISRA · `@tooling` `@safety` 🟢 `@emb:ok`
7. Cobertura: gcov/llvm-cov, criterios útiles · `@tooling`
8. Revisión de código y estilo: clang-format, Core Guidelines, guías de Google/Mozilla · `@tooling`

## Ejercicio

Añadir a este repo un fuzzer libFuzzer para el parser de tramas del módulo 04, un preset con UBSan+ASan y un objetivo de cobertura; corregir lo que encuentren.

## Preguntas de control (nivel entrevista)

1. ¿Qué diferencia hay entre `target_link_libraries(... PUBLIC ...)` y `PRIVATE`?
2. ¿Cómo testearías en host un driver que escribe en registros de hardware?
3. ¿Qué tipo de bugs encuentra el fuzzing que los tests unitarios no?
4. ¿Por qué no puedes combinar ASan y TSan en el mismo binario?

## Ejemplos

- **Lenguaje (`examples/lang/`):** [`inyeccion_dependencias.cpp`](examples/lang/inyeccion_dependencias.cpp), [`tests_en_compilacion.cpp`](examples/lang/tests_en_compilacion.cpp)
- **Firmware (`examples/embedded/`):** [`hal_mock.cpp`](examples/embedded/hal_mock.cpp)

Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0.

## Conexiones con otros módulos

- [13 — C++ moderno en embedded](../13-embedded) · `@safety` `@tooling` `@abi` `@compile-time`
- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@tooling` `@safety` `@abi` `@generic`
- [02 — Programación en tiempo de compilación](../02-compile-time) · `@safety` `@tooling` `@abi` `@generic`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@safety` `@tooling`
- [14 — C++26](../14-cpp26) · `@safety` `@generic` `@compile-time`
- [12 — Módulos, enlace y organización del código](../12-modulos) · `@tooling` `@abi` `@safety`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/18-calidad.md`](../../docs/notas/18-calidad.md)
