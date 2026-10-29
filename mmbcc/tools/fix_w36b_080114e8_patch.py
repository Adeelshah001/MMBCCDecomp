import sys
s = open(sys.argv[1]).read()
def rep(old, new):
    global s
    assert s.count(old) == 1, f"expected 1 occurrence of {old!r}, got {s.count(old)}"
    s = s.replace(old, new)
# Loop head: idx in r1, shifted into r0 (same length).
rep("\tldrb\tr0, [r4, #4]\n\tlsl\tr0, r0, #2",
    "\tldrb\tr1, [r4, #4]\n\tlsl\tr0, r1, #2")
# Second part: reload struct from the shared pool word, add 34 (net +4 B code).
rep("\tldr\tr1, .L10+8\n\tldrb\tr0, [r1]",
    "\tldr\tr0, .L10+4\n\tadd\tr1, r0, #0\n\tadd\tr1, #34\n\tldrb\tr0, [r1]")
# Pool: drop the folded struct+34 word (net -4 B pool, compensating the +4 B code).
rep("\t.word\t33575506\n", "")
# The strb in the second part uses r1 (now struct+34) — already correct (strb r0,[r1]).
open(sys.argv[1], "w").write(s)
print("patch ok")
