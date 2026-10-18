# 12 — Módulos, enlace y organización del código

Entender el modelo de compilación (unidades de traducción, ODR, enlace) es imprescindible en bases de código de millones de líneas. Los módulos [20] lo cambian, con soporte aún irregular. Fuera del build por defecto hasta que el toolchain lo permita.

**Temas core:** `@abi` `@tooling` `@safety`

**Firmware:** 🟢 `@emb:ok` ×1 · 🟡 `@emb:cond` ×1

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento. Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).

1. Modelo clásico
    1. Unidades de traducción, enlace interno/externo, `static` y namespaces anónimos · `@abi`
    2. ODR, `inline` (funciones y variables [17]), violaciones silenciosas · `@abi` `@safety`
    3. Coste de los headers: tiempos de build, *include-what-you-use*, *precompiled headers* · `@abi` `@tooling`
2. Módulos [20]
    1. `export module`, `import`, particiones, *global module fragment*, *header units* · `@abi`
    2. `import std;` [23] · `@abi` 🟡 `@emb:cond` _soporte de toolchain cruzado_
    3. *Module linkage*, macros que no cruzan fronteras · `@abi`
3. Herramientas: CMake `FILE_SET CXX_MODULES` + Ninja, soporte en GCC/Clang/MSVC · `@tooling` `@abi`
4. Sin módulos: namespaces `inline` [11] para versionado, anidados [17], `__has_include` [17], macros `__cpp_*` [20] · `@abi` 🟢 `@emb:ok`

## Ejercicio

Convertir una librería pequeña de utilidades en un módulo y compilarla con CMake + Ninja para host; documentar qué falla con el toolchain del target.

## Preguntas de control (nivel entrevista)

1. ¿Qué es una violación de ODR y por qué el enlazador no siempre la detecta?
2. ¿Qué aporta un namespace `inline` al versionado de una biblioteca?
3. ¿Qué problemas de los headers resuelven los módulos y cuáles no?
4. ¿Cómo reducirías a la mitad el tiempo de compilación de un proyecto grande?

> Este módulo no está en el build por defecto: añadirlo a `COURSE_MODULES` en el `CMakeLists.txt` raíz cuando el compilador lo soporte.

## Conexiones con otros módulos

- [16 — Diseño de tipos y APIs: polimorfismo, type erasure, ABI e interoperabilidad](../16-diseno-apis) · `@abi` `@tooling` `@safety`
- [18 — Calidad: testing, sanitizers, fuzzing, análisis estático y build](../18-calidad) · `@tooling` `@abi` `@safety`
- [13 — C++ moderno en embedded](../13-embedded) · `@tooling` `@abi` `@safety`
- [15 — Modelo de objetos, comportamiento indefinido y seguridad de memoria](../15-ub-seguridad) · `@tooling` `@safety`
- [02 — Programación en tiempo de compilación](../02-compile-time) · `@abi` `@safety` `@tooling`
- [17 — Rendimiento y diseño orientado a datos](../17-rendimiento) · `@tooling`

## Checklist

- [ ] Estudiar el temario y probar cada punto en `examples/lang/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Responder por escrito las preguntas de control
- [ ] Anotar conclusiones en [`docs/notas/12-modulos.md`](../../docs/notas/12-modulos.md)
