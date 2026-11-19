/* Lookup_0800cb70 @ 0x0800CB70 (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0800cb70_MATCHED.c (registry: src/w36a_0800cb70_MATCHED.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

extern void sub_08005268(void *a, void *b);

extern u32 gUnknown_020038AC[];

extern u8 gUnknown_081731E0[];

void sub_0800CB70(u8 *s, s8 idx)
{
    u32 p2;
    s8 b;
    s32 b4;
    u8 *t2;
    u32 x;
    u32 y;
    u8 *p;
    if (idx < 0)
        return;
    {
        register u8 *e;
        {
            register u8 *t1 = gUnknown_081731E0;
            u32 off = 20;
            e = (*(s16 *)(s + off)) * 8 + t1;
        }
        p2 = gUnknown_020038AC[1] + 0xfa000a20;
        b = *e;
        b4 = b * 4;
        t2 = (u8 *)0x087493b0;
        x = *(u32 *)(t2 + b4);
        y = x + (u32)t2;
        p = (u8 *)(b4 + y);
        p += idx * 20;
        sub_08005268(p, (void *)p2);
    }
}
