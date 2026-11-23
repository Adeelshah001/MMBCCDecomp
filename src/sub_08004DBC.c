/* Sub_08004DBC @ 0x08004DBC (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08004dbc_MATCHED.c (registry: mmbcc/src/w35c_08004dbc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void QueueResourceTransfer(u8 *p, int v);

extern void sub_080028D0(u8 *p, int a, int b);

void sub_08004DBC(u8 a)
{
    u8 *entry = (u8 *)0x082c0000 + a * 20;
    register u16 *fp = (u16 *)0x020031e6;
    int w;
    
    w = 12;
    w &= *fp;
    QueueResourceTransfer(entry, (w << 12) + 32);
    sub_080028D0((u8 *)0x082c000c + a * 20, 0, 0);
}
