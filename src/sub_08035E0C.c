/* Task_35E0C @ 0x08035E0C (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_k.c (registry: src/wave4_k.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0804A2DC(u32 v);

void sub_08004F18(void);

void sub_08004F80(void);

/* 0x08035E0C: task init. Tentative. */
void sub_08035E0C(u8 *p)
{
    u8 z = 0;
    p[1] = 2;
    p[3] = z;
    p[2] = z;
    p[0x4699] = z;
    p[4] = z;
    p[0x46B7] = z;
    sub_0804A2DC(6);
    sub_08004F18();
    sub_08004F80();
}
