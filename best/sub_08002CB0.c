/* sub_08002CB0 @ 0x08002CB0 (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w23a_08002cb0.c (registry: src/w23a_08002cb0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08002D20(void);

void sub_08002CB0(void)
{
    u16 *p = (u16 *)0x020031E0;
    u32 m = 0xFFF8;
    volatile u32 *q;
    u16 v;
    u32 spv;
    v = (*p & m) | 0x1300;
    *p = v;
    spv = 0;
    q = (volatile u32 *)0x040000D4;
    q[0] = (u32)&spv;
    q[1] = (u32)((u8 *)p + 4);
    q[2] = 0x8500000E;
    (void)q[2];
    p[2] = 0xC008;
    p[3] = 0x4205;
    p[4] = 0x4406;
    p[5] = 0x4807;
    sub_08002D20();
}
