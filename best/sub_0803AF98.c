/* Task_3AF98 @ 0x0803AF98 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l3_old.c (registry: src/wave6_l3_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0803AF98: Task_3AF98 (coordinator-verified). */
void sub_080267B4(u8 *a, u32 b);

void sub_08004F18(void);

void sub_08004F80(void);

extern u8 gUnknown_0000469C[];

extern u8 gUnknown_020070F0[];

extern u8 gUnknown_00004698[];

extern u8 gUnknown_020070F0[];

extern u8 gUnknown_00004698[];

void sub_0803AF98(u8 *s)
{
    register u32 off;
    register u8 *p;
    u8 v;
    off = (u32)gUnknown_0000469C;
    p = s + off;
    v = *p;
    if (v == 8) {
        register u8 *q;
        register u32 o;
        sub_080267B4(gUnknown_020070F0, 8);
        o = (u32)gUnknown_00004698;
        q = s + o;
        *q = 0;
    } else if (v == 9) {
        register u8 *q;
        register u32 o;
        sub_080267B4(gUnknown_020070F0, 8);
        o = (u32)gUnknown_00004698;
        q = s + o;
        *q = 6;
    } else {
        u8 z = 0;
        s[1] = 1;
        s[2] = z;
        s[3] = z;
    }
    sub_08004F18();
    sub_08004F80();
}
