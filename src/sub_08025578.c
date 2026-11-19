/* FilterCopy @ 0x08025578 (122 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_e.c (registry: src/wave7_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_082297E8[];

/* 0x08025578: FilterCopy (coordinator-verified, 122B + 2B 00 pad). */
void sub_08025578(u8 *p, u8 a, u8 b)
{
    u8 *base;
    u16 n;
    u8 *src;
    u8 *dst;
    u8 v;
    if (a > 6) a = 0;
    if (b > 1) b = 0;
    base = gUnknown_082297E8;
    n = *(u16*)(base + 28);
    src = *(u8**)(base + a * 4);
    dst = *(u8**)(p + 8);
    if (b == 0) {
        if (n == 0) return;
        do {
            v = *src;
            if (*(u8*)(*(u8**)(p + 4) + v))
                *dst++ = v;
            n--;
            src++;
        } while (n != 0);
        return;
    }
    src += n - 1;
    if (n == 0) return;
    do {
        v = *src;
        if (*(u8*)(*(u8**)(p + 4) + v))
            *dst++ = v;
        n--;
        src--;
    } while (n != 0);
}
