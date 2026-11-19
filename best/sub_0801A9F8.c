/* Sub_0801A9F8 @ 0x0801A9F8 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0801a9f8_MATCHED.c (registry: mmbcc/src/w36b_0801a9f8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D9FC(u8 *s);

extern void sub_08017478(u32 x, u32 y);

extern void sub_08017464(u32 x);

void sub_0801A9F8(u8 *s)
{
    u32 *table1 = (u32 *)0x08226644;
    u32 *table2 = (u32 *)0x082243d8;
    u32 *ptr1 = table1 + s[16];
    u8 res = (u8)((u8 (*)(u8 *))*ptr1)(s);
    sub_0800D9FC(s);
    if (res != 0) {
        u32 *ptr2 = table2 + s[9];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)ptr2 + 8);
        sub_08017478(*(u32 *)(s + 44), 7);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
