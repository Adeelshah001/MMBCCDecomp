# Match notes — text engine (Wave 1)

Worker: Phase-3 matching, 2026-10-20.
File: `mmbcc/src/text.c` (sections `.text.text_select`, `.text.text_open`).

## Text_SelectBlob @0x0804C6B4 — MATCHED

**Status:** Byte-identical (0 differing bytes, code + pool) when compiled
with `tools/agbcc/bin/old_agbcc`. **Does NOT match** with
`tools/agbcc/bin/agbcc` (the Makefile's default) — see below.

**C idiom that works:**
```c
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
__asm__(
    ".globl gTextCfgs\n.set gTextCfgs, 0x08106D7C\n"
    ".globl gTextDir\n.set gTextDir, 0x08106DD0\n"
);
extern u32 gTextCfgs[];
extern u8 gTextDir[];
void Text_OpenDialogue(u32 a, u32 b);

__attribute__((section(".text.text_select")))
void Text_SelectBlob(u16 idx)
{
    u32 off = (u32)idx << 16;
    u32 *cfgs = gTextCfgs;
    u8 *dir = gTextDir;
    u32 *entry;
    u16 sub;

    off >>= 13;
    entry = (u32 *)(dir + off);
    sub = *(u16 *)((u8 *)entry + 4);
    Text_OpenDialogue(*(u32 *)((u8 *)cfgs + sub * 12), entry[0]);
}
```

**Flags:** `-O2 -mthumb-interwork` with `old_agbcc`
(preprocessed via `cpp -I mmbcc/include`, assembled with
`arm-none-eabi-as -mthumb -mcpu=arm7tdmi`).

**Why this shape:**
- The prologue `lsls r0,r0,#16 | ldr r2,[pc] | ldr r1,[pc] | lsrs r0,r0,#13`
  (two literal loads *between* the split shifts) only reproduces when the
  two addresses are materialized from **extern absolute symbols**
  (`gTextCfgs`, `gTextDir` defined via `.set`). With plain immediates
  (`0x08106D7C`, `0x08106DD0`), combine folds the constants into the
  address computations and the loads sink to their use points (after the
  shifts), giving `lsls, lsrs, ldr, ...`.
- The split shifts (`off = idx<<16; ...; off >>= 13;` with the symbol
  inits between) are required; a single `((u32)idx<<16)>>13` keeps the
  shifts adjacent.
- Pool order is `(0x08106D7C, 0x08106DD0)`, matching the init order.

**old_agbcc vs agbcc:** `old_agbcc` (pre-patched variant, see ANALYSIS.md)
allocates the table base to `r2` (`ldr r2, [pc]`), then `sub` goes to `r3`
(`ldrh r3, [r0,#4]`). The newer `agbcc` allocates the table base to `r3`
and `sub` to `r2`. All other bytes are identical. The original ROM has
`r2`, so the original was built with a compiler matching `old_agbcc`.

**Build-system note:** `mmbcc/Makefile` uses `$(AGBCC)` =
`tools/agbcc/bin/agbcc` for all C files. `text.c` will NOT match until
the Makefile uses `old_agbcc` for it (or the register allocation is
coaxed from the newer compiler — not found). `make` stays green either
way; the region only matches with `old_agbcc`.

**Semantics:** `r0 = (idx & 0xFFFF) * 8`; `entry = 0x08106DD0 + r0`;
`sub = *(u16*)(entry+4)`; `cfgWord = *(u32*)(0x08106D7C + sub*12)`;
`blob = entry[0]`; calls `Text_OpenDialogue(cfgWord, blob)`.
The 8-byte directory entries are `(blob_ptr, u16 cfgIdx, u16 pad)` —
the second word's low halfword indexes 12-byte structs at `0x08106D7C`.
Refines symbols_phase2.md: entries are NOT `(blob_ptr, 0)`; the low
halfword of the second word is live.

## Text_OpenDialogue @0x0804CDE8 — BLOCKED

**Status:** Not byte-identical. Best attempt produces correct prologue
(first 12 instructions match exactly) but diverges later.

**What matches:** The prologue through the `cfg[11]`/`blob[2]` loads:
```
push {r4-r7,lr}; mov r7,r8; push {r7}; mov r5,r0; mov r7,r1;
ldr r1,[r5,#52]; ldr r0,[pc] (=0x68736D53); cmp r1,r0; bne End;
ldrb r0,[r5,#11]; ldrb r2,[r7,#2]; cmp r0,#0; beq L2a;
ldr r0,[r5,#0]; cmp r0,#0; beq L14;
ldr r1,[r5,#44]; movs r0,#64; ldrb r1,[r1]; ands r0,r1; cmp r0,#0; bne L20;
```
(pool value `0x68736D53` confirmed at `0x0804CEC8`.)

**Remaining diff (precise):** My best attempt (`/tmp/open4.c` formulation)
is 216 bytes vs 228 expected. Specific divergences:
- At L20 (`0x0804CE20`): original does `ldrb r0,[r7,#2]; adds r2,r0,#0`
  (reload blob[2] via r0, copy to r2); mine loads directly to r2.
- Control-flow shape of the two window loops differs: original has
  a `do/while`-style first loop with the `i < blob[0]` check at both top
  and bottom, and a separate second loop; my goto structure produces
  different branch targets and a shorter encoding.
- Pool placement differs (mine earlier due to shorter code).

**Blob layout refinements (for Phase 4 / recomp):**
- `[+0]` (u8): window count. Loop 1 runs `i` over `[0, min(blob[0], cfg[8]))`.
- `[+2]` (u8): compared against `cfg[9]` (unsigned `bhi`); stored to `cfg[9]`.
- `[+3]` (u8): bit 7 (`0x80`) gates the `sub_0804CBCC(blob[3])` call.
- `[+4]` (u32): copied to `cfg[48]`.
- `[+8]` (u32 each): per-window data dwords, `blob[8 + i*4]` stored to
  window struct `[+64]`.
- Window structs are 80 bytes (`r4 += 80`), built at `cfg[44]` (u32 ptr).
  Per-window init: `[+0] = 192` (u8), `[+32] = i` (u32), `[+64] = blob dword`.
  Second loop (for `i` in `[blob_count, cfg[8])`) writes `[+0] = 0` and
  still calls `Text_UpdateWindows` per window.
- `cfg` struct (pointed to by the table word): `[+52]` is a magic guard
  (`0x68736D53`; incremented on entry, restored on exit; early-return if
  mismatch on entry). `[+11]` (u8) nonzero enables the whole gate block.
  `[+0]` nonzero + `([+44][0] & 64)==0` enables the `[+4]` checks
  (halfword `==0` or signed word `<0` → skip to init). `[+9]` (u8) is the
  high-water mark compared against `blob[2]`.
- Callee `sub_0804C288` = `Text_UpdateWindows(cfg, winStruct)` (two `bl`s);
  `sub_0804CBCC` takes `blob[3]` (u8) as a single arg.

## Files
- `mmbcc/src/text.c` — SelectBlob matched code + OpenDialogue stub.
- Scratch: `/tmp/final_sel.c`, `/tmp/open*.c`, `/tmp/ext*.c` (ephemeral).
