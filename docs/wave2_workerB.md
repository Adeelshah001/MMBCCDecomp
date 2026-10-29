# Wave 2 worker-B notes — 0x0800DD08 cluster (2026-10-20)

Worker: matching-C, Wave 2 (caller-count order). Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` before any byte trust.
Scratch: `/tmp/wave2_B/` (dd08.c, dd2c.c, dd4c.c, .s/.o/.bin).

## The family

Three leaf utilities operating on a game-object tail struct:

```c
struct ObjVec {
    u8 _00[35];
    u8 flip;      /* +35: bit 7 = mirror X */
    u8 _36[44];   /* +36..+79 */
    s32 x;        /* +80 */
    s32 y;        /* +84 */
};
struct Vec2 { s32 x; /* +0 */ s32 y; /* +4 */ };
```

All three test bit 7 of the flag byte at struct offset +35 and negate the
X component when set (horizontal-mirror-aware vector helpers). No `bl`,
no literal pool, pure Thumb leaf functions.

| Address | Name | Behavior | Status |
|---|---|---|---|
| 0x0800DD2C (30 B, 15 insns) | `Vec2_SetMirrored` | `o->x = (o->flip & 0x80) ? -x : x; o->y = y;` (void) | **MATCHED** |
| 0x0800DD4C (38 B, 19 insns) | `Vec2_AddMirrored` | `o->x += (o->flip & 0x80) ? -x : x; o->y += y;` (void) | **MATCHED** |
| 0x0800DD08 (34 B, 17 insns) | `Vec2_CopyMirrored` | copy `s->{x,y}` to `d->{x,y}`, negating x if *src* flip set; returns `d` | BLOCKED (7-byte regalloc diff) |

## MATCHED: Vec2_SetMirrored @0x0800DD2C

Compiler: **old_agbcc** (`tools/agbcc/bin/old_agbcc`), `-O2
-mthumb-interwork`. Main agbcc does NOT match (see idiom note below).

```c
__attribute__((section(".text.vec2_setmirrored")))
void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y)
{
    u8 *p = (u8 *)o;
    p += 35;

    if ((*p & 0x80) != 0)
        x = -x;
    o->x = x;
    o->y = y;
}
```

Verification (exact task rule):
```
cpp -I /tmp/wave2_B dd2c.c -o dd2c.i
tools/agbcc/bin/old_agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o dd2c.s dd2c.i
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o dd2c.o dd2c.s
arm-none-eabi-objcopy -O binary -j .text.vec2_setmirrored dd2c.o dd2c.bin
# python diff of dd2c.bin[:30] vs baserom[0xDD2C:0xDD2C+30] -> 0 diffs
```
Result: **0 differing bytes** (30/30). Section is 32 B (2 B alignment
padding after the function; padding not part of the ROM function).

## MATCHED: Vec2_AddMirrored @0x0800DD4C

Compiler: **old_agbcc**, `-O2 -mthumb-interwork`. Same shape as Set,
with `+=`.

```c
__attribute__((section(".text.vec2_addmirrored")))
void Vec2_AddMirrored(struct ObjVec *o, s32 x, s32 y)
{
    u8 *p = (u8 *)o;
    p += 35;

    if ((*p & 0x80) != 0)
        x = -x;
    o->x += x;
    o->y += y;
}
```

Verification: same rule; `dd4c.bin[:38]` vs baserom
`[0xDD4C:0xDD4C+38]` -> **0 differing bytes** (38/38).

## BLOCKED: Vec2_CopyMirrored @0x0800DD08 (27/34 bytes)

Best attempt (old_agbcc, `-O2 -mthumb-interwork`):

```c
__attribute__((section(".text.vec2_copymirrored")))
struct Vec2 *Vec2_CopyMirrored(struct Vec2 *d, struct ObjVec *s)
{
    struct Vec2 *dd = d;
    s32 x = s->x;
    s32 y = s->y;

