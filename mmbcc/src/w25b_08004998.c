/* Wave 33-D: 0x08004998 HexFormat_08004998 — pure-C 0-diff swap-in.
 * Replaces the Wave 25-B version (main agbcc + python patch) with a pure-C
 * 0-diff build (108 B incl pool, main agbcc, NO post-process patch).
 * Drop-in content for mmbcc/src/w25b_08004998.c (section renamed to match).
 * Verified 2026-10-24 by W33-D: clean-room recompile, link at 0x08004998,
 * 0 diffs over true extent 108 B (0x08004998-0x08004A04).
 * Registry: W25-B MATCHED row (mmbcc/src/w25b_08004998.c) stays — no new row.
 * Idioms:
 * - Pool-const pin with initialization forces literal-pool load into r1:
 *     register u32 poolr __asm__("r1") = 0xFFFF0000u;  (supersedes W22-D
 *     "pinning ignored for constants"; with pool pinned, c lands in r7
 *     naturally, breaking the W24-D catch-22)
 * - Combiner-defeating mask: register u32 dm __asm__("r0") = d; +
 *     __asm__ volatile("" : "+r" (dm)); materializes the u16 mask
 *     (lsls r3,r3,#16; lsrs r0,r3,#16) instead of folding into the shift
 * - Explicit copy asm: __asm__ volatile("add %0, %1, #0" : "=r"(tmp):"r"(d16))
 *     forces the redundant adds r0,r2,#0
 * - Unpinning tmp lets gcc choose r0 and emit ROM's mov r3,sp; adds r1,r3,r0
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void DrawText_048B4(u8 *p, u32 x, u32 y);

__attribute__((section(".text.w25b_08004998")))
void HexFormat_08004998(u32 p, u16 b, u16 c, u16 d)
{
    char buf[16];
    register u32 dm __asm__("r0") = d;
    register u32 d16 __asm__("r2");
    s32 tmp;
    s32 t;

    __asm__ volatile("" : "+r" (dm));
    d16 = dm << 16;
    __asm__ volatile("add %0, %1, #0" : "=r" (tmp) : "r" (d16));
    tmp >>= 16;
    {
        char *bp0 = &buf[tmp];
        *bp0 = 0;
    }
    {
        register u32 poolr __asm__("r1") = 0xFFFF0000u;
        t = (s32)(d16 + poolr);
    }
    if (t >= 0) {
        do {
            s32 idx = t >> 16;
            char *bp = &buf[idx];
            u32 q = p & 15;
            u32 ch = q + '0';
            *bp = (char)ch;
            if ((ch & 255) > (u32)'9')
                *bp = (char)(q + 'A' - 10);
            p >>= 4;
            t = (idx - 1) << 16;
        } while (t >= 0);
    }
    DrawText_048B4(buf, b, c);
}
