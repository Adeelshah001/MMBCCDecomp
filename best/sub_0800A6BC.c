/* Ewram4830_StateReset_0800A6BC @ 0x0800A6BC (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24c_0800a6bc.c (registry: src/w24c_0800a6bc.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800B4E4(void);

extern void sub_0800B4C8(void);

u32 sub_0800A6BC(u8 *p)
{
    u8 *r5 = (u8 *)0x02004830;
    u8 v = p[1];
    u8 b, r;
    u32 t;
    register s32 sh;
    s32 shc;
    s8 q;
    u8 d;
    s8 sb2, ds;
    u32 base;

    if (v == 0) {
        p[1] = 1;
        sub_0800B4E4();
        sub_0800B4C8();
        t = p[19];
        t &= -3;
        p[19] = (u8)t;
    } else if (v != 1) {
        return 1;
    }

    b = *(r5 + 0x264);
    if (p[19] & 1) {
        sh = (s32)b << 24;
        shc = sh;
        if ((s8)(shc >> 24) > 1) {
            q = shc >> 26;
            d = q ? (u8)q : 1;
            sb2 = (s8)(sh >> 24);
            ds = (s8)d;
            r = (u8)(sb2 - ds);
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }

    if ((r << 24) > 0)
        goto store;
    r = 0;
    p[0] = 0;
    p[3] = 0;
    p[2] = 0;
    p[1] = 0;
    base = 0x02004830;
    
    *(u8 *)(base + 0x265) = 0;
store:
    *(r5 + 0x264) = r;
    return 1;
}
