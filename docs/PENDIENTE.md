# Pendiente: contenido que se puede incluir

Huecos detectados en el curso que aún no tienen temario ni ejemplos. Al incluir uno, añadirlo a
`tools/course_data.py`, regenerar con `python3 tools/gen_docs.py` y borrar la entrada de aquí.

## 07 — Ranges, views y algoritmos

Hoy los views se cubren a nivel de temario y ejemplos básicos. Faltan las trampas, que son
justo lo que se pregunta en entrevistas. Candidato: `examples/lang/views_trampas.cpp`.

- [ ] `filter_view` cachea `begin()`: por eso no es iterable a través de `const&`, y modificar elementos de forma que dejen de cumplir el predicado es UB. Pasar views por valor o `auto&&`. Hoy solo aparece como pregunta de control.
- [ ] Las funciones de los adaptadores pueden ejecutarse más de una vez: en `transform | filter`, el transform corre en la comprobación del filtro y otra vez al desreferenciar. Lambdas baratas y sin efectos secundarios.
- [ ] `owning_view` (P2415): pasar un contenedor rvalue por un pipe es seguro; un view sobre un lvalue destruido queda colgando.
- [ ] Qué adaptadores pierden propiedades: `filter` pierde acceso aleatorio y `size()`; `take` sobre `iota` infinito devuelve un range finito.
- [ ] `split` (corregido por P2210) frente a `lazy_split` para input ranges.
