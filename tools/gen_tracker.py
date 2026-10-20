#!/usr/bin/env python3
"""Genera tracker/index.html (seguimiento de progreso) a partir de tools/course_data.py.

    python3 tools/gen_tracker.py

Los identificadores de cada elemento derivan del número de módulo y de la numeración del
temario: si se renumera un punto, su casilla marcada no se conserva.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import course_data as C  # noqa: E402
from gen_docs import TAG_RE, topic_lines  # noqa: E402

ROUNDS = ["Screening técnico", "Coding: LRU cache", "Code review con código hostil",
          "Concurrencia y modelo de memoria", "Diseño de sistema",
          "Rendimiento y sistemas embebidos", "Comportamiento y liderazgo"]


def typo(text):
    """Comillas tipográficas fuera de los fragmentos de código."""
    parts = re.split(r"(`[^`]*`)", text)
    out = []
    for p in parts:
        if not p.startswith("`"):
            p = re.sub(r'"([^"]+)"', "“\\1”", p).replace("'", "’")
        out.append(p)
    return "".join(out)


def build():
    mods = []
    for m in C.MODULES:
        n = m["d"][:2]
        items = []
        for ref, text, tags in topic_lines(m):
            # nota en cursiva al final: _texto_
            note = None
            mt = re.search(r"\s_([^_]+)_\s*$", text)
            if mt:
                note, text = mt.group(1), text[:mt.start()].rstrip()
            depth = ref.count(".")
            items.append({"id": f"{n}-t{ref}", "ref": ref, "d": depth, "text": typo(text),
                          "note": typo(note) if note else None, "tags": tags})
        mods.append({
            "n": n, "slug": m["d"], "title": typo(m["title"]), "intro": typo(m["intro"]),
            "items": items,
            "exercise": {"id": f"{n}-ex", "text": typo(m["exercise"])},
            "questions": [{"id": f"{n}-q{i}", "text": typo(q)} for i, q in enumerate(m["questions"], 1)],
        })
    return {
        "order": C.ORDER,
        "core": C.CORE_TAGS,
        "emb": C.EMB_TAGS,
        "modules": mods,
        "rounds": [{"id": f"r{i}", "text": t} for i, t in enumerate(ROUNDS)],
        "repo": "https://github.com/vicentemonge/cxx_course",
    }


def main():
    data = json.dumps(build(), ensure_ascii=False, separators=(",", ":"))
    tpl = open(os.path.join(ROOT, "tracker", "template.html"), encoding="utf-8").read()
    out = tpl.replace("/*__COURSE_DATA__*/null", data.replace("</", "<\\/"))
    with open(os.path.join(ROOT, "tracker", "index.html"), "w", encoding="utf-8") as f:
        f.write(out)
    print(f"tracker/index.html: {len(out) // 1024} KB")


if __name__ == "__main__":
    main()
