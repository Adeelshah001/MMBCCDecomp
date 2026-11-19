/* sub_08039CFC @ 0x08039CFC (416 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w83a_08039cfc_MATCHED.c (registry: mmbcc/src/w83a_08039cfc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

s8 Sub_08028778(u8 *a, u32 b);

void Call4E60_4E44(void);

void PalModeSet_4DFC(u8 a);

void SyncObjFlagBits_BEE0(u32 a, u32 b);

void TblState_0804A2DC(u32 a);

void EntryMgr_Teardown(void);

void EntryMgr_Setup(void);

u8 TblGetByte_241F8(u32 a);

s16 Sub200_08024514(u8 a);

u8 sub_0800B148(u8 f, s16 t, u8 mode);

u8 Tst_0800B2D8(void);

u8 TblGetByte_24384(u32 a);

u8 sub_0800B368(u32 f, u32 a, u32 b, u32 c);

u8 Check_B308(void);

void LoadCallClear_4A328(void);

u8 CheckAndSet_B2B4(void);

extern u8 g_02004F80[];

extern u8 gEwram_02004E40[];

extern u32 Tbl_082317FC[];

extern u32 G_08230E28[];

extern u32 G_08230E30[];

__attribute__((section(".text.w83a_08039cfc")))
u8 sub_08039CFC(u8 *s)
{
    u8 r = 0;
    u8 z;
    u8 *p;
    switch ((s8)s[0x469D]) {
    case 0:
        if (Sub_08028778(s + 0x469F, 1) == 0) {
            s[0x469F] = 0;
            s[0x469D]++;
        }
        break;
    case 1:
        Call4E60_4E44();
        PalModeSet_4DFC(g_02004F80[2]);
        SyncObjFlagBits_BEE0(64, 128);
        TblState_0804A2DC(8);
        s[0x4699] = 0;
        s[0x469D]++;
    case 2:
        EntryMgr_Teardown();
        if (sub_0800B148(1, Sub200_08024514((u8)TblGetByte_241F8(128 << 5)), 4) == 0)
            goto f80;
        goto inc;
    case 3:
        EntryMgr_Teardown();
        if (Tst_0800B2D8() == 0)
            goto f80;
        goto inc;
    case 4: {
        u32 f;
        u8 idx;
        EntryMgr_Teardown();
        idx = (u8)(TblGetByte_24384(128 << 5) - 50);
        f = Tbl_082317FC[idx];
        if (sub_0800B368(f, *G_08230E28, *G_08230E30, 0) == 0)
            goto f80;
        goto inc;
    }
    inc:
        s[0x469D]++;
        goto f80;
    case 5:
        EntryMgr_Teardown();
        gEwram_02004E40[20] |= 1;
        if (Check_B308() == 0)
            goto f80;
        {
            int i = 8;
            if ((s8)gEwram_02004E40[i] == 0)
                goto inc;
        }
        p = s + 0x469C;
        z = 0;
        *p = 4;
        s[0x469D] = z;
        LoadCallClear_4A328();
        r = 1;
    f80:
        EntryMgr_Setup();
        break;
    case 6:
        EntryMgr_Teardown();
        if (CheckAndSet_B2B4() == 0)
            goto f80_6;
        p = s + 0x469C;
        z = 0;
        *p = 8;
        s[0x469D] = z;
        s[4] = z;
        r = 1;
    f80_6:
        EntryMgr_Setup();
        break;
    default:
        break;
    }
    return r;
}