    if ((((u8 *)s)[35] & 0x80) != 0)
        x = -x;
    dd->x = x;
    dd->y = y;
    return dd;
}
```

Byte diff vs ROM (7 bytes, all one register swap):

| Off | ROM | Mine | Meaning |
|---|---|---|---|
| +2 | `1c04` adds r4,r0,#0 | `1c03` adds r3,r0,#0 | d→r4 vs d→r3 |
| +6 | `6d4b` ldr r3,[r1,#84] | `6d4c` ldr r4,[r1,#84] | y→r3 vs y→r4 |
| +22 | `6022` str r2,[r4,#0] | `601a` str r2,[r3,#0] | (consequence) |
| +24 | `6063` str r3,[r4,#4] | `605c` str r4,[r3,#4] | (consequence) |
| +26 | `1c20` adds r0,r4,#0 | `1c18` adds r0,r3,#0 | (consequence) |
| +30 | `bc04` pop {r2} | `bc02` pop {r1} | lr restore reg |
| +32 | `4710` bx r2 | `4708` bx r1 | (consequence) |

Everything else is identical: load order (`ldr r2,[r1,#80]`,
`ldr r3,[r1,#84]`), single `adds r1,#35` (s dead, r1 reused),
`movs r0,#128; ldrb r1,[r1]; ands r0,r1; cmp r0,#0; beq`,
`negs r2,r2`, `pop {r4}; bx` epilogue shape.

Tried (~22 variants, both compilers, -O1/-Os/-O2): explicit `dd = d`
at top / after loads / uninitialized-then-assigned; `d` used directly;
`u8 *p` local at top / after loads / omitted; `s32 x,y` separate vs
single declaration vs separate assign; declaration-order swaps;
load-order swap (compiler does NOT reorder loads — diagnostic only);
ternary `cond ? -x : x` (swaps load order, still d→r3); `s32 *sp`
local; `s32 *d` destination; unused 3rd parameter; `unsigned int` x/y.
In every case old_agbcc and main agbcc both assign d→r3, x→r2, y→r4;
x is pinned to r2 in all shapes (the `negs` use), and the (d,y)→(r3,r4)
assignment is immovable. The ROM's (d,y)→(r4,r3) was not reachable.
Functionally identical; kept as best-effort C in `/tmp/wave2_B/dd08.c`.

## New idioms discovered

1. **old_agbcc vs agbcc register allocation** (extends the
   Text_SelectBlob finding): for the `(u8 *)o; p += 35; if ((*p & 0x80)
   != 0)` shape, main agbcc spills x to r3 and computes the flag
   address in r0 (`add r3,r1,#0; add r0,r0,#35; ldrb r1,[r0]`), while
   old_agbcc keeps the byte pointer in r3 and x in r1
   (`adds r3,r4,#0; adds r3,#35; ldrb r3,[r3]`), matching the ROM.
   Evidence: `/tmp/wave2_B/vD.s` (main) vs `/tmp/wave2_B/vD_old.s`
   (old) — identical except the register assignment. This cluster was
   built with old_agbcc.
2. **Two-`adds` byte-pointer idiom**: `u8 *p = (u8 *)o; p += 35;` as two
   statements reproduces the ROM's `adds r3,r4,#0` + `adds r3,#35`
   (the `+=` is not folded into a single `adds r3,r4,#35`). A single
   `((u8 *)s)[35]` in the condition instead reuses the dead source
   register (`adds r1,#35`), which is what fn1 (0x0800DD08) needs.
3. **`!= 0` on the masked flag** reproduces the ROM's redundant
   `ands r0,r3; cmp r0,#0; beq` (plain `if (f & 0x80)` was not
   separately verified to differ, but `!= 0` matches).
4. **No-`dd`-local spill**: in fn2/fn3 the `adds r4,r0,#0` is the
   compiler's own spill of `o` (r0 clobbered by `movs r0,#128`), not a
   source-level local — no explicit `s = o` copy is needed or wanted
   (adding one perturbs allocation under main agbcc).
5. **Return-address pop register follows the return value**: fn1
   returns `d`, so lr pops to r2 (`pop {r4}; pop {r2}; bx r2`); void
   fn2/fn3 pop to r0 (`pop {r0}; bx r0`). Just write `return d;` /
   void and the compiler does this naturally.

## Feeds / naming notes for coordinator

- Proposed names: `Vec2_SetMirrored` (0x0800DD2C), `Vec2_AddMirrored`
  (0x0800DD4C), `Vec2_CopyMirrored` (0x0800DD08, blocked). "Mirrored"
  = X negated when flag byte +35 bit 7 is set (probable H-flip flag).
- Struct tail: flag byte +35, s32 vector +80/+84. The +80/+84 vector
  with an H-flip flag smells like a sprite/object velocity or offset;
  callers (84/82/71) will confirm. fn1 reads the flag from the
  *source*; fn2/fn3 from the *target itself*.
- Compiler flag for the coordinator's Makefile: these two matched
  functions need **old_agbcc** (like text.c's Text_SelectBlob), not
  the default agbcc. Sections `.text.vec2_setmirrored` /
  `.text.vec2_addmirrored`.
