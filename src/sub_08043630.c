/* F_08043630 @ 0x08043630 (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21c_08043630.c (registry: src/w21c_08043630.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08005A9C(u32 a);

extern u32 sub_0804580C(u8 *s);

 /* actual: u8 (w16b_0804580c.c); u32 decl suppresses the return zero-extend (w15-D idiom); call+use identical */
extern void sub_08042E14(u8 *s);

extern void sub_08043430(u8 *s);

extern void sub_08042EC0(u8 *s);

extern void sub_08045838(u8 *s);

void sub_08043630(u8 *s)
{
    u32 y;
    u8 *base;
    u8 *p;
    u8 *q;
    u8 z;
    sub_08005A9C(8);
    y = sub_0804580C(s);
    base = (u8 *)0x02004830;
    
    p = base + 0x26A;
    z = 0;
    *p = (u8)y;
    q = base + 0x26B;
    *q = z;
    sub_08042E14(s);
    sub_08043430(s);
    sub_08042EC0(s);
    sub_08045838(s);
}
