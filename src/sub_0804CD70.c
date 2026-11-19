/* Mem1_AllocInit @ 0x0804CD70 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0804CD70: Mem1_AllocInit (coordinator-verified). */
void sub_0804CA1C(u8 *s);

extern u32 gUnknown_03007FF0[];

extern u32 gUnknown_68736D53[];

extern u32 gUnknown_0804C021[];

void sub_0804CD70(u8 *s, u8 *d, u32 cnt_arg)
{
    u8 cnt = (u8)cnt_arg;
    u32 *p;

    if (cnt == 0)
        return;
    if (cnt > 16)
        cnt = 16;
    p = *(u32 **)gUnknown_03007FF0;
    if (*p != (u32)gUnknown_68736D53)
        return;
    *p += 1;
    sub_0804CA1C(s);
    ((u32 *)s)[11] = (u32)d;
    s[8] = cnt;
    *(u32 *)(s + 4) = 0x80000000;
    if (cnt != 0) {
        do {
            *d = 0;
            cnt--;
            d += 0x50;
        } while (cnt != 0);
    }
    if (p[8] != 0) {
        ((u32 *)s)[14] = p[8];
        ((u32 *)s)[15] = p[9];
        p[8] = 0;
    }
    p[9] = (u32)s;
    p[8] = (u32)gUnknown_0804C021;
    *p = (u32)gUnknown_68736D53;
    ((u32 *)s)[13] = (u32)gUnknown_68736D53;
}
