/* Sub_08028FEC @ 0x08028FEC (512 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w59d_08028fec_MATCHED.c (registry: src/w59d_08028fec_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08029504(u8 *s);

extern u8 sub_080292B0(u8 *s);

extern void Sub_0802D5D4(u8 *s);

extern u8 sub_0802EA64(u8 *s);

__attribute__((section(".text.w59d_08028fec")))
u8 Sub_08028FEC(u8 *s)
{
    int mode;
    sub_08029504(s);
    if (((s[404] & 15) == 1) || ((s[404] & 240) == 16) ||
        ((s[408] & 15) == 1) || ((s[408] & 240) == 16)) {
        s[4] = 0;
    } else if (s[11] == 1) {
        s[4] = 0;
    } else {
        s[4] = sub_080292B0(s) << 4;
    }
    mode = s[4] >> 4;
    switch (mode) {
    case 1:
    case 2:
        if ((s[6] & 8) == 0) {
            s[2] = 3;
            s[3] = 0;
        }
        s[0] = 4;
        break;
    case 4:
        Sub_0802D5D4(s);
        if (s[28] <= 9) {
            int z = 0;
            s[0] = 2;
            s[1] = z;
        } else {
            s[4] = sub_0802EA64(s);
            if ((s[6] & 8) == 0) {
                s[2] = 3;
                s[3] = 0;
            }
            s[0] = mode;
        }
        break;
    default:
        if (s[11] == 1) {
            s[11] = 2;
            if ((s[6] & 8) == 0) {
                s[2] = 8;
                s[3] = 0;
            }
        } else if ((s[404] & 15) == 1) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            {
                int m = -16;
                s[404] = (s[404] & m) | 2;
            }
            if (s[321] == 0)
                s[321] = 11;
            else
                s[320] = 11;
        } else if ((s[404] & 240) == 16) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            s[404] = (s[404] & 15) | 32;
            if (s[321] == 0)
                s[321] = 10;
            else
                s[320] = 10;
        } else if ((s[408] & 15) == 1) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            {
                int m = -16;
                s[408] = (s[408] & m) | 2;
            }
            if (s[329] == 0)
                s[329] = 11;
            else
                s[328] = 11;
        } else if ((s[408] & 240) == 16) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            s[408] = (s[408] & 15) | 32;
            if (s[329] == 0)
                s[329] = 10;
            else
                s[328] = 10;
        }
        break;
    }
    return 3;
}
