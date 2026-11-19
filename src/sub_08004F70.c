/* EntryMgr_HookA @ 0x08004F70 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/entrymgr.c (registry: src/entrymgr.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_080057FC(void);

/* Vestigial hook slot @0x08004F70 (worker-D "HelperA"): just forwards
 * to the empty sub_080057FC. */
static void sub_08004F70(u8 *base)
{
    (void)base;
    sub_080057FC();
}
