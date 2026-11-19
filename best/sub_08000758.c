/* Memcpy16 @ 0x08000758 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_h.c (registry: src/wave4_h.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DB24(void *src, void *dst, unsigned mode);

extern void sub_0804DB28(void *src, void *dst, unsigned mode);

/* 0x08000758: 16-bit memcpy via CpuFastSet/CpuSet. Tentative.
 * The `cnt = n; cnt &= 0x1F; cnt >>= 1` sequence is required for the
 * exact `movs r2,#31; ands r2,r4; lsrs r2,r2,#1` (see match notes). */
void sub_08000758(u8 *src, u8 *dst, u32 size)
{
    u8 *s;
    u8 *d;
    u32 n;

    s = src;
    
    d = dst;
    
    n = size;
    n &= -2;
    if (n == 0)
        return;
    s = (u8 *)((u32)s & -2);
    d = (u8 *)((u32)d & -2);
    if (((u32)s & 2) || ((u32)d & 2)) {
        sub_0804DB28(s, d, (n << 10) >> 11);
        return;
    }
    if (n > 0x1F) {
        u32 bulk = n & -32;
        sub_0804DB24(s, d, (bulk >> 2) & 0x1FFFFF);
        if ((n & 0x1F) == 0)
            return;
    }
    s += n & -32;
    d += n & -32;
    {
        u32 cnt;
        cnt = n;
        cnt &= 0x1F;
        cnt >>= 1;
        sub_0804DB28(s, d, cnt);
    }
}
