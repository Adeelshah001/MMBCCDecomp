/* Sub_0800E994 @ 0x0800E994 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800e994_MATCHED.c (registry: mmbcc/src/w36b_0800e994_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct A { u16 f0; u16 f2; u8 pad4[4]; u8 f8; u8 f9; u8 f10; u8 pad11; u16 f12; u16 f14; u16 f16; u16 f18; u8 pad20[4]; u16 f24; u8 pad26[2]; u32 f28; u8 pad32[11]; u8 f43; };

struct F { u8 pad[2]; u8 f2; };

extern void sub_08004E50(int x);

extern void sub_08011DF0(void *a, void *b, int c);

extern void sub_08016FD0(void *a, void *b, int c);

extern void sub_0800EE98(void);

extern void sub_08004DFC(u8 x);

void sub_0800E994(void)
{
    struct A *a = (struct A *)0x02005130;
    int z2 = 0;
    int z1 = 0;
    a->f0 = z1;
    a->f2 = 60;
    a->f24 = z1;
    a->f28 = z1;
    a->f10 = 255;
    a->f8 = 50;
    a->f9 = 50;
    a->f12 = z1;
    a->f14 = z1;
    a->f16 = z1;
    a->f18 = z1;
    a->f43 = z2;
    sub_08004E50(2);
    *(u16 *)0x02004830 = z1;
    {
        void *c = (void *)0x02004fa0;
        sub_08011DF0(c, (void *)0x02005280, 2);
        sub_08016FD0((u8 *)c + 40, (void *)0x020053d0, 36);
    }
    sub_0800EE98();
    sub_08004DFC(((struct F *)0x02004f80)->f2);
}
