#!/usr/bin/env python3
"""Genera los README de módulos, docs/TAGS.md y la tabla de módulos del README raíz
a partir de tools/course_data.py. Ejecutar tras editar el temario:

    python3 tools/gen_docs.py
"""
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import course_data as C  # noqa: E402

TAG_RE = re.compile(r"`@([a-z][a-z0-9:-]*)`")
EMB_ICON = {"emb:ok": "🟢", "emb:cond": "🟡", "emb:no": "🔴"}


def num(m):
    return m["d"][:2]


def tags_of(text):
    return TAG_RE.findall(text)


def topic_lines(m):
    """(número jerárquico, texto sin tags, tags) por línea de temario."""
    out, stack = [], []
    for line in m["topics"].splitlines():
        mt = re.match(r"^( *)(\d+)\. (.*)$", line)
        if not mt:
            continue
        depth = len(mt.group(1)) // 4
        stack = stack[:depth] + [mt.group(2)]
        text = mt.group(3)
        clean = TAG_RE.sub("", text).replace(" · ", " ").strip()
        out.append((".".join(stack), clean, tags_of(text)))
    return out


def decorate(topics):
    # Añade el icono delante de cada tag embedded para lectura rápida
    return TAG_RE.sub(lambda mt: (EMB_ICON.get(mt.group(1), "") + " " if mt.group(1) in EMB_ICON else "")
                      + f"`@{mt.group(1)}`", topics)


def examples(m):
    res = {}
    for cat in ("lang", "embedded"):
        d = os.path.join(ROOT, "modules", m["d"], "examples", cat)
        if os.path.isdir(d):
            res[cat] = sorted(f for f in os.listdir(d) if f.endswith(".cpp"))
    return res


