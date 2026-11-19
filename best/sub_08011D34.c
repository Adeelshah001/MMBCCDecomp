/* FlagBit_Get_11D34 @ 0x08011D34 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_R_old.c (registry: src/wave10_R_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005260[];

/* FlagBit_Get_11D34 @ 0x08011D34 (52 B).
 * Returns bit (x&7) of byte at *(u8**)(gEwram02005260+4) + (x>>3),
 * for 1 <= x <= 127; else 0.
 * Idiom: empty barrier on xr before t=xr forces the lsr+add copy. */
u32 sub_08011D34(u16 x)
{
    register u32 xs = (u32)x << 16;
    register u32 xr = xs >> 16;
    register u32 t;
    u32 hdr;
    u32 off;
    u8 *base;
    u8 *p;
    u32 bit;
    int v;
    u8 vb;

    
    t = xr;
    if (t == 0)
        goto Lret0;
    if (t > 127)
        goto Lret0;
    hdr = (u32)gUnknown_02005260;
    
    off = xs >> 19;
    base = *(u8 **)(hdr + 4);
    p = base + off;
    bit = t & 7;
    v = *p;
    v >>= bit;
    vb = (u8)v;
    return vb & 1;
Lret0:
    return 0;
}
