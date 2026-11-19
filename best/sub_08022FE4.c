/* F_08022fe4 @ 0x08022FE4 (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* F_08022fe4 @ 0x08022fe4 */
u8 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_08022FE4(u8 *p)
{
    u8 *q;
    if (p[7] & 1)
        return 0;
    q = sub_08020ED4(0, 0, 0, 6);
    if (q != 0) {
        q[0x10] = 2;
        q[0x11] = p[0];
        *(u8 **)(q + 0x28) = p;
    }
    p[7] |= 1;
    return q;
}
