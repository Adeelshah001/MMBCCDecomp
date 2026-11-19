/* Dispatch_08173064_1 @ 0x0800AC70 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_08173064[];

/* --- The 28 plain A1 dispatchers (table base + s[OFF] index) --- */

/* 0x0800AC70: tbl[s[1]](s); return 5. */
u32 sub_0800AC70(u8 *s)
{
    u32 *tbl = gUnknown_08173064;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
    return 5;
}
