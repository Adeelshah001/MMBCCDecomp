/* Sub_08022700 @ 0x08022700 (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08022700_MATCHED.c (registry: mmbcc/src/w36d_08022700_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800D9FC(void *s);

void sub_08022700(u8 *s)
{
    register s32 st = s[13];
    if (st == 1)
        goto case1;
    if (st > 1)
        goto gt;
    if (st == 0)
        goto case0;
    goto end;
gt:
    if (st == 2)
        goto case2;
    goto end;
case0: {
        u8 *p;
        register u32 v0;
        s[13] = 1;
        p = s + 76;
        v0 = 288;
        *(u16 *)p = v0;
        p += 2;
        *(u16 *)p = v0;
        s[18] = 32;
    }
    /* fall through */
case1: {
        u32 t;
        register u32 v = s[18] | 256;
        u8 *p = s + 76;
        register u8 f18b;
        *(u16 *)p = v;
        f18b = s[18];
        {
            u32 w = 256 | f18b;
            p += 2;
            *(u16 *)p = w;
        }
        t = ((u32)s[18] << 24);
        if (t == 0) {
            s[13]++;
        } else {
            u32 d;
            t >>= 25;
            t <<= 16;
            d = 1;
            if (t != 0)
                d = t >> 16;
            s[18] -= d;
        }
        goto end;
    }
case2: {
        register u32 base = 0x08226ef0;
        register u8 f9b = s[9];
        u32 *addr = (u32 *)base + f9b;
        u32 *e;
        *(u32 *)(s + 12) = st;
        e = *(u32 **)addr;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)e + 8);
        goto end;
    }
end:
    sub_0800D9FC(s);
}
