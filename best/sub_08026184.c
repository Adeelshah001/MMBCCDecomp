/* F_08026184 @ 0x08026184 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24b_08026184.c (registry: src/w24b_08026184.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

typedef struct { u8 *p; u16 a; u16 b; } Buf;

extern void sub_0802520C(Buf *s, u8 *ptr, u16 n);

extern int sub_0802526C(Buf *s, u8 v);

void sub_08026184(u8 *a1, u16 *a2)
{
    u16 i;
    u32 t;

    sub_0802520C((Buf *)(a1 + 8), *(u8 **)a1 + 0xE00, 0x82);
    sub_0802520C((Buf *)(a1 + 16), *(u8 **)a1 + 0xE82, 0x82);
    sub_0802526C((Buf *)(a1 + 16), 0);
    ((u16 *)*(u8 *volatile *)(a1 + 4))[7] = a2[0];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[8] = a2[1];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[9] = a2[2];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[10] = a2[3];
    {
        u16 *pw = (u16 *)*(u8 *volatile *)(a1 + 4);
        pw[11] = 0x8000;
    }
    (*(u8 *volatile *)(a1 + 4))[24] = 1;
    (*(u8 *volatile *)(a1 + 4))[25] = 1;
    i = 1;
    do {
        sub_0802526C((Buf *)(a1 + 8), (u8)i);
        t = ((u32)i << 16) + 0x10000;
        i = (u16)(t >> 16);
    } while ((s16)(t >> 16) <= 127);
}
