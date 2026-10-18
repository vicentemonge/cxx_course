# 12 — Módulos y organización del código

Los módulos [20] sustituyen el modelo de `#include`; su soporte en toolchains cruzados aún es irregular. Este módulo no está en el build por defecto: añadirlo a `COURSE_MODULES` cuando el compilador lo permita.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Conceptos: problemas de los headers, `export module`/`import`, particiones, *global module fragment*, *header units*, `import std;` [23]
2. Visibilidad: `export`, *module linkage*, macros
3. Herramientas: GCC/Clang/MSVC, CMake `FILE_SET CXX_MODULES` + Ninja, viabilidad con `arm-none-eabi-gcc`
4. Sin módulos: namespaces `inline` [11], anidados [17], `__has_include` [17], macros `__cpp_*` [20]

## Ejercicio

Convertir una librería pequeña de utilidades en un módulo y compilarla con CMake + Ninja para host; documentar qué falla con el toolchain del target.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/12-modulos.md`](../../docs/notas/12-modulos.md)
