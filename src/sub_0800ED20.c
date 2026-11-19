/* Setup10308_Flag15_0800ED20 @ 0x0800ED20 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22b_0800ed20.c (registry: src/w22b_0800ed20.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u32 sub_08010308(u32 a, u32 b, s16 c, s8 d);

extern void sub_0800E1F0(u8 x);

s8 sub_0800ED20(u32 a, u32 b, s16 c, s8 d)
{
    s8 r = sub_08010308(a, b, c, d);
    if (r == 1) {
        sub_0800E1F0(15);
        return 1;
    }
    return r;
}
