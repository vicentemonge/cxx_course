# Seguimiento de progreso

Página de seguimiento del curso, publicada como artifact privado de Claude:
<https://claude.ai/artifact/P1LjwBkDY2Vh3dJUeYwszH>

- Una casilla por cada punto del temario, ejercicio y pregunta de control, más la puntuación de las rondas de la entrevista simulada.
- Progreso por módulo (recorrido en el orden recomendado) y por tag: filtrar por `@safety` muestra solo esos puntos en todo el curso.
- El progreso se guarda en la base de datos privada del artifact, por usuario, y se sincroniza entre dispositivos. Abierta fuera de claude.ai, la página guarda en el navegador.

## Regenerar

`index.html` se genera desde `tools/course_data.py`:

```bash
python3 tools/gen_tracker.py
```

Después hay que volver a publicar `tracker/index.html` en el mismo artifact (pidiéndoselo a Claude con el enlace de arriba) para que la versión online recoja los cambios del temario.
Los identificadores de las casillas derivan del número de módulo y de la numeración del temario: renumerar un punto hace que pierda su marca.
