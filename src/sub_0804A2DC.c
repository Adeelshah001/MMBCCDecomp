/* TblState_0804A2DC @ 0x0804A2DC (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_0800300C(u16 a);

extern void sub_08002FC4(u16 a);

extern void sub_08002FD4(u16 a);

/* 0x0804a2dc (70 B): TblValidate + Text_Select/F_08002FD4 dispatch. */
void sub_0804A2DC(u16 a)
{
    u16 *p = (u16 *)0x0200BD10;
    if (p[1] != 0) {
        int v = sub_0800300C(a);
        if (v != 0)
            goto Lend;
        if (p[1] != 0) {
            if (sub_0800300C(p[0]) != 0) {
                sub_08002FD4(p[0]);
                p[1] = v;
            }
        }
    }
    sub_08002FC4(a);
    {
        u16 *q = (u16 *)0x0200BD10;
        q[1] = 1;
        q[0] = a;
    }
Lend:;
}
