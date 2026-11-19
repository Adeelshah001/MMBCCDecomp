/* Sub_08020660 @ 0x08020660 (396 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w46a_08020660_MATCHED.c (registry: src/w46a_08020660_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void ChipSlot_Tick(u8 *s);

extern u8 *NewNode_080203A4(u8 *a, u8 *b, u8 c);

__attribute__((section(".text.w46a_08020660")))
void Sub_08020660(u8 *s)
{
    u8 *s2 = *(u8 **)(s + 40);
    u8 b;
    int c, t;
    u32 cc, m;
    u8 *p;
    switch (s[13]) {
    case 0:
        if ((u8)(s[119] - 3) > 1) goto exit;
        s[13]++;
        ChipSlot_Setup(s, 0x401b, 0);
        ChipSlot_IncUse(s, 2);
        if (s[17] & 2) {
            s[72] = 1;
            s[10] |= 16;
        }
        { u8 b0; int c0; int t0; u32 cc0; u32 m0; u8 * p0; int ix0; u8 *tbl0;
ix0 = (*(u16 *)0x081705b0 >> 4) * 2;
tbl0 = (u8 *)0x020031e4;
__asm__ volatile("" : "+r"(tbl0));
ix0 += (int)tbl0;
b0 = *(u8 *)ix0;
c0 = b0 & 3;
t0 = c0;
__asm__ volatile("" : "+r"(t0));
if (t0 > 3) c0 = 3;
p0 = s + 69;
cc0 = c0 << 2;
__asm__ volatile("movs %0, #13" : "=r"(m0));
m0 = -m0;
*p0 = (*p0 & m0) | cc0;
}
        s[18] = 0;
        NewNode_080203A4(s, s + 18, s[17]);
        /* fallthrough */
    case 1:
        if (s[18] == 0) goto exit;
        s[13]++;
        s2[10] |= 2;
        /* fallthrough */
    case 2:
        if (s2[10] & 1) goto exit;
        s[13]++;
        s[18] = 0;
        /* fallthrough */
    case 3:
        if (s[18] == 0) goto exit;
        s[13]++;
        ChipSlot_Setup(s, 0x401b, 0);
        ChipSlot_IncUse(s, 1);
        if (s[17] & 2) {
            s[72] = 1;
            s[10] |= 16;
        }
        { u8 b3; int c3; int t3; u32 cc3; u32 m3; u8 * p3; int ix3; u8 *tbl3;
ix3 = (*(u16 *)0x081705b0 >> 4) * 2;
tbl3 = (u8 *)0x020031e4;
__asm__ volatile("" : "+r"(tbl3));
ix3 += (int)tbl3;
b3 = *(u8 *)ix3;
c3 = b3 & 3;
t3 = c3;
__asm__ volatile("" : "+r"(t3));
if (t3 > 3) c3 = 3;
p3 = s + 69;
cc3 = c3 << 2;
__asm__ volatile("movs %0, #13" : "=r"(m3));
m3 = -m3;
*p3 = (*p3 & m3) | cc3;
}
        s[19] = 30;
        /* fallthrough */
    case 4:
        if ((u8)(s[119] - 3) > 1) goto exit;
        __asm__ volatile("movs %0, #3" : "=r"(m));
        m = -m;
        s2[10] &= m;
        {
            u32 *addr = (u32 *)0x082243d8;
            register u32 *entry __asm__("r0");
            __asm__ volatile("" : "+r"(addr));
            entry = (u32 *)((u32)(s[9] * 4) + (u32)addr);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*(u32 *)entry + 8);
        }
        break;
    default:
        break;
    }
exit:
    ChipSlot_Tick(s);
    ChipSlot_Tick(s);
}
