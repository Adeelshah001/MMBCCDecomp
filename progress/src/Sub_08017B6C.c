/* Sub_08017B6C @ 0x08017B6C (372 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40c_08017b6c_MATCHED.c (registry: mmbcc/src/w40c_08017b6c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 GetField17_U8(u8 *s);

void DecIfNonZero_18(u8 *s);

void ChipSlot_Setup(u8 *s, u16 b, u8 c);

void ChipSlot_IncUse(u8 *s, u8 idx);

void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w40c_08017b6c")))
void Sub_08017B6C(u8 *s)
{
    u32 i0 = s[16];
    u32 sh0 = i0 << 4;
    u8 *ent = (u8 *)(sh0 + 0x082263A8);
    u8 *obj = *(u8 **)(s + 44);
    switch (s[13]) {
    case 0: {
        u8 v = (u8)(s[0x77] - 3);
        if (v > 1 && GetField17_U8(obj) == 0)
            break;
        if (ent[0] != ent[6]) {
            u16 a = 768;
            u16 ctr;
            u8 bits;
            int vv;
            int m;
            a |= ent[1];
            ChipSlot_Setup(s, a, ent[6]);
            ctr = *(u16 *)0x081705B0;
            bits = ((u8 *)0x020031E4)[(ctr >> 4) * 2] & 3;
            vv = bits;
            m = -13;
            __asm__ volatile("" : "+r" (vv));
            if (vv > 3)
                bits = 3;
            __asm__ volatile("" : "+r" (m));
            s[69] = (bits << 2) | (s[69] & m);
            s[34] = 14;
        }
        ChipSlot_IncUse(s, ent[3]);
        s[18] = 25;
        s[13]++;
        break;
    }
    case 1:
        if ((s[18] -= 1) == 0)
            s[13]++;
        break;
    case 2: {
        if (GetField17_U8(obj) <= 6)
            break;
        if (ent[6] != ent[7]) {
            u16 a = 768;
            u16 ctr;
            u8 bits;
            int vv;
            int m;
            a |= ent[1];
            ChipSlot_Setup(s, a, ent[7]);
            ctr = *(u16 *)0x081705B0;
            bits = ((u8 *)0x020031E4)[(ctr >> 4) * 2] & 3;
            vv = bits;
            m = -13;
            __asm__ volatile("" : "+r" (vv));
            if (vv > 3)
                bits = 3;
            __asm__ volatile("" : "+r" (m));
            s[69] = (bits << 2) | (s[69] & m);
            s[34] = 14;
        }
        ChipSlot_IncUse(s, ent[4]);
        s[13]++;
        break;
    }
    case 3: {
        u8 v = (u8)(s[0x77] - 3);
        if (v > 1)
            break;
        DecIfNonZero_18(obj);
        *(u32 *)(s + 44) = 0;
        {
            register u32 *tblp __asm__("r1") = (u32 *)0x082243D8;
            u32 *e = tblp + s[9];
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*e + 8);
        }
        break;
    }
    default:
        break;
    }
    ChipSlot_Tick(s);
}
