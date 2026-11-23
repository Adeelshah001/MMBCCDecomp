/* Sub_08023F28 @ 0x08023F28 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39c_08023f28_MATCHED.c (registry: mmbcc/src/w39c_08023f28_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_0200BD20[];

extern void InitChipIndexTables(u8 *a, u8 *b);

extern void sub_0802616C(u8 *a, u8 *b);

extern void sub_0802617C(u8 *a, u8 *b);

void sub_08023F28(u8 *s)
{
    u8 *gEwram_0200BD20 = (u8 *)0x02007090;
    s8 si;
    u8 *q62;
    *(u16 *)(gUnknown_0200BD20 + 88) = 1;
    *(u32 *)(gUnknown_0200BD20 + 52) = (u32)s;
    InitChipIndexTables(gUnknown_0200BD20, s + 436);
    sub_0802616C(gUnknown_0200BD20 + 20, *(u8 **)(gUnknown_0200BD20 + 52));
    sub_0802617C(gUnknown_0200BD20 + 24, *(u8 **)(gUnknown_0200BD20 + 52) + 1184);
    s = s + 5028;
    *(u32 *)(gUnknown_0200BD20 + 56) = (u32)s;
    {
        register u16 v1;
        register u16 w1;
        v1 = 128;
        
        v1 <<= 8;
        w1 = v1;
        *(u16 *)(s + 0) = w1;
        *(u16 *)(s + 2) = w1;
        *(u16 *)(s + 4) = w1;
        *(u16 *)(s + 6) = w1;
        *(u16 *)(s + 8) = w1;
    }
    gUnknown_0200BD20[60] = 50;
    gUnknown_0200BD20[61] = 200;
    si = 0;
    q62 = gUnknown_0200BD20 + 62;
    do {
        q62[si] = 0;
        si++;
    } while (si <= 9);
    {
        register u8 *q;
        register u16 vv;
        q = gUnknown_0200BD20 + 72;
        *q = 0;
        q++;
        *q = 0;
        q++;
        vv = 128;
        
        vv <<= 8;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        
        *(u16 *)q = vv;
    }
}
