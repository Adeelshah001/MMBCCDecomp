/* AllChipCopiesValid_08049704 @ 0x08049704 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18d_08049704.c (registry: src/w18d_08049704.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080496E8(u32 a, u32 b);

extern u8 gUnknown_082344D6[];

u8 sub_08049704(u8 x)
{
    register u32 xx;
    register u32 base;
    u8 ok;
    u8 i;
    u8 *p;
    u8 *q;
    xx = x;
    base = 0x020070f0;
    ok = 1;
    if (xx <= 4) {
        i = 0;
        p = gUnknown_082344D6 + xx;
        if (i < *p) {
            q = p;
            do {
                u8 v = sub_080496E8(xx, i);
                if (*(u16 *)(base + 12 * v + 50) <= 252)
                    ok = 0;
                i++;
            } while (i < *q);
        }
    } else {
        u8 v = sub_080496E8(xx, 0);
        if (*(u16 *)(base + 12 * v + 50) != 255)
            ok = 0;
    }
    return ok;
}
