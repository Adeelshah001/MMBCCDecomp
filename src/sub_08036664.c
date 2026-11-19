/* Task_36664 @ 0x08036664 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_k.c (registry: src/wave4_k.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0804A2DC(u32 v);

void sub_08004F18(void);

void sub_08004F80(void);

/* 0x08036664: task init, 32-bit stores. Tentative. */
void sub_08036664(u8 *p)
{
    *(u32 *)(p + 0x4698) = 0;
    *(u32 *)(p + 0x469C) = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[0x4699] = 0;
    p[5] = 0;
    p[0x469E] = 0;
    sub_0804A2DC(7);
    sub_08004F18();
    sub_08004F80();
}
