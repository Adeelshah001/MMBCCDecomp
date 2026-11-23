/* Sub_08021780 @ 0x08021780 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08021780_MATCHED.c (registry: staging/wave34_C/w34c_08021780_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void QueueResourceTransfer(u8 *p, u32 x);

void sub_08021780(void)
{
    u8 *p = (u8 *)0x08173760;
    u32 base = *(u32 *)(p + 108);
    u32 t = *(u32 *)(base + 68);
    u8 *q;
    u32 w;
    t += 68;
    base += t;
    q = (u8 *)0x0817386c;
    w = *(u16 *)(q + 54);
    QueueResourceTransfer((u8 *)base, (w << 5) + 0x10000);
}
