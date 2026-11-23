/* NewNode_0801EE14 @ 0x0801EE14 (82 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_0801ee14.c (registry: src/w18d_0801ee14.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

struct ObjVec { u8 _[64]; };

extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);

extern void sub_0800DD2C(struct ObjVec *o, s32 x, s32 y);

u8 *sub_0801EE14(u8 a, u8 b, u8 c, u16 d, u16 e)
{
    u8 *p = (u8 *)CreateBattleObject(0, 1, c, 16);
    if (p != 0) {
        u8 z = 0;
        p[16] = a;
        p[17] = b;
        p[18] = z;
        sub_0800DD2C((struct ObjVec *)p, (s16)d, (s16)e);
    }
    return p;
}
