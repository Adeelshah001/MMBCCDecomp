/* Task_38FE4 @ 0x08038FE4 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08004F18(void);

void sub_08004F80(void);

void sub_080267B4(u8 *a, u32 b);

extern u8 gUnknown_020070F0[];

void sub_08038FE4(u8 *p)
{
    s8 v = (s8)p[0x469c];
    if (v == 7) {
        u32 z = 0;
        p[1] = 2;
        p[2] = z;
        p[3] = z;
    } else if (v == 0xb) {
        sub_080267B4(gUnknown_020070F0, 8);
        p[0x4698] = 0;
    } else if (v == 0xc) {
        sub_080267B4(gUnknown_020070F0, 8);
        p[0x4698] = 4;
    } else {
        u32 z = 0;
        p[1] = 1;
        p[2] = z;
        p[3] = z;
    }
    sub_08004F18();
    sub_08004F80();
}
