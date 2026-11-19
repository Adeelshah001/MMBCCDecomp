/* Task_35C1C @ 0x08035C1C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 sub_08006DD8(u32 p, u32 a, u32 b, u32 c, u32 d);

extern u8 gUnknown_020070F0[];

void sub_08035C1C(void)
{
    u8 *base = gUnknown_020070F0;
    sub_08006DD8(base[0x13], 0x2f, 4, 2, 0);
    sub_08006DD8(base[0x12], 0x32, 4, 2, 0);
    sub_08006DD8(base[0x11], 0x35, 4, 2, 0);
}
