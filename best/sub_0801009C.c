/* Setup_0801009C @ 0x0801009C (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19c_0801009c.c (registry: src/w19c_0801009c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08010508(u32 v);

extern void sub_0801052C(void);

u8 sub_0801009C(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    u8 z = *(u8 *)0x02005160;
    u32 t;
    if (z != 0)
        return 0;
    sub_08010508(2);
    sub_0801052C();
    {
        register u8 *p = (u8 *)0x02004ca0;
        register u32 one;
        p[29] = a | b | c;
        one = 1;
        
        t = p[31] | one;
        p[30] = z;
        
        p[31] = t | one;
        p += 32;
        p[29] = d | e | f;
        t = p[31] | one;
        p[30] = z;
        
        p[31] = t | one;
    }
    return 1;
}
