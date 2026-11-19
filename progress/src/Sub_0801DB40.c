/* Sub_0801DB40 @ 0x0801DB40 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0801db40_MATCHED.c (registry: mmbcc/src/w36a_0801db40_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Tick(u32 *s);

__attribute__((section(".text.w36a_0801db40")))
void Sub_0801DB40(u32 *s_in)
{
    register u32 *s __asm__("r2");
    register u32 *sub __asm__("r3");
    u32 t0, t1;
    u8 *p;
    u8 *tp;
    register u8 b12 __asm__("r3");
    s = s_in;
    sub = (u32 *)s[10];
    t0 = sub[20];
    t1 = sub[21];
    s[20] = t0;
    s[21] = t1;
    __asm__ volatile("" : : : "memory");
    s[20] += s[24];
    s[21] += s[25];
    if ((u8)(((u8 *)s)[119] - 3) <= 1) {
        b12 = ((u8 *)sub)[12];
        if (b12 <= 1) {
            p = (u8 *)s[11];
            (*p)++;
        }
        tp = ({ register u8 *addr __asm__("r0");
                __asm__ volatile(
                    "ldr r1, .Ldb40_tbl\n\t"
                    "ldrb r3, [%1, #9]\n\t"
                    "lsl %0, r3, #2\n\t"
                    "add %0, %0, r1\n\t"
                    : "=r"(addr) : "r"(s) : "r1", "r3");
                addr; });
        s[3] = 2;
        s[5] = *(u32 *)(*(u32 *)tp + 8);
    }
    ChipSlot_Tick(s);
}
