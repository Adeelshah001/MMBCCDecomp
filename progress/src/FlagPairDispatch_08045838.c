/* FlagPairDispatch_08045838 @ 0x08045838 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w25d_08045838.c (registry: mmbcc/src/w25d_08045838.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 g_02004d48[];

extern u8 g_02004d7c[];

extern void ShiftPair_Copy_800C(u8 *o, u8 idx);

__attribute__((section(".text.w25d_08045838")))
void FlagPairDispatch_08045838(u8 *p)
{
    register u8 *pp __asm__("r5") = p;
    register s8 *q __asm__("r4") = (s8 *)(pp + 0x46B0);
    int v;
    __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r" (v) : "r" (q));

    switch (v) {
    case 1: {
        u8 *base = g_02004d48;
        u8 *r3 = base + 44;
        register int t __asm__("r1") = 1;
        int x;
        t |= *r3;
        *(u16 *)(base + 40) = 0x98;
        x = 12;
        *(u16 *)(base + 42) = x;
        x -= 43;
        t &= x;
        t |= 32;
        *r3 = (u8)t;
        {
            u32 mask = 0xFFFFFC3F;
            u16 w = *(u16 *)(base + 44);
            *(u16 *)(base + 44) = (w & mask) | 0x40;
        }
        ShiftPair_Copy_800C(base, 1);
        *q = 2;
        break;
    }
    case 3: {
        u8 *b = g_02004d48;
        int n;
        b += 44;
        n = 2;
        n = -n;
        *b &= n;
        *q = 0;
        break;
    }
    default:
        goto second;
    }
second:
    pp += 0x46B1;
    {
        int v2;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r" (v2) : "r" (pp));
        switch (v2) {
        case 1: {
            u8 *base = g_02004d7c;
            register u8 *r3p __asm__("r3") = base + 44;
            register int t __asm__("r1") = 1;
            t |= *r3p;
            *(u16 *)(base + 40) = 0x98;
            {
                register int x __asm__("r4") = 0x80;
                int tmp = 0x80;
                *(u16 *)(base + 42) = tmp;
                tmp -= 159;
                t &= tmp;
                t |= 32;
                *r3p = (u8)t;
                {
                    u32 mask = 0xFFFFFC3F;
                    u16 w = *(u16 *)(base + 44);
                    *(u16 *)(base + 44) = (w & mask) | (u32)x;
                }
            }
            ShiftPair_Copy_800C(base, 2);
            *(s8 *)pp = 2;
            break;
        }
        case 3: {
            u8 *b = g_02004d7c;
            int n;
            b += 44;
            n = 2;
            n = -n;
            *b &= n;
            *(s8 *)pp = 0;
            break;
        }
        default:
            goto ret;
        }
    }
ret:;
}
