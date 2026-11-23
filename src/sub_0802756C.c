/* Sub_0802756C @ 0x0802756C (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0802756c_MATCHED.c (registry: mmbcc/src/w35c_0802756c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void QueueResourceTransfer(u8 *p, int v);

extern void sub_0800288C(u8 *p, int v);

extern void sub_080062B4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);

void sub_0802756C(void)
{
    u8 *tbl = (u8 *)0x0830b638;
    QueueResourceTransfer(tbl, 0x4dc0);
    tbl += 12;
    sub_0800288C(tbl, (176 << 1));
    sub_080062B4(0, 0, 30, 20, 110, 11, 0x080f2228);
}
