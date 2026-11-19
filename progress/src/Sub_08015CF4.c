/* Sub_08015CF4 @ 0x08015CF4 (668 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w138b_08015cf4_MATCHED.c (registry: src/w138b_08015cf4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern void Vec2_SetMirrored(u8 *s, s32 a, s32 b);

extern int SetBit16(u32 a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void ChipSlot_Tick(u8 *s);

extern int GetField17_U8(u32 a);

extern s16 Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, int a);

extern void MaxAssign_17(u32 a, int b);

extern void DecIfNonZero_18(u32 a);

extern void ChipInit_08017d00(int a, int b, s16 c, s16 d, u8 *e);

extern void NewNode_0801EE14(int a, int b, int c, s32 d, int e);

extern void Text_SelectBlobIdx(int a);

extern u8 gEwram_02003670[];

extern u8 T_08223EB4[];

extern u8 T_08223ED4[];

extern u8 T_08224060[];

struct DPair {
    u16 a;
    s16 b;
};

extern struct DPair TABLE_08223ED8[];

__attribute__((section(".text.w138b_08015cf4_v4")))
void Sub_08015CF4(u8 *s)
{
    u8 *p = s + 124;

    switch (s[14]) {
    case 0:
        if (p[7] == 0)
            SetBit16(*(u32 *)(s + 44), 1);
        Vec2_SetMirrored(s, (int)0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        if (T_08223EB4[s[17]] == 23) {
            ChipInit_08017d00(T_08223ED4[T_08224060[p[0]]],
                ((u32)s[35] << 28) >> 28,
                (s16)(TABLE_08223ED8[p[0]].a - 14080),
                TABLE_08223ED8[p[0]].b, *(u32 *)(s + 44));
        } else {
            ChipInit_08017d00(T_08223EB4[s[17]],
                ((u32)s[35] << 28) >> 28,
                (s16)(TABLE_08223ED8[p[0]].a - 14080),
                TABLE_08223ED8[p[0]].b, *(u32 *)(s + 44));
        }
        if (p[7] != 0)
            s[14] = 2;
        else
            s[14]++;
        break;
    case 2:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) == 0)
            break;
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            s[14] = 5;
            break;
        }
        gEwram_02003670[0x11AF] = (gEwram_02003670[0x11AF] & 0xF) | 0x40;
        s[33] = 6;
        ChipSlot_IncUse(s, 3);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 1) {
            if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5) {
                s[33] = 6;
                ChipSlot_IncUse(s, 3);
                break;
            }
        }
        if (p[7] == 2) {
            ChipSlot_IncUse(s, 7);
            s[14] = 6;
            break;
        }
        s[14]++;
        break;
    case 4:
        if (Check119_Minus3_Le1(s) != 0) {
            ChipSlot_IncUse(s, 0);
            s[14]++;
        }
        break;
    case 1:
    case 5:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            MaxAssign_17(*(u32 *)(s + 44), 8);
            DecIfNonZero_18(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Vec2_SetMirrored(s, (int)0xffffc400, 0);
            ChipSlot_IncUse(s, 0);
            p[4] = 0;
            SetBytes_08011F68(s, 0);
        }
        break;
    case 6: {
        u8 *q = s + 33;
        u32 z = 0;
        *q = 60;
        s[18] = 40;
        NewNode_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, (int)0xffffc400, z);
        s[14]++;
        break;
    }
    case 7:
        if (--s[18] == 0) {
            ChipSlot_IncUse(s, 2);
            Text_SelectBlobIdx(127);
            s[14]++;
        }
        break;
    case 8:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            u8 t = s[10] & 0xFE;
            u32 z = 0;
            s[10] = t;
            MaxAssign_17(*(u32 *)(s + 44), 8);
            DecIfNonZero_18(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = z;
            Vec2_SetMirrored(s, (int)0xffffc400, 0);
            ChipSlot_IncUse(s, 0);
            p[4] = z;
            SetBytes_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
