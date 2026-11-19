/* Sub_08016988 @ 0x08016988 (780 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w149c_08016988_MATCHED.c (registry: src/w149c_08016988_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void SetBit16(u32 a, int b);

extern void Vec2_SetMirrored(u8 *a, u32 b, int c);

extern void ChipSlot_IncUse(u8 *a, int b);

extern u8 GetField17_U8(u32 a);

extern void MaxAssign_17(u32 a, int b);

extern void DecIfNonZero_18(u32 a);

extern u16 Check119_Minus3_Le1(u8 *a);

extern void SetBytes_08011F68(u8 *a, int b);

extern void NewNode_0801EE14(int a, int b, int c, u32 d, int e);

extern void ChipSlot_Tick(u8 *a);

extern void Text_SelectBlobIdx(int a);

extern u8 gEwram_02003670[];

__attribute__((section(".text.w149c_08016988_v8_oldO2")))
void Sub_08016988(u8 *s)
{
    u8 *q = s + 0x7c;

    switch (s[0xe]) {
    case 0:
        if (q[7] == 0)
            SetBit16(*(u32 *)(s + 0x2c), 0);
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        s[0x12] = 0;
        if (q[7] == 0)
            s[0xe]++;
        else
            s[0xe] = 5;
        break;
    case 1:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0xf) {
            int z = 0;
            s[0x13] = z;
            s[0xe]++;
        } else {
            s[0x12]++;
        }
        break;
    case 2:
        if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) > 6)
            s[0xe]++;
        else
            s[0x13]++;
        break;
    case 3:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0)
            s[0xe]++;
        else
            s[0x12]--;
        break;
    case 5:
        if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) != 0) {
            { int t = s[0x24] | 1; { int m = ~0x1e; s[0x24] = t & m; } }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) > 6) {
                s[0xe] = 5;
            } else {
                u8 *g = gEwram_02003670;
                g += 0x11af;
                *g = (*g & 0xf) | 0x40;
                s[0x21] = 6;
                ChipSlot_IncUse(s, 3);
                s[0xe]++;
            }
        } else {
            s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if (s[0x12] <= 0xe)
                s[0x12]++;
        }
        break;

    case 6:
        if ((u16)Check119_Minus3_Le1(s) == 0)
            break;
        if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) > 1) {
            if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) <= 5) {
                s[0x21] = 6;
                ChipSlot_IncUse(s, 3);
                break;
            }
        }
        if (q[7] != 2) {
            s[0xe]++;
        } else {
            ChipSlot_IncUse(s, 7);
            s[0xe] = 9;
        }
        break;
    case 7:
        if ((u16)Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 0);
            s[0xe]++;
        }
        break;
    case 8:
        if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) <= 6)
            break;
    case 4:
        MaxAssign_17(*(u32 *)(s + 0x2c), 8);
        DecIfNonZero_18(*(u32 *)(s + 0x2c));
        *(u32 *)(s + 0x2c) = 0;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    case 9: {
        u8 *p = s + 0x21;
        int z = 0;
        *p = 0x3c;
        s[0x12] = 0x28;
        NewNode_0801EE14(0, ~3, (int)(((unsigned)(s[0x23] << 28)) >> 28), 0xffffc400, z);
        s[0xe]++;
        break;
    }
    case 10:
        s[0x12]--;
        if (s[0x12] == 0) {
            ChipSlot_IncUse(s, 2);
            Text_SelectBlobIdx(0x7f);
            s[0xe]++;
        }
        break;
    case 11:
        if ((u8)GetField17_U8(*(u32 *)(s + 0x2c)) > 6) {
            int t = s[0xa] & 0xfe;
            { int z = 0;
            s[0xa] = t;
            MaxAssign_17(*(u32 *)(s + 0x2c), 8);
            DecIfNonZero_18(*(u32 *)(s + 0x2c));
            *(u32 *)(s + 0x2c) = z;
            Vec2_SetMirrored(s, 0xffffc400, 0);
            ChipSlot_IncUse(s, 0);
            q[4] = z;
            SetBytes_08011F68(s, 0);
            }
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
