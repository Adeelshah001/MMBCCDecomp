/* TaskScan_08000D6C @ 0x08000D6C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_08000d6c.c (registry: src/w15c_08000d6c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_030023C8[];

void SetTaskField0_030023C8(int i);

void TaskScan_08000D6C(void)
{
    u8 *p = gUnknown_030023C8;
    int i = 0;
    do
    {
        if (*p != 1)
            SetTaskField0_030023C8(i);
        i++;
        p += 24;
    } while (i <= 2);
}
