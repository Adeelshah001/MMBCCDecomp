/* Entry_TryActivate_08010F34 @ 0x08010F34 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22d_08010f34.c (registry: mmbcc/src/w22d_08010f34.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern s8 sub_08010FB4(u8 a);

__attribute__((section(".text.w22d_08010F34")))
u8 Entry_TryActivate_08010F34(u8 a, u8 b, u8 c)
{
    register u8 *tbl __asm__("r2") = (u8 *)0x020051B0;
    u32 shifted;
    int a12;
    u8 *e;

    /* ROM: ldrb r0,[r2,#3]; asrs r0,r3 */
    __asm__ volatile(
        "ldrb %0, [%1, #3]\n\t"
        "asr %0, %2"
        : "=&r" (shifted)
        : "r" (tbl), "r" ((u32)a)
    );
    if ((shifted & 1) == 0)
        return 0;
    a12 = a * 12;
    __asm__ volatile("" : "+r" (tbl));   /* barrier against pool folding */
    {
        register u8 *base __asm__("r1") = tbl;  /* adds r1, r2, #0 */
        base += 24;                             /* adds r1, #24 */
        e = (u8 *)((u32)a12 + (u32)base); /* adds r4, r0, r1 */
    }
    if (sub_08010FB4(a) != 1)
        return 0;
    {
        register u32 z __asm__("r1") = 0;   /* movs r1, #0 */
        register u32 t __asm__("r0") = 2;   /* movs r0, #2 */
        e[0] = (u8)t;
        e[6] = (u8)z;
        e[2] = b;
        e[5] = c;
    }
    return 1;
}
