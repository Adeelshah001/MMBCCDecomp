/* Sub_08003058 @ 0x08003058 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08003058_MATCHED.c (registry: staging/wave34_C/w34c_08003058_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern int sub_0800300C(u16);

extern void sub_0804C780(u16);

void sub_08003058(u32 a)
{
    u32 t = a << 16;
    u16 b;
    if ((s32)t < 0)
        return;
    b = t >> 16;
    if (sub_0800300C(b))
        sub_0804C780(b);
}
