/* Sub_0801D070 @ 0x0801D070 (302 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w57c_0801d070_MATCHED.c (registry: src/w57c_0801d070_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

typedef struct { u32 x, y; } Pair;

extern u32 *sub_08017000(u8 a, u8 b, u8 c, u8 d);

extern u32 gUnknown_020053C0;

extern u16 gUnknown_08226A44[];

u32 *sub_0801D070(u8 kind, u32 *parent, u32 *info, u16 count)
{
    u8 buf[4];
    u32 *node = 0;
    short i;
    u8 n;
    int off;
    u32 *prev;

    if (count > 9999)
        count = 9999;
    for (i = 0; i <= 3; i++) {
        buf[i] = count / gUnknown_08226A44[i];
        count %= gUnknown_08226A44[i];
    }
    n = 4;
    i = 0;
    while (buf[i] == 0) {
        n--;
        i++;
        if (i > 2)
            break;
    }
    if (*(s16 *)((u8 *)gUnknown_020053C0 + 10) < n)
        return 0;
    off = (-5 * n) << 7;
    prev = parent;
    for (i = 0; i < n; i++) {
        node = sub_08017000(1, 1, 0, 12);
        ((u8 *)node)[16] = 1;
        ((u8 *)node)[17] = (kind << 4) | i;
        ((u8 *)node)[18] = n;
        ((u8 *)node)[19] = buf[4 - n + i];
        ((u32 *)node)[10] = (u32)prev;
        if (i != 0)
            ((u32 *)prev)[11] = (u32)node;
        *(Pair *)((u8 *)node + 88) = *(Pair *)info;
        ((u32 *)node)[22] += off;
        off += 1280;
        prev = node;
    }
    if (node != 0)
        ((u32 *)node)[11] = 0;
    return node;
}
