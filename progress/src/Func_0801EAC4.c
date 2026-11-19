/* Func_0801EAC4 @ 0x0801EAC4 (268 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w51c_0801eac4_MATCHED.c (registry: src/w51c_0801eac4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Tick(u8 *s);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern void ChipSlot_Setup(u8 *s, u32 a, u32 b);

__attribute__((section(".text.w51c_0801eac4")))
void Func_0801EAC4(u8 *s) {
    u8 *cur = *(u8 **)(s + 40);
    u8 old1;
    u8 old0h;
    ChipSlot_Tick(s);
    if (((cur[0] >> 1) & 1) != 0) {
        if ((u8)(s[119] - 3) > 1)
            return;
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = (u32 **)0x082243D8;
            register u32 sh __asm__("r0");
            u32 *slot;
            __asm__ volatile("" : "+r"(base));
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    } else {
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = (u32 **)0x082243D8;
            register u32 sh __asm__("r0");
            u32 *slot;
            __asm__ volatile("" : "+r"(base));
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    }
    old1 = cur[1];
    {
        register u32 mm __asm__("r1") = 15;
        old0h = (u8)(cur[0] >> 4);
        cur += 4;
        *(u8 **)(s + 40) = cur;
        if (old1 == cur[1] && old0h == (u8)((cur[0] >> 4) & mm)) {
            ChipSlot_IncUse(s, cur[2]);
        } else {
        u16 hv;
        u8 b;
        u8 cl;
        {
            u32 v = 0x200;
            register u32 cp __asm__("r0") = v;
            __asm__ volatile("" : "+r"(v));
            ChipSlot_Setup(s, cur[1] | cp, (u32)(cur[0] >> 4));
        }
        ChipSlot_IncUse(s, cur[2]);
        hv = *(u16 *)0x081705B0;
        b = *(u8 *)(0x020031E4 + ((hv >> 4) << 1));
        cl = (u8)(b & 3);
        {
            int cl2 = cl;
            int mk;
            u32 sh;
            u8 *p69;
            __asm__ volatile("" : "+r"(cl2));
            if (cl2 > 3)
                cl = 3;
            p69 = s + 69;
            sh = (u32)(cl << 2);
            mk = 13;
            __asm__ volatile("" : "+r"(mk));
            mk = -mk;
            *p69 = (u8)((*p69 & mk) | sh);
        }
        {
            u8 tv = (u8)(s[17] + 14);
            s[34] = tv;
        }
        }
    }
    s[18] = cur[3];
}
