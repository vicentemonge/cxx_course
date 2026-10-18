# 14 — C++26

Técnicamente completo, con soporte en compiladores llegando por partes. Fuera del build por defecto: probar en Compiler Explorer con ramas experimentales de GCC/Clang.

## Temario

Entre corchetes, el estándar en que aparece o cambia cada elemento.

1. Reflexión estática: `^^`, `std::meta::info`, splicers `[: :]`, consultas, `enum` ↔ string, serialización
2. Contracts: `pre`, `post`, `contract_assert`, semánticas de evaluación, handler de violación
3. `std::execution`: senders/receivers/schedulers, `then`, `let_value`, `when_all`, relación con coroutines
4. Biblioteca: `inplace_vector`, `function_ref`, `copyable_function`, `optional<T&>`, aritmética saturada, hazard pointers/RCU, `std::simd`, `std::linalg`, hardening
5. Lenguaje: pack indexing, `#embed`, placeholder `_`, `= delete("motivo")`, comportamiento erróneo para no inicializadas, `constexpr` ampliado

## Ejercicio

Usar reflexión para generar automáticamente la conversión `enum` ↔ string de los códigos de error del módulo 05.

Pasos:

- [ ] Estudiar el temario y probar cada punto en `examples/`
- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) con la versión C++03
- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`
- [ ] Anotar conclusiones en [`docs/notas/14-cpp26.md`](../../docs/notas/14-cpp26.md)
