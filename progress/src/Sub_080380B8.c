/* Sub_080380B8 @ 0x080380B8 (404 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w45b_080380b8_MATCHED.c (registry: src/w45b_080380b8_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef int s32;

extern s8 Sub_08028778(u8 *p, int one);

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(u8 v);

extern void SyncObjFlagBits_BEE0(int a, int b);

extern void TblState_0804A2DC(int a);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

extern int TblGetByte_241F8(int a);

extern s16 Sub200_08024514(u8 v);

extern int sub_0800B148(u32 a, int b, u32 c);

extern int Tst_0800B2D8(void);

extern int TblGetByte_24384(int a);

extern int sub_0800B368(u32 a, u32 b, u32 c, u32 d);

extern u8 Check_B308(void);

extern u8 CheckAndSet_B2B4(void);

extern void LoadCallClear_4A328(void);

extern u8 g_02004F80[];

__attribute__((section(".text.w45b_080380b8")))
int Sub_080380B8(u8 *s)
{
    int ret = 0;
    int r;
    switch ((s8)s[0x469d]) {
    case 0: {
        u8 *p = s + 0x46a0;
        if (Sub_08028778(p, 1) != 0)
            goto done;
        *p = 0;
        s[0x469d]++;
        goto done;
    }
    case 1:
        Call4E60_4E44();
        PalModeSet_4DFC(g_02004F80[2]);
        SyncObjFlagBits_BEE0(64, 128);
        TblState_0804A2DC(8);
        s[0x469d]++;
        /* fall through into case 2 */
    case 2:
        EntryMgr_Teardown();
        r = sub_0800B148(1, Sub200_08024514((u8)TblGetByte_241F8(4096)), 4);
        goto check;
    case 3:
        EntryMgr_Teardown();
        r = Tst_0800B2D8();
        goto check;
    case 4:
        EntryMgr_Teardown();
        {
            u32 t = TblGetByte_24384(4096) - 50;
            u32 *tbl;
            t <<= 24;
            tbl = (u32 *)0x08230d14;
            __asm__ volatile("" : "+r"(t) : "r"(tbl));
            t >>= 22;
            r = sub_0800B368(*(u32 *)((u8 *)tbl + t),
                             *(u32 *)0x0823014c, *(u32 *)0x08230154, 0);
        }
        /* fall through to check */
    check:
        if ((u8)r == 0)
            goto tail;
    statepp:
        s[0x469d]++;
        goto tail;
    case 5: {
        register u8 *base __asm__("r4");
        EntryMgr_Teardown();
        base = (u8 *)0x02004e40;
        {
            register u8 c __asm__("r0") = 1;
            base[20] = c | base[20];
        }
        if (Check_B308() == 0)
            goto tail;
        {
            register s32 v __asm__("r0");
            __asm__ volatile("movs r0, #8\n\tldrsb %0, [%1, r0]" : "=r"(v) : "r"(base));
            if (v == 0)
                goto statepp;
        }
        {
            u8 *q = s + 0x469c;
            u8 z = 0;
            *q = 4;
            s[0x469d] = z;
        }
        LoadCallClear_4A328();
        ret = 1;
        goto tail;
    }
    tail:
        EntryMgr_Setup();
        goto done;
    case 6:
        EntryMgr_Teardown();
        if (CheckAndSet_B2B4() == 0)
            goto tail2;
        {
            u8 *q = s + 0x469c;
            u8 z = 0;
            *q = 5;
            s[0x469d] = z;
            s[4] = z;
        }
        ret = 1;
    tail2:
        EntryMgr_Setup();
        goto done;
    default:
        break;
    }
    done:
    return ret;
}
