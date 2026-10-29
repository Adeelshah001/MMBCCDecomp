# Wave 4 batch J match notes (worker J, 2026-10-20)

## Part 1 — Thunk-span entries: ALL 25 are INTERIOR (not functions)

### Verdict
The 25 v2.4 "thunk-span" entries (0x0802BCE2–0x0802C71E) are **interior
long-branch targets inside the single giant function sub_080298FC
(0x080298FC–0x0802C7B2)**, not separate functions and not alternate
entries. The v2.4 addendum's promotion ("they are entry points
regardless") is incorrect. 0x08033962 is likewise INTERIOR inside
sub_08030AD4 (0x08030AD4–0x08033AC2).

### Evidence
1. **All BL callers are intra-function.** Full-ROM BL scan: every caller
   site for all 25 targets lies in 0x0802A194–0x0802B546 (plus 0x0802BE9E
   for 0x0802C6E6), all strictly inside sub_080298FC's
   0x080298FC–0x0802C7B2 range. Zero callers from outside. Counts match
   the v2.4 addendum exactly (31/26/15/3/1…), confirming the scan found
   the same sites — but they are not calls.
2. **No target can return.** Recursive descent from all 25 targets
   (1308 insns) reaches exactly ONE terminator: `bx r1` at 0x0802C7B2,
   sub_080298FC's single epilogue (`add sp,#0x58; pop {r3,r4,r5};
   mov r8,r3; mov sb,r4; mov sl,r5; pop {r4,r5,r6,r7}; pop {r1};
   bx r1`), which pops the *original* saved LR. A `bl` to any target
   pushes a return address into LR that is never used — the target
   cannot return to its BL site. Therefore every one of these BLs is a
   **branch**, not a call.
3. **Mechanism: out-of-range `b`.** Thumb `b` reaches only ±2KB. All 25
   targets are >2KB from their BL sites (e.g. 0x0802A194→0x0802C71E =
   0x258A). agbcc emits `bl` as a long branch for what the source
   expresses as `goto`/early-`return` to a shared tail/epilogue label.
   (Same pattern already documented for 0x0802C6E6 in
   docs/match_notes_wave3_a.md §3: "The single `bl` caller (0x0802BE9E)
   is intra-function.")
4. **No data-pointer references** to any of the 25 targets
   (full-ROM word scan).
5. **Host body confirmed:** sub_080298FC prologue `push {r4,r5,r6,r7,lr}`
   at 0x080298FC; single epilogue ending `bx r1` at 0x0802C7B2; next
   function prologue at 0x0802C7B4. No `pop {pc}`/`bx lr` anywhere in
   0x080298FC–0x0802C7B2.

### Host body ranges for the coordinator
- 25 targets → fold into **sub_080298FC, 0x080298FC–0x0802C7B2**.
  Demote from tier B; they are labels, not functions. (Working count
  impact: −25 from the 1703.)
- 0x08033962 → fold into **sub_08030AD4, 0x08030AD4–0x08033AC2**
  (prologue `push {r4,r5,r6,r7,lr}` at 0x08030AD4, epilogue `bx r1` at
  0x08033AC2). Sole BL caller 0x08030B0C is intra-function
  (distance 0x2E56 > 2KB → long branch). Zero data refs.
- Related observation (not in my 31, flagged for coordinator):
  **sub_08033AB2 (v1:A) is also an interior long-branch target**, not a
  function. It is the shared epilogue entry (`ldr r0,[sp,#0x40]` at
  0x08033AB2 → `add sp,#0x50; pop…; bx r1` at 0x08033AC2) with 2 BL
  callers (0x08030AFC, 0x08030B10), both intra-function sub_08030AD4
  (distances 12214/12194 > 2KB). No prologue; the region's only prologue
  is sub_08030AD4's at 0x08030AD4.

### New idiom (for the catalog)
**Intra-function `bl` as long branch.** When agbcc needs an
unconditional branch beyond ±2KB (Thumb `b` range), it emits `bl` to an
interior label. Signature: (a) BL site and target inside the same
function body, (b) distance > 2048, (c) target flows to the function's
epilogue/shared tail without returning, (d) code after the BL site is
dead or reached via other paths. Do NOT mistake these for calls —
validate by checking the target's reachable terminators, not just the
BL opcode. (This generalizes the 0x0802C6E6 case from wave3_a.)

## Part 1 — Pointer-table discoveries: 4 MATCHED, 1 INTERIOR, 1 BLOCKED

### MATCHED (all require old_agbcc — see idiom below)
- **List_UnlinkPushHead @ 0x080044F4** (36 B, mmbcc/src/wave4_j.c).
  Unlinks node from doubly-linked list (`node->next->prev =
  node->prev; node->prev->next = node->next;` — the `->` chain shape is
  required to force the ROM's reload sequence), then pushes node as new
  head of global list at `*(0x0200081C)` (head +0x10, u16 count +0xA).
  old_agbcc keeps the list pointer in r1 (`ldr r1,[r1]`); main agbcc
  moves it to r2. 29 data-table refs, 0 BL callers.
- **Obj_SetFromTableA/B/C @ 0x08011E98/0x08017084/0x08020F58** (24 B
  each, mmbcc/src/wave4_j.c). `*(u32*)(obj+12)=4;
  *(u32*)(obj+20)=table[obj[9]]->val10` with tables 0x08223CC0 /
  0x082243D8 / 0x08226EF0. The `base` + `&base[obj[9]]` two-statement
  shape reproduces the ROM's order (pool, ldrb, lsls, adds, =4 store,
  double deref). old_agbcc puts the index byte in r3; main agbcc uses
  r1. 2/19/8 data-table refs respectively, 0 BL callers.

