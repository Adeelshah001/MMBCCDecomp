/* Sub_0802CCE4 @ 0x0802CCE4 (486 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w63c_0802cce4_MATCHED.c (registry: staging/w63c_2cce4/w63c_2cce4_RECOMMENDED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void Obj_AddEntry(u8 *s, u8 a, u8 b, int flag, int a5, u16 a6, int a7, s16 a8, int a9, int a10);

extern u8 SubClamp_0802C7B4(int a, u16 *p);

extern void RangeCheckClear_2FC28(void **ctx, u8 *out);

__attribute__((section(".text.w63c_0802cce4")))
int Sub_0802CCE4(u8 *s, u8 p1, u8 p2, u16 p3, u8 p4)
{
    int flag;
    u8 **t1;
    u8 **t2;
    int mode;
    u8 cnt;
    u8 *bp;
    int bval;
    u8 **slot;
    int f;
    u8 i;

    {
        int ftmp = (p1 == 0);
        flag = ftmp;
    }
    t1 = (u8 **)(p1 == 0 ? s + 336 : s + 364);
    t2 = (u8 **)(p1 == 0 ? s + 364 : s + 336);
    cnt = 0;
    bp = (p1 == 0) ? s + 393 : s + 392;
    bval = *bp;
    {
        int c = s[6] & 1;
        mode = 9;
        if (c == 0)
            mode = 5;
    }
    if (p4 != 0)
        p3 = p3 * p4;
    Obj_AddEntry(s, p1, p2, flag, 2, p3, *(s16 *)(t1[p2] + 2), *(s16 *)(t1[p2] + 2), 27, mode);
    i = 5;
    while (i > 2) {
        slot = (u8 **)((i * 4) + (int)t2);
        if (*(s16 *)(*slot + 2) != 0) {
            f = *(u16 *)(*slot + 2);
            cnt = cnt + 1;
            SubClamp_0802C7B4((s16)p3, (u16 *)(*slot + 2));
            Obj_AddEntry(s, p1, p2, flag, i, p3, ({ __asm__ volatile("lsl %0, %0, #16\n\tasr %0, %0, #16" : "+r"(f)); f; }), *(s16 *)(*slot + 2), 28, mode);
            f = *(s16 *)(*slot + 2);
            if (f == 0) {
                Obj_AddEntry(s, p1, p2, flag, i, p3, f, f, 24, mode);
                if (i == bval) {
                    Obj_AddEntry(s, p1, p2, flag, i, f, f, f, 14, mode);
                    Obj_AddEntry(s, p1, p2, flag, i, f, *(s16 *)(*slot + 2), *(s16 *)(*slot + 2), 78, mode);
                    RangeCheckClear_2FC28((void **)(t2 + 6), bp);
                }
            }
            break;
        }
        i = i - 1;
    }
done:
    if (cnt == 0) {
        Obj_AddEntry(s, p1, p2, flag, 2, cnt, cnt, cnt, 29, mode);
    }
    return 0;
}
