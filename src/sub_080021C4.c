/* Init_080021C4 @ 0x080021C4 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r.c (registry: src/wave8_r.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_080021C4(void) {
    u32 *p = (u32 *)0x02002FB0;
    u32 stackMarker;

    p[0] = 0;
    p[50] = 0;
    stackMarker = 0x11111111;
    {
        volatile u32 *io = (volatile u32 *)0x040000D4;

        io[0] = (u32)&stackMarker;
        io[1] = 192 << 19;
        io[2] = 0x85006000;
        return io[2];
    }
}
