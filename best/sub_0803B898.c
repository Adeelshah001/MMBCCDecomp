/* Sub_0803B898 @ 0x0803B898 (256 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39d_0803b898_MATCHED.c (registry: mmbcc/src/w39d_0803b898_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_080499AC(u8 a);

extern void sub_080073D4(int a, int b, int c, int d, int e);

extern void sub_08006A54(u32 a, int b, int c, int d, int e);

extern void sub_08006DD8(u32 a, int b, int c, int d, int e);

void sub_0803B898(u8 *s_in)
{
    register u8 *s = s_in;
    register int e;
    {
        u8 t = sub_080499AC(0);
        e = 0;
        sub_080073D4(22, t, 2, 1, e);
    }
    {
        u8 t = sub_080499AC(1);
        sub_080073D4(23, t, 2, 3, e);
    }
    {
        u8 t = sub_080499AC(2);
        sub_080073D4(24, t, 2, 5, e);
    }
    {
        u8 t = sub_080499AC(3);
        sub_080073D4(25, t, 2, 7, e);
    }
    {
        u32 a0 = *(u32 *)0x08231960;
        e = 2;
        sub_08006A54(a0, 4, 1, 13, e);
    }
    sub_08006A54(*(u32 *)0x08231968, 4, 3, 13, e);
    sub_08006A54(*(u32 *)0x08231970, 4, 5, 13, e);
    sub_08006A54(*(u32 *)0x08231978, 4, 7, 13, e);
    sub_08006DD8(*(u32 *)(s + 32), 20, 1, 7, e);
    sub_08006A54(*(u32 *)0x08231958, 27, 1, 1, e);
    {
        u8 *dst = (u8 *)0x02004ce0;
        u8 b;
        *(u16 *)(dst + 40) = 20;
        s += 0x4698;
        b = *s;
        *(u16 *)(dst + 42) = (b << 4) + 8;
    }
}