### INTERIOR
- **sub_08033962 @ 0x08033962** — see above; fold into sub_08030AD4.

### BLOCKED — sub_0804C4FC @ 0x0804C4FC (script-consume-byte)
ROM (64 B): `b4b0 push {r4,r5}`; `6c0a ldr r2,[r1,#0x40]`;
`7813 ldrb r3,[r2]`; `2b80 cmp r3,#0x80`; `d802 bhs`; if/else storing
`ctx[5]`/`[r1,#0x40]`; `6a09 ldr r1,[r1,#0x20]`; null check; `2583 movs
r4,#0x83`; `2440 movs r5,#0x40`; loop with `tst r2,r4` / `tst r2,r5` /
`n[0x11]==v` check; `*n |= 0x40`; break; `bcb0 pop {r4,r5}`; `4770 bx lr`.
Semantics: consume a byte from a script cursor (if <0x80, stash to
ctx[5] and advance; else reload v from ctx[5]), then scan a linked list
(via +0x34) for a node with flags &0x83 set, &0x40 clear, and id byte
+0x11 == v; set its 0x40 flag and stop.

**Blocker: lr-push quirk.** Both agbcc and old_agbcc, with and without
-mthumb-interwork, emit `push {r4,r5,lr}` (not `push {r4,r5}`) whenever
callee-saved r4/r5 are used in this function shape. ROM has
`push {r4,r5}` / `pop {r4,r5}` / `bx lr` with no lr save. Tried: while,
do-while, for, goto-CFG, if+while, constants hoisted vs local,
u8 vs u32 for v, `v<0x80` vs `v>=0x80`, dummy param vs none —
the lr push persists in all variants across all 3 compiler settings.
The ROM's prologue is not producible from C with the available
toolchains. (Minimal repro: any if/else leaf makes main-agbcc push lr;
any r4/r5-using loop makes old_agbcc push lr.)
2 data-table refs (0x0804C9DC +1), 0 BL callers.

## Part 2 — Blocked revisits

### MATCHED — Wrap_0804DF9E @ 0x0804DF9E (no-interwork TU)
ROM (8 B): `b500 push {lr}`; `f7ff fefc bl 0x0804DD9C`;
`2000 movs r0,#0`; `bd00 pop {pc}`.
```c
u32 Wrap_0804DF9E(void) { sub_0804DD9C(); return 0; }
```
in mmbcc/src/wave4_j_noiw.c, compiled WITHOUT -mthumb-interwork —
byte-identical codegen (the exact DivZeroStub precedent from
wave3_d_noiw.c). Notes: (a) the assembler pads the section with a
2-byte nop; ROM has the next function at 0x0804DFA8 immediately —
strip like GetIndexedU8 (wave3_a). (b) In a minimal `ld -T` test at
0x0804DF9E the BL linked 2 bytes short (`fb fe` vs `fc fe`); the same
object links the BL correctly at 0x0804DE64, and the DivZeroStub
precedent (identical shape, same callee) is MATCHED in the project —
treated as a minimal-harness linker quirk, not a source problem.
Coordinator: verify the BL bytes in the full build.

### Still BLOCKED — Frag_0804C558 @ 0x0804C558 (register allocation)
New angles tried: old_agbcc (the List_UnlinkPushHead fix) and
volatile write-posting read `(void)*(volatile u8 *)p` to force the
`ldrb`. Result: the load is now emitted, but both compilers allocate
the temp and the loaded byte to r0 (`adds r0,r2,#1`; `ldrb r0,[r2]`);
ROM uses r3 for both (`1c53 adds r3,r2,#1`; `7813 ldrb r3,[r2]`) and
never touches r0. r0-in is dead, so no C shape makes r0 "live" to push
the allocator to r3. No genuinely new angle left; stays BLOCKED.
(Also confirmed: 0 BL callers; real entry after `bx lr`+nop at
0x0804C554/0x0804C556 — not an interior label.)

### Other old blockers
No genuinely new angles found for Sram_VerifyCompare, StridedCopy,
Vec2_CopyMirrored, Obj_AddEntry, ChipSlot_Tick, Text_OpenDialogue, or
MainLoop. (Vec2_CopyMirrored's note already exhausts old_agbcc;
the struct-layout hypothesis remains the only unexplored angle but is
not something I can test without the struct context.) Not re-run.

## New idioms / codegen notes (worker J)
1. **old_agbcc register allocation** (extends wave3_b idiom 1 to two
   more sites): main agbcc prefers r1/r2 for certain temps where
   old_agbcc keeps the ROM's r3 (Obj_SetFromTable trio index byte) or
   reuses r1 (List_UnlinkPushHead list pointer). When main agbcc
   mis-allocates by one register with otherwise identical codegen, try
   old_agbcc before restructuring.
2. **`->` chains defeat CSE for reload sequences**: `node->next->prev
   = node->prev; node->prev->next = node->next;` forces the compiler to
   re-read `node->next`/`node->prev` (matching ROM's
   ldr/str/ldr/ldr/str), where named locals would let it keep them in
   registers.
3. **Intra-function `bl` as long branch** — see above. Check reachable
   terminators, not just the opcode.
4. **No-interwork TU confirmed again**: `push {lr}; bl; movs r0,#0;
   pop {pc}` wrappers (Wrap_0804DF9E) need agbcc WITHOUT
   -mthumb-interwork, exactly like DivZeroStub.
