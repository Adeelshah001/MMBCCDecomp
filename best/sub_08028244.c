/* Tick_08028244 @ 0x08028244 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08028244: Tick_08028244 (coordinator-verified). */
void sub_080267B4(u8 *p, u8 kind);

extern u8 gUnknown_02002F50[];

extern u8 gUnknown_020070F0[];

void sub_08028244(u8 *s)
{
    u8 v = s[1];
    if (v == 0)
        goto zero;
    if (v == 1)
        goto one;
    return;
zero:
    s[6] = 0;
    s[1]++;
one:
    s[6]++;
    if (s[6] > 180)
        goto call;
    {
        struct { u8 pad[4]; u16 flg; } *st = (void *)gUnknown_02002F50;
        if ((st->flg & 1) == 0)
            goto end;
    }
call:
    sub_080267B4(gUnknown_020070F0, 9);
end:;
}
