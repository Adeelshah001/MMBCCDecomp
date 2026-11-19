/* Task_Clock_08026740 @ 0x08026740 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w25b_08026740.c (registry: mmbcc/src/w25b_08026740.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef struct {
    u8 pad0[13];
    u8 mode;
    u8 pad1[3];
    u8 f17;
    u8 pad2[17];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void sub_08000EF8(void);

extern void sub_08000DC0(u32 slot);

void sub_08026740(void)
{
    u8 *S;
    u16 max;
    sub_08000EF8();
    S = (u8 *)0x020070F0;
    max = 0x633B;
    for (;;) {
        if (S[0] != 11) {
            S[16]++;
            if ((u8)S[16] > 59) {
                S[16] = 0;
                if (S[17] <= 58) {
                    S[17]++;
                } else {
                    register u32 hrs = *(u16 *)(S + 18);
                    if (hrs != max) {
                        S[17] = 0;
                        if (S[18] <= 58) {
                            S[18]++;
                        } else {
                            if (S[19] != 99) {
                                S[19]++;
                                S[18] = 0;
                            }
                        }
                    }
                }
            }
        }
        {
            register u32 *tbl = (u32 *)0x0822D8EC;
            register u32 idx = S[0];
            register u32 idx4 = idx << 2;
            register u32 *fnaddr;
            
            fnaddr = (u32 *)(idx4 + (u32)tbl);
            ((void (*)(u8 *))*fnaddr)(S);
        }
        sub_08000DC0(1);
    }
}
