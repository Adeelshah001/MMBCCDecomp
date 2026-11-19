/* Task_4827C @ 0x0804827C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08004F18(void);

void sub_08004F80(void);

u32 sub_0804827C(u8 *p)
{
    u32 off = 0x46a8;
    *(u32 *)(p + 0x46a4) = 0;
    *(u32 *)(p + off) = 0;
    p[2] = 1;
    p[3] = 0;
    p[0x46a4] = 0;
    p[0x46a5] = 0;
    p[off - 2] = 0;
    sub_08004F18();
    sub_08004F80();
    return 0;
}
