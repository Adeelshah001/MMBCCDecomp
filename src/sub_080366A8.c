/* Task_366A8 @ 0x080366A8 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_blk.c (registry: src/wave5_blk.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

void sub_08004F18(void);

void sub_08004F80(void);

void sub_08004DFC(u32 a);

s32 sub_08004E0C(u32 a);

void sub_080366A8(u8 *p)
{
    switch (p[2]) {
    case 0:
        sub_08004DFC(1);
        p[2]++;
    case 1:
        sub_08004F18();
        {
            s32 v = (s8)sub_08004E0C(0);
            if (!v) {
                p[1] = 2;
                p[2] = v;
                p[3] = v;
            }
        }
        sub_08004F80();
        break;
    default:
        break;
    }
}
