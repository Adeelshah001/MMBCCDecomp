/* Step_08010d84 @ 0x08010D84 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08010d84_MATCHED.c (registry: src/w36a_08010d84_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004E24(u8 v);

extern int sub_08004E0C(u32 v);

extern void sub_080111B4(u32 a);

extern void sub_08011170(u8 a);

extern u16 gUnknown_020031E0;

u8 sub_08010D84(u8 *s)
{
    u8 st = s[0];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[0] = 1;
    sub_08004E24(s[13]);
    goto ret;
state1:
    if ((u8)sub_08004E0C(3) == 0)
        goto ret;
    sub_080111B4(1);
    gUnknown_020031E0 &= 0xedff;
    gUnknown_020031E0 &= 0xdbff;
    sub_08011170(s[2]);
ret:
    return s[4];
}
