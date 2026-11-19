/* Sub_0800EED4 @ 0x0800EED4 (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800eed4_MATCHED.c (registry: mmbcc/src/w36b_0800eed4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef u8 (*fn_t)(u8 *p);

extern void sub_0801054C(u8 *p);

extern void sub_08010750(u8 *p);

void sub_0800EED4(void)
{
    u8 *p = (u8 *)0x02005160;
    fn_t fn;
    u8 ret;
    if (p[68] == 0) {
        if ((*(u16 *)0x02002f50 & 1) != 0) {
            ((u8 *)0x02004e40)[20] |= 1;
        }
    } else {
        ((u8 *)0x02004e40)[20] |= 2;
    }
    fn = ((fn_t *)0x08173e8c)[p[0]];
    ret = fn(p);
    {
        u8 *q = (u8 *)0x02005160;
        q[0] = ret;
        sub_0801054C(q);
        sub_08010750(q);
    }
}
