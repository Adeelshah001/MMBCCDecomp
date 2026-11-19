/* TblValidate @ 0x0800300C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ent12 { u32 *f0; u16 f4; u16 _06; u32 _08; };

extern struct Ent12 gUnknown_08106D7C[];

extern u8 gUnknown_08106DD0[];

u16 sub_0800300C(u16 x)
{
    register u32 xr = (u32)x << 16;
    struct Ent12 *tbl = gUnknown_08106D7C;
    u8 *pbase = gUnknown_08106DD0;
    u32 i = xr >> 13;
    u8 *p = pbase + i;
    u16 vi = *(u16 *)(p + 4);
    struct Ent12 *e = &tbl[vi];
    u32 *q = e->f0;
    if (*q != *(u32 *)p)
        return 0;
    return *(u16 *)((u8 *)q + 4);
}
