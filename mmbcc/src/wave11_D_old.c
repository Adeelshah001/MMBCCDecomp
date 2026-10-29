/* Wave 11 worker D: third-compiler-vintage investigation target.
 * sub_0803FACC (76 B incl. trailing pool) matched byte-identical.
 * See docs/match_notes_wave11_D.md for the full investigation.
 *
 * Findings baked into this source:
 * - The ROM's third decision constant is 0x2030 (pool bytes 30 20 00 00),
 *   NOT 0x3020 as the Wave-10 attempt assumed. With the correct constant
 *   old_agbcc emits a literal pool load like the ROM (the old mismatch (3)
 *   was an artifact of the wrong constant).
 * - `int b = a;` copy is kept alive by an empty read/write asm barrier at
 *   its single use site; without it old_agbcc copy-propagates b away and
 *   allocates the return accumulator to r2 instead of r3.
 * - `int lo = 0x30; ... if (a < lo)` defeats the C-frontend fold that rewrites
 *   `a < 0x30` as `a <= 0x2F` (emitted as cmp #47 / ble at every -O level in
 *   both compilers); the variable constant-propagates away in RTL so the
 *   backend still emits `cmp r1, #0x30` / `blt`.
 * Needs old_agbcc (main agbcc always emits push {lr} / pop {pc} here;
 * old_agbcc emits the ROM's plain `bx lr`).
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

/* 0x0803FACC (76 B): returns 1 if u16 chip in {0x1030,0x3030,0x2030,0x4030}
 * or in 0x30..0x36, else 0. */
__attribute__((section(".text.w11d_0803facc")))
u8 IsSpecialChip_3FACC(u16 chip)
{
    int a = chip;
    int b = a;
    int lo = 0x30;
    u8 r = 0;
    if (a == 0x1030) goto yes;
    if (a > 0x1030) goto big;
    if (a > 0x36) goto no;
    if (a < lo) goto no;
    goto yes;
big:
    if (a == 0x3030) goto yes;
    if (a > 0x3030) goto huge;
    if (a == 0x2030) goto yes;
    goto no;
huge:
    /* Keep the b-copy alive in r2 for the final compare. */
    asm("" : "+r" (b));
    if (b != 0x4030) goto no;
yes:
    r = 1;
no:
    return r;
}
