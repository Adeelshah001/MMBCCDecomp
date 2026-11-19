/* Sub_08021FDC @ 0x08021FDC (494 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w59c_08021fdc_MATCHED.c (registry: src/w59c_08021fdc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void SelBlob_Ret(int a);

extern int sub_080052A0(void);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w59c_08021fdc")))
void Sub_08021FDC(u8 *s)
{
    register int a __asm__("r2") = *(u8 *)(*(u32 *)(s + 40));
    register int b __asm__("r3") = *(u8 *)(*(u32 *)(s + 44));
    u8 s18 = s[18];
    int nm, ns;

    switch (s[13]) {
    case 0: {
        u8 old;
        if (a == 255)
            break;
        old = s[13];
        s[13] = 1;
        s[14] = old;
        s[18] = a;
        break;
    }
    case 1: {
        u8 sub = s[14];
        switch (sub) {
        case 0:
            s[14] = s[13];
            *(u32 *)(s + 100) = 192 << 3;
            *(u32 *)(s + 92) = 128 << 4;
            *(u32 *)(s + 84) = 160 << 7;
            if (s[17] == 0)
                *(u32 *)(s + 84) = -20480;
            else
                *(u32 *)(s + 84) = 240 << 8;
            /* fallthrough to shared block */
        case 1: {
            u8 f17 = s[17];
            if (f17 == 0) {
                int v84 = *(u32 *)(s + 84) + *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 > 20479 || b == 2) {
                    s[14]++;
                    s[19] = 8;
                    if (b != 2)
                        SelBlob_Ret(114);
                    *(u32 *)(s + 84) = 160 << 7;
                    *(u32 *)(s + 92) = f17;
                    *(u32 *)(s + 100) = f17;
                }
            } else {
                int v84 = *(u32 *)(s + 84) - *(u32 *)(s + 92);
                int v92;
                int c;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                c = 160 << 7;
                if (v84 <= c || b == 2) {
                    u8 ns14;
                    ns14 = s[14] + 1;
                    f17 = 0;
                    s[14] = ns14;
                    s[19] = 8;
                    if (b != 2)
                        SelBlob_Ret(114);
                    *(u32 *)(s + 84) = c;
                    __asm__ volatile ("add r0, r4, #0\n\tadd r0, #88\n\tstr %0, [r0, #4]" :: "r" (f17) : "r0", "memory");
                    *(u32 *)(s + 100) = f17;
                }
            }
            break;
        }
        case 2: {
            u32 x;
            if (s[19] & s[13]) {
                *(u32 *)(s + 84) = 160 << 7;
                x = *(u32 *)(s + 84) + ((sub_080052A0() & 3) << 8);
            } else {
                *(u32 *)(s + 84) = 160 << 7;
                x = *(u32 *)(s + 84) - ((sub_080052A0() & 3) << 8);
            }
            *(u32 *)(s + 84) = x;
            ns = --s[19];
            if (ns != 0)
                break;
            *(u32 *)(s + 84) = 160 << 7;
            nm = s[13] + 1;
            goto tail;
        }
        }
        break;
    }
    case 2:
        if (a == s18)
            break;
        nm = 3;
        ns = 0;
        /* fallthrough to shared tail */
    tail:
        s[13] = nm;
        s[14] = ns;
        break;
    case 3: {
        u8 sub = s[14];
        switch (sub) {
        case 0:
            s[14] = 1;
            *(u32 *)(s + 100) = 128 << 3;
            *(u32 *)(s + 92) = 192 << 3;
            /* fallthrough to shared block */
        case 1: {
            u8 f17 = s[17];
            if (f17 == 0) {
                int v84 = *(u32 *)(s + 84) + *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 > 61439) {
                    s[14]++;
                    *(u32 *)(s + 84) = 240 << 8;
                    *(u32 *)(s + 92) = f17;
                    *(u32 *)(s + 100) = f17;
                }
            } else {
                int v84 = *(u32 *)(s + 84) - *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 <= -20480) {
                    u32 *p;
                    u32 z;
                    u8 ns14 = s[14] + 1;
                    z = 0;
                    s[14] = ns14;
                    *(u32 *)(s + 84) = -20480;
                    p = (u32 *)(s + 88);
                    p[1] = z;
                    *(u32 *)(s + 100) = z;
                }
            }
            break;
        }
        case 2:
            s[13] = 0;
            s[14] = 0;
            break;
        }
        break;
    }
    }
    ChipSlot_Tick(s);
}
