/* StateMachine_08038EFC @ 0x08038EFC (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_08038efc.c (registry: src/w17d_08038efc.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004DFC(u8 a);

extern void sub_08004F18(void);

extern int sub_08004E0C(u8 x);

extern void sub_08004F80(void);

void sub_08038EFC(u8 *p)
{
    u8 t = p[2];
    switch (t) {
    case 0:
        sub_08004DFC(1);
        p[2]++;
        /* fallthrough */
    case 1: {
        u32 r;
        sub_08004F18();
        r = (u32)(s8)sub_08004E0C(0);
        if (r == 0) {
            p[1] = 2;
            p[2] = (u8)r;
            p[3] = (u8)r;
        }
        sub_08004F80();
        break;
    }
    default:
        break;
    }
}
