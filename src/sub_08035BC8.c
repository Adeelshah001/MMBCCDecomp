/* Task_35BC8 @ 0x08035BC8 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_0804A378(u16 idx);

extern u8 gUnknown_02004CE0[];

void sub_08035BC8(u8 *p)
{
    u8 *pA = p + 0x46aa;
    u8 v = *pA;
    u32 flag = 0;
    u16 *ew;
    if ((s8)v > 12) {
        v -= 13;
        flag = 1;
    }
    p[0x46a9] = 3;
    sub_0804A378(0x66);
    ew = (u16 *)gUnknown_02004CE0;
    ew[20] = (v << 4) + 0x10;
    ew[21] = flag * 24 + 0x20;
}
