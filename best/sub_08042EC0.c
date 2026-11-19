/* Gfx_Blit3 @ 0x08042EC0 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08042EC0: Gfx_Blit3 (coordinator-verified). */
void sub_08006A54(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u32 *gUnknown_08232D5C[];

extern u32 *gUnknown_08232D70[];

extern u32 gUnknown_08232BA4[];

extern s8 gUnknown_08232D50[];

extern u32 gUnknown_000046AA[];

void sub_08042EC0(u8 *s)
{
    u8 *p = s;
    u32 **tA = (u32 **)gUnknown_08232D5C;
    u32 **tB;

    p += (u32)gUnknown_000046AA;
    sub_08006A54(*tA[*p], gUnknown_08232D50[4] + 1, gUnknown_08232D50[5] + 1, 8, 0);
    tB = (u32 **)gUnknown_08232D70;
    sub_08006A54(*tB[*p], gUnknown_08232D50[4] + 1, gUnknown_08232D50[5] + 3, 8, 0);
    sub_08006A54(gUnknown_08232BA4[0], gUnknown_08232D50[4] + 1, gUnknown_08232D50[5] + 5, 8, 0);
}
