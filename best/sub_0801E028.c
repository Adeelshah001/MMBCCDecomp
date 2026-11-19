/* Sub_0801E028 @ 0x0801E028 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801e028_MATCHED.c (registry: mmbcc/src/w37c_0801e028_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D6E0(u8 *s, u16 b, u8 c);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0801E0D0(u8 *s);

void sub_0801E028(u8 *s)
{
    register u8 *tbl;
    register u8 *tbase;
    register u8 *pbase;
    register u8 *sbase;
    u32 *tp;
    u16 *taddr;
    u8 s17;
    u8 *q108;
    u8 *q69;
    int v;
    int w;
    u8 t10;
    int tmp;
    u8 v18;
    u8 z;
    tbl = (u8 *)(s[16] * 12);
    tbase = (u8 *)0x020051c8;
    
    tbl = (u8 *)((u32)tbl + (u32)tbase);
    pbase = (u8 *)0x082243d8;
    
    tp = (u32 *)(s[9] * 4 + (u32)pbase);
    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
    v18 = tbl[2];
    z = 0;
    s[18] = v18;
    s[19] = z;
    q108 = s + 80;
    
    *(u32 *)(q108 + 28) = 0;
    t10 = 2;
    t10 |= s[10];
    t10 |= 1;
    s[10] = t10;
    sbase = (u8 *)0x08226a70;
    
    taddr = (u16 *)(s[16] * 2 + (u32)sbase);
    s17 = s[17];
    sub_0800D6E0(s, s17 | *taddr, 0);
    sub_0800D9EC(s, 6);
    v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
    w = v;
    
    if (w > 3)
        v = 3;
    q69 = s + 69;
    {
        int sh = v << 2;
        tmp = (s[69] & -13) | sh;
    }
    *q69 = tmp;
    sub_0801E0D0(s);
}
