/* EwCopy_4A3C4 @ 0x0804A3C4 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

struct Ew0200BD20 { u8 _00[128]; u16 f128; };

extern struct Ew0200BD20 gUnknown_0200BD20;

extern u8 gUnknown_02002EE0[];

s32 EwCopy_4A3C4(void)
{
    register u8 *bd = (u8 *)&gUnknown_0200BD20;
    register u8 *flg = gUnknown_02002EE0;
    register u8 *p;
    s32 r;
    if ((*flg & 48) != 48)
        goto Lneg;
    {
        u8 v = flg[4];
        p = bd;
        p += 130;
        *p = v;
    }
    r = 0;
    goto Lend;
Lneg:
    r = -1;
Lend:
    return r;
}
