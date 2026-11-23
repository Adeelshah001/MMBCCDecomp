/* F_08049780 @ 0x08049780 (396 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40d_08049780_MATCHED.c (registry: mmbcc/src/w40d_08049780_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804990C(void);

extern u16 sub_08024F08(void);

extern void sub_08024F30(u16 a);

extern u16 sub_08024F48(void);

extern void sub_08024F70(u16 a);

void F_08049780(u8 arg)
{
    u8 idx = arg;
    u8 *g = (u8 *)0x020070f0;
    u32 v24, v28;
    if (g[20] >= idx)
        return;
    g[20]++;
    sub_0804990C();
    switch (idx - 1) {
    case 0:
        sub_08024F30((u16)(sub_08024F08() + 20));
        *(u32 *)(g + 24) |= 8;
        *(u32 *)(g + 28) &= ~8;
        return;
    case 2:
        sub_08024F30((u16)(sub_08024F08() + 20));
        *(u32 *)(g + 24) |= 64;
        *(u32 *)(g + 28) &= ~64;
        return;
    case 4:
        sub_08024F30((u16)(sub_08024F08() + 20));
        *(u32 *)(g + 24) |= 256;
        *(u32 *)(g + 28) &= ~256;
        return;
    case 6:
        *(u32 *)(g + 24) |= 2048;
        *(u32 *)(g + 28) &= ~2048;
        sub_08024F30((u16)(sub_08024F08() + 40));
        return;
    case 8:
        *(u32 *)(g + 24) |= 8192;
        *(u32 *)(g + 28) &= ~8192;
        sub_08024F30((u16)(sub_08024F08() + 60));
        return;
    case 1:
        v24 = *(u32 *)(g + 24);
        v24 |= 16;
        v28 = *(u32 *)(g + 28);
        v28 &= ~16;
        v24 |= 32;
        *(u32 *)(g + 24) = v24;
        v28 &= ~48;
        *(u32 *)(g + 28) = v28;
        sub_08024F70((u16)(sub_08024F48() + 10));
        return;
    case 3:
        *(u32 *)(g + 24) |= 128;
        *(u32 *)(g + 28) &= ~128;
        sub_08024F70((u16)(sub_08024F48() + 10));
        return;
    case 5:
        v24 = *(u32 *)(g + 24);
        v24 |= 512;
        v28 = *(u32 *)(g + 28);
        v28 &= ~512;
        v24 |= 1024;
        *(u32 *)(g + 24) = v24;
        v28 &= ~1536;
        *(u32 *)(g + 28) = v28;
        sub_08024F70((u16)(sub_08024F48() + 10));
        return;
    case 7:
        *(u32 *)(g + 24) |= 4096;
        *(u32 *)(g + 28) &= ~4096;
        sub_08024F70((u16)(sub_08024F48() + 30));
        return;
    default:
        return;
    }
}
