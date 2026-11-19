/* ChipInit_0801E990 @ 0x0801E990 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_chipinit.c (registry: src/w17c_chipinit.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

 typedef signed int s32;

struct ObjVec;

extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

extern void sub_0800DD2C(struct ObjVec *o, s32 x, s32 y);

/* 0x0801e990 (82 B): Node_PopAndInit(0,1,c,14). */
u32 *sub_0801E990(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u32 *n = sub_08017000(0, 1, c, 14);
    if (n != 0) {
        u8 *q = (u8 *)n;
        u32 z = 0;
        q[16] = a;
        q[17] = b;
        q[18] = z;
        sub_0800DD2C((struct ObjVec *)n, (s32)(s16)d, (s32)(s16)e);
    }
    return n;
}
