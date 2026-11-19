/* StateMachine_08048380 @ 0x08048380 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_08048380.c (registry: src/w17d_08048380.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004E24(u8 x);

extern void sub_08004F18(void);

extern int sub_08004E0C(u8 x);

extern void sub_08004F80(void);

u32 sub_08048380(u8 *p)
{
    u8 t = p[3];
    switch (t) {
    case 0:
        sub_08004E24(0);
        p[3]++;
        /* fallthrough */
    case 1: {
        u32 m;
        u16 *p1;
        sub_08004F18();
        if ((sub_08004E0C(3) << 24) != 0) {
            p1 = (u16 *)0x020031e0;
            m = 0xedff;
            m &= *p1;
            {
                u8 z = 0;
                m &= 0xdbff;
                *p1 = (u16)m;
                p[2] = 4;
                p[3] = z;
            }
        }
        sub_08004F80();
        break;
    }
    default:
        break;
    }
    return 0;
}
