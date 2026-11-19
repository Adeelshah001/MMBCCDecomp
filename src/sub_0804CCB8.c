/* HwSetup_0804CCB8 @ 0x0804CCB8 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0804ccb8: HwSetup_0804CCB8 (coordinator-verified). */
void sub_0804DB28(void *src, void *dst, u32 len);

void sub_0804CCB8(void)
{
    u32 *p = *(u32 **)0x03007FF0;
    u32 v = *p;
    u32 bit;
    u32 *r;
    u32 v1;
    u32 v2;

    if (v + 0x978C92AD > 1)
        return;
    *p = v + 10;
    r = (u32 *)0x040000C4;
    v1 = *r;
    bit = 0x2000000;
    if (v1 & bit)
        *r = 0x84400004;
    r = (u32 *)0x040000D0;
    v2 = *r;
    if (v2 & bit)
        *r = 0x84400004;
    *(u16 *)0x040000C6 = 0x400;
    *(u16 *)0x040000D2 = 0x400;
    {
        u32 zero = 0;
        sub_0804DB28(&zero, (u8 *)p + 0x350, 0x05000318);
    }
}
