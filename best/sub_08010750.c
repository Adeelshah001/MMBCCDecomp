/* Sub_08010750 @ 0x08010750 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08010750_MATCHED.c (registry: mmbcc/src/w36b_08010750_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080062B4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);

extern void sub_080107CC(u8 *s);

extern void sub_08010844(u8 *s, u32 x);

void sub_08010750(u8 *arg0)
{
    u8 b = arg0[68];
    int boolean = (b != 0);
    u32 *p = (u32 *)0x02003670;
    int bit = (*p >> (3 - boolean)) & 1;
    u32 stack0 = 525;
    int stack1 = boolean ? 3 : 5;
    u32 *table = (u32 *)0x08173e2c;
    u32 stack2 = table[bit];
    u8 *s;
    sub_080062B4(13, 19, 4, 1, stack0, stack1, stack2);
    s = (u8 *)0x02005168;
    sub_080107CC(s);
    sub_08010844(s, 0);
    sub_080107CC(s + 20);
    sub_08010844(s + 20, 1);
}