def main():
    by_num = {num(m): m for m in C.MODULES}
    core_count = {num(m): defaultdict(int) for m in C.MODULES}
    tag_index = defaultdict(list)  # tag -> [(mod, ref, text)]
    for m in C.MODULES:
        for ref, text, tags in topic_lines(m):
            for t in tags:
                tag_index[t].append((num(m), ref, text))
                if t in C.CORE_TAGS:
                    core_count[num(m)][t] += 1

    unknown = set(tag_index) - set(C.CORE_TAGS) - set(C.EMB_TAGS)
    if unknown:
        sys.exit(f"Tags no declarados en course_data.py: {sorted(unknown)}")

    # ---------------------------------------------------------------- README por módulo
    for m in C.MODULES:
        n = num(m)
        mine = core_count[n]
        main_tags = sorted((t for t in mine if mine[t]), key=lambda t: -mine[t])
        # Conexiones: módulos que comparten tags core, ponderado por apariciones
        links = []
        for o in C.MODULES:
            if o is m:
                continue
            other = core_count[num(o)]
            shared = {t: min(c, other.get(t, 0)) for t, c in mine.items() if c and other.get(t, 0)}
            if shared:
                links.append((sum(shared.values()), num(o), sorted(shared, key=lambda t: -shared[t])))
        links.sort(reverse=True)
        emb = defaultdict(int)
        for _, _, tags in topic_lines(m):
            for t in tags:
                if t in C.EMB_TAGS:
                    emb[t] += 1

        lines = [f"# {n} — {m['title']}", "", m["intro"], ""]
        lines += ["**Temas core:** " + " ".join(f"`@{t}`" for t in main_tags), ""]
        if emb:
            lines += ["**Firmware:** " + " · ".join(f"{EMB_ICON[t]} `@{t}` ×{emb[t]}"
                                                     for t in ("emb:ok", "emb:cond", "emb:no") if emb[t]), ""]
        lines += ["## Temario", "",
                  "Entre corchetes, el estándar en que aparece o cambia cada elemento. "
                  "Leyenda de tags en [`docs/TAGS.md`](../../docs/TAGS.md).", "",
                  decorate(m["topics"]), "",
                  "## Ejercicio", "", m["exercise"], "",
                  "## Preguntas de control (nivel entrevista)", ""]
        lines += [f"{i}. {q}" for i, q in enumerate(m["questions"], 1)]
        ex = examples(m)
        if ex:
            lines += ["", "## Ejemplos", ""]
            names = {"lang": "Lenguaje (`examples/lang/`)", "embedded": "Firmware (`examples/embedded/`)"}
            for cat, files in ex.items():
                lines.append(f"- **{names[cat]}:** " + ", ".join(f"[`{f}`](examples/{cat}/{f})" for f in files))
            lines += ["", "Cada ejemplo es un ejecutable que se registra en `ctest` y debe terminar con código 0."]
        if not m["build"]:
            lines += ["", "> Este módulo no está en el build por defecto: añadirlo a `COURSE_MODULES` "
                          "en el `CMakeLists.txt` raíz cuando el compilador lo soporte."]
        lines += ["", "## Conexiones con otros módulos", ""]
        for w, o, shared in links[:6]:
            om = by_num[o]
            lines.append(f"- [{o} — {om['title']}](../{om['d']}) · " + " ".join(f"`@{t}`" for t in shared[:4]))
        lines += ["", "## Checklist", "",
                  "- [ ] Estudiar el temario y probar cada punto en `examples/lang/`",
                  "- [ ] Comparar en Compiler Explorer (`arm-none-eabi-gcc -Os`) los puntos marcados `@emb:*`",
                  "- [ ] Resolver el ejercicio en `exercise/` con tests en `tests/`",
                  "- [ ] Responder por escrito las preguntas de control",
                  f"- [ ] Anotar conclusiones en [`docs/notas/{m['d']}.md`](../../docs/notas/{m['d']}.md)", ""]
        d = os.path.join(ROOT, "modules", m["d"])
        os.makedirs(os.path.join(d, "exercise"), exist_ok=True)
        open(os.path.join(d, "exercise", ".gitkeep"), "a").close()
        with open(os.path.join(d, "README.md"), "w") as f:
            f.write("\n".join(lines))
        note = os.path.join(ROOT, "docs", "notas", m["d"] + ".md")
        if not os.path.exists(note):
            with open(note, "w") as f:
                f.write(f"# Notas — {n} {m['title']}\n\n")

    # ---------------------------------------------------------------- docs/TAGS.md
    order = {n: i for i, n in enumerate(C.ORDER)}
    t = ["# Tags del curso", "",
         "Generado por `tools/gen_docs.py` desde `tools/course_data.py`. No editar a mano.", "",
         "Los tags aparecen al final de cada punto del temario. Los **core** marcan los hilos "
         "conductores que conectan módulos; los **firmware** indican si una característica aporta, "
         "es condicional o se descarta en bare-metal.", "",
         "## Tags core", "", "| Tag | Significado | Módulos (apariciones) |", "|---|---|---|"]
    for tag, desc in C.CORE_TAGS.items():
        cnt = defaultdict(int)
        for mod, _, _ in tag_index[tag]:
            cnt[mod] += 1
        mods = " ".join(f"[{mo}](#{tag})×{c}" for mo, c in sorted(cnt.items(), key=lambda kv: order[kv[0]]))
        t.append(f"| [`@{tag}`](#{tag}) | {desc} | {mods} |")
    t += ["", "## Tags de firmware", "", "| Tag | Significado | Puntos |", "|---|---|---|"]
    for tag, desc in C.EMB_TAGS.items():
        anchor = tag.replace(":", "")
        t.append(f"| {EMB_ICON[tag]} [`@{tag}`](#{anchor}) | {desc} | {len(tag_index[tag])} |")
    t += ["", "## Matriz módulo × tag core", "",
          "| Módulo | " + " | ".join(f"`{k}`" for k in C.CORE_TAGS) + " |",
          "|---|" + "---|" * len(C.CORE_TAGS)]
    for n in C.ORDER:
        row = [str(core_count[n].get(k) or "") for k in C.CORE_TAGS]
        t.append(f"| [{n}](../modules/{by_num[n]['d']}) | " + " | ".join(row) + " |")
    t += ["", "## Índice por tag", ""]
    for tag in list(C.CORE_TAGS) + list(C.EMB_TAGS):
        anchor = tag.replace(":", "")
        title = (EMB_ICON.get(tag, "") + " " if tag in EMB_ICON else "") + f"`@{tag}`"
        t += [f'<a id="{anchor}"></a>', f"### {title}", ""]
        for mod, ref, text in sorted(tag_index[tag], key=lambda x: (order[x[0]], x[1])):
            t.append(f"- [{mod}](../modules/{by_num[mod]['d']}) §{ref} — {text}")
        t.append("")
    with open(os.path.join(ROOT, "docs", "TAGS.md"), "w") as f:
        f.write("\n".join(t))

    # ---------------------------------------------------------------- tabla del README raíz
    rows = ["| # | Módulo | Temas core principales | 🟢 | 🟡 | 🔴 |", "|---|---|---|---|---|---|"]
    for n in sorted(by_num):
        m = by_num[n]
        top = sorted((k for k in core_count[n] if core_count[n][k]), key=lambda k: -core_count[n][k])[:4]
        e = defaultdict(int)
        for _, _, tags in topic_lines(m):
            for tg in tags:
                e[tg] += 1
        new = " 🆕" if int(n) >= 15 else ""
        rows.append(f"| {n} | [{m['title']}](modules/{m['d']}){new} | "
                    + " ".join(f"`@{x}`" for x in top)
                    + f" | {e['emb:ok'] or ''} | {e['emb:cond'] or ''} | {e['emb:no'] or ''} |")
    readme = os.path.join(ROOT, "README.md")
    s = open(readme).read()
    s = re.sub(r"<!-- modules:start -->.*<!-- modules:end -->",
               "<!-- modules:start -->\n" + "\n".join(rows) + "\n\nOrden recomendado: "
               + " → ".join(C.ORDER) + "\n<!-- modules:end -->", s, flags=re.S)
    open(readme, "w").write(s)
    print(f"{len(C.MODULES)} módulos, {sum(len(v) for v in tag_index.values())} tags asignados")


if __name__ == "__main__":
    main()
