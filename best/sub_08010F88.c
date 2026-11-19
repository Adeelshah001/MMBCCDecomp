/* ClearSlot_10F88 @ 0x08010F88 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_020051B0[];

u32 sub_08010F88(u8 x)
{
    u8 *p = gUnknown_020051B0;
    int off;
    u8 *q;
    u8 v;

    v = p[3];
    v &= ~(1 << x);
    {
        u8 z = 0;

        p[3] = v;
        off = x * 12;
        p += 24;
        q = p + off;
        q[0] = z;
        q[6] = z;
        q[1] = z;
    }
    return 1;
}
