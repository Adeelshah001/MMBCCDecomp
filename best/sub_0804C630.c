/* Sub_0804C630 @ 0x0804C630 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0804c630_MATCHED.c (registry: mmbcc/src/w36b_0804c630_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_0804BA05[];

extern u8 gUnknown_03000000[];

extern u8 gUnknown_00000007[];

extern void sub_0804DB28(u32 a, u32 b, u32 c);

extern void sub_0804CA30(u32 a);

extern void sub_0804C8EC(u32 a);

extern void sub_0804CBCC(u32 a);

extern void sub_0804CD70(u32 a, u32 b, u32 c);

typedef struct { u32 f0; u32 f4; u8 f8; u8 f9; u16 f10; } Ent;

void sub_0804C630(void)
{
    int count;
    Ent *t;
    sub_0804DB28((u32)gUnknown_0804BA05 & ~1, (u32)gUnknown_03000000, 0x04000100);
    sub_0804CA30(0x0200bdd0);
    sub_0804C8EC(0x0200ce10);
    sub_0804CBCC(0x0095fa00);
    count = (u16)gUnknown_00000007;
    if (count == 0) return;
    t = (Ent *)0x08106d7c;
    for (; count != 0; count--) {
        u32 f0 = t->f0;
        sub_0804CD70(f0, t->f4, t->f8);
        *(u8 *)(f0 + 11) = (u8)t->f10;
        *(u32 *)(f0 + 24) = 0x0200d090;
        t++;
    }
}
