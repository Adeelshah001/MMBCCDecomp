/* ChipList_Setup_0800E224 @ 0x0800E224 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24c_0800e224.c (registry: src/w24c_0800e224.c).
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

extern u32 *sub_08011E20(u8 a, u8 b, u8 c);

extern void sub_08016E0C(u8 *s, u32 v);

extern void sub_0800D568(u8 *s);

extern u32 sub_08016F88(u8 *s);

extern int sub_08004E0C(u8 x);

extern void sub_0800E1F0(u8 v);

void sub_0800E224(void)
{
    u8 *S = (u8 *)0x02005130;
    u32 *n1, *n2;
    u32 *p;
    u8 v;

    *(u16 *)(S + 24) = 1;
    if (S[21] == 0) {
        S[21]++;
        n1 = sub_08011E20(1, 0, 1);
        n2 = sub_08011E20(1, 1, 1);
        sub_08016E0C((u8 *)n1, S[4]);
        sub_08016E0C((u8 *)n2, S[5]);
    }
    sub_0800D568(*(u8 **)0x02005270);
    sub_0800D568(*(u8 **)0x020053C0);
    p = (u32 *)0x02005020;
    n1 = (u32 *)p[0];
    n2 = (u32 *)p[1];
    if ((u16)sub_08016F88((u8 *)n1) != 0) {
        u8 v1 = 1;
        v1 |= S[22];
        S[22] = v1;
    }
    if ((u16)sub_08016F88((u8 *)n2) != 0) {
        u8 v2 = 2;
        v2 |= S[22];
        S[22] = v2;
    }
    if (S[22] == 3) {
        u8 z = 0;
        v = sub_08004E0C(0);
        if ((u8)v != 0) {
            *(u16 *)(S + 24) = z;
            sub_0800E1F0(z);
        }
    }
}
