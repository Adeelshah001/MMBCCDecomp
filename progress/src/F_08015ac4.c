/* F_08015ac4 @ 0x08015AC4 (560 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w41c_08015ac4_MATCHED.c (registry: mmbcc/src/w41c_08015ac4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern void Vec2_SetMirrored(u8 *s, u32 x, u8 y);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern s32 GetField17_U8(u32 p);

extern s32 Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

extern void MaxAssign_17(u32 p, u8 v);

extern void DecIfNonZero_18(u32 p);

extern u8 *NewNode_0801EE14(u8 a, s32 b, u32 c, u32 d, u32 e);

extern void Text_SelectBlobIdx(s32 idx);

extern void Sub_0801D070(s32 a, u8 *s, u32 *out, u16 v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w41c_08015ac4")))
void F_08015ac4(u8 *s) {
    u8 *p = s + 124;
    u8 mode = s[14];
    if (mode > 6) goto tail;
    switch (mode) {
    case 0:
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        __asm__ volatile("" ::: "memory");
        goto inc;
    case 1: {
        u8 v;
        v = (u8)GetField17_U8(*(u32 *)(s + 44));
        if (v == 0) goto tail;
        v = (u8)GetField17_U8(*(u32 *)(s + 44));
        if (v > 6) {
            s[14] = 3;
            goto tail;
        }
        {
            u8 *tbl = (u8 *)0x02003670;
            __asm__ volatile("" : "+r" (tbl));
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        ChipSlot_IncUse(s, 3);
        s[14]++;
        goto p6;
    }
    case 2: {
        u8 v;
        v = (u8)GetField17_U8(*(u32 *)(s + 44));
        if (p[6] >= v) goto check119;
        v = (u8)GetField17_U8(*(u32 *)(s + 44));
        if (v > 5) goto check119;
        {
            u8 *tbl = (u8 *)0x02003670;
            __asm__ volatile("" : "+r" (tbl));
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        ChipSlot_IncUse(s, 3);
        goto p6;
    }
    p6:
        p[6] = (u8)GetField17_U8(*(u32 *)(s + 44));
        goto tail;
    check119:
        if ((s16)Check119_Minus3_Le1(s) == 0) goto tail;
        else if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 6) {
            u32 buf[2] = {0, 0};
            Sub_0801D070(0, s, buf, *(u16 *)(p + 8));
            if (p[7] == 2) {
                ChipSlot_IncUse(s, 7);
                s[14] = 4;
                goto tail;
            } else {
                ChipSlot_IncUse(s, 0);
                goto inc;
            }
        } else goto tail;
    case 3:
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 6) goto tail;
        MaxAssign_17(*(u32 *)(s + 44), 8);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        __asm__ volatile("" ::: "memory");
        goto tail;
    case 4: {
        u8 *q = s + 33;
        u32 zero = 0;
        *q = 60;
        s[18] = 40;
        NewNode_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, 0xffffc400, zero);
        goto inc;
    }
    case 5:
        s[18]--;
        if (s[18] != 0) goto tail;
        ChipSlot_IncUse(s, 2);
        Text_SelectBlobIdx(127);
    inc:
        s[14]++;
        goto tail;
    case 6: {
        u32 zero;
        u8 m;
        u8 v10;
        if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 6) goto tail;
        m = 254;
        v10 = s[10] & m;
        zero = 0;
        s[10] = v10;
        MaxAssign_17(*(u32 *)(s + 44), 8);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = zero;
        Vec2_SetMirrored(s, 0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        p[4] = zero;
        SetBytes_08011F68(s, 0);
    }
    }
tail:
    ChipSlot_Tick(s);
}
