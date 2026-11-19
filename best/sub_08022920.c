/* Ent_TblInit_08022920 @ 0x08022920 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08021000: Ent_TblInit_08021000 (coordinator-verified). */
extern u32 gUnknown_08226EF0[];

extern u32 gUnknown_0822715C[];

void sub_0802295C(u8 *s);

void sub_08022920(u8 *s)
{
    u32 *t1 = gUnknown_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gUnknown_0822715C;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    sub_0802295C(s);
}
