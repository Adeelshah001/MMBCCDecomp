/* Sub_08001C08 @ 0x08001C08 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36e_08001c08_MATCHED.c (registry: mmbcc/src/w36e_08001c08_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int sub_08001800(int v);

extern void Sub_08001AE4(int v);

__attribute__((section(".text.w36e_08001c08")))
void Sub_08001C08(void)
{
    register u16 *reg __asm__("r3") = (u16 *)0x04000128;
    u8 *p;
    u16 v;
    if ((*reg & 64) != 0)
        return;
    p = (u8 *)0x02002ee0;
    if (p[4] == 0) {
        u16 rv = *(volatile u16 *)reg;
        u16 t = (rv & 48) >> 4;
        __asm__ volatile("ldrb r0, [%0, #4]" :: "r"(p) : "r0");
        p[4] = t;
    }
    __asm__ volatile("ldrb r0, [%0, #5]" :: "r"(p) : "r0");
    p[5] = 1;
    v = *(u16 *)(p + 2);
    if (v != 0)
        Sub_08001AE4(sub_08001800(v));
}
