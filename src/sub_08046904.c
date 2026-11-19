/* Sub_08046904 @ 0x08046904 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08046904_MATCHED.c (registry: mmbcc/src/w36a_08046904_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern void sub_08046CA0(u8 *a, u8 *b, u32 c, u32 d);

extern void sub_08004E44(void);

extern void sub_08004DFC(u32 a);

extern void sub_0800BEE0(u32 a, u32 b);

extern void sub_08002FC4(u32 a);

extern void sub_08046960(u8 *a);

void sub_08046904(u8 *arg0)
{
    u8 *pool = (u8 *)0x0200b7a8;
    u8 *p = pool;
    s16 i;
    u8 *m92;
    i = 0;
    m92 = pool - 92;
    for (; (u16)i <= 15; i++) {
        *p++ = 0;
    }
    sub_08046CA0(pool + 4, m92, 4, 0);
    sub_08004E44();
    sub_08004DFC(2);
    sub_0800BEE0(63, 128);
    arg0[2]++;
    sub_08002FC4(3);
    sub_08046960(arg0);
}
