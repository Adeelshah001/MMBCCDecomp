/* ChipInit_080178A8 @ 0x080178A8 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_chipinit.c (registry: src/w17c_chipinit.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

 typedef signed int s32;

struct ObjVec;

extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

extern void sub_0800DD2C(struct ObjVec *o, s32 x, s32 y);

extern void sub_08017458(u8 *s);

/* 0x080178a8 (84 B): Node_PopAndInit(0,1,b,3), u16*(n+120) stores. */
u32 *sub_080178A8(u8 a, u8 b, u16 c, u16 d, u8 *e)
{
    u32 *n = CreateBattleObject(0, 1, b, 3);
    if (n != 0) {
        u16 *p = (u16 *)((u8 *)n + 120);
        u8 *q = (u8 *)n;
        u32 z = 0;
        p[0] = c;
        p[1] = d;
        q[16] = a;
        q[17] = z;
        q[18] = z;
        sub_0800DD2C((struct ObjVec *)n, (s32)(s16)c, (s32)(s16)d);
        sub_08017458(e);
        *(u32 *)((u8 *)n + 44) = (u32)e;
    }
    return n;
}
