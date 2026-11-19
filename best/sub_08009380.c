/* TableDispatch_9380 @ 0x08009380 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h1_old.c (registry: src/wave5_h1_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern u32 gUnknown_0817212C[];

extern u8 gUnknown_02004CE0[];

void sub_08009380(void)
{
    u16 i = 0;
    s16 j = i;
    u32 *tbl = gUnknown_0817212C;
    while (j <= 5) {
        u8 *p = gUnknown_02004CE0 + j * 0x34;
        u8 b = *(p + 0x2c);
        if (b & 1) {
            u16 v = *(u16 *)(p + 0x2c);
            u32 idx = ((u32)v << 22) >> 28;
            ((void (*)(u8 *))tbl[idx])(p);
        }
        i = j + 1;
        j = i;
    }
}
