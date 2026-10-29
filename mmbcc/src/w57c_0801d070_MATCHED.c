/* W57-C v7 (v6 + trailing 00 00 pad, w36b convention): 0x0801D070, TRUE extent 304 B (code thru bx @0x1d19c + 2 B pad
 * @0x1d19e; next fn @0x1d1a0). Decimal-digit node builder: count clamped to
 * 9999, split into digits via ROM place table {1000,100,10,1} (@0x08226a44),
 * leading zeros dropped (min 1 digit), header s16 at [*0x020053C0 + 10] must
 * be >= digit count, else NULL. One node per digit via Node_PopAndInit
 * (1,1,0,12); node bytes +16=1, +17=(kind<<4)|i, +18=n, +19=digit;
 * +40=prev (parent for i=0), +44=next (0 on last); +88=info[0]+off,
 * +92=info[1], off starts -640*n and grows by 1280 per node.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef struct { u32 x, y; } Pair;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
extern u32 g_020053C0;
__asm__(".set g_020053C0, 0x020053C0");
extern u16 PlaceTbl_08226A44[];
__asm__(".set PlaceTbl_08226A44, 0x08226a44");
__asm__(".set __udivsi3, 0x0804de70");
__asm__(".set __umodsi3, 0x0804dee8");

__attribute__((section(".text.w57c_0801d070")))
u32 *Sub_0801D070(u8 kind, u32 *parent, u32 *info, u16 count)
{
    u8 buf[4];
    u32 *node = 0;
    short i;
    u8 n;
    int off;
    u32 *prev;

    if (count > 9999)
        count = 9999;
    for (i = 0; i <= 3; i++) {
        buf[i] = count / PlaceTbl_08226A44[i];
        count %= PlaceTbl_08226A44[i];
    }
    n = 4;
    i = 0;
    while (buf[i] == 0) {
        n--;
        i++;
        if (i > 2)
            break;
    }
    if (*(s16 *)((u8 *)g_020053C0 + 10) < n)
        return 0;
    off = (-5 * n) << 7;
    prev = parent;
    for (i = 0; i < n; i++) {
        node = Node_PopAndInit(1, 1, 0, 12);
        ((u8 *)node)[16] = 1;
        ((u8 *)node)[17] = (kind << 4) | i;
        ((u8 *)node)[18] = n;
        ((u8 *)node)[19] = buf[4 - n + i];
        ((u32 *)node)[10] = (u32)prev;
        if (i != 0)
            ((u32 *)prev)[11] = (u32)node;
        *(Pair *)((u8 *)node + 88) = *(Pair *)info;
        ((u32 *)node)[22] += off;
        off += 1280;
        prev = node;
    }
    if (node != 0)
        ((u32 *)node)[11] = 0;
    return node;
}

/* Trailing 00 00 pad to the next-function boundary (0x0801d1a0), as in ROM.
   GAS would otherwise emit c0 46 here. */
__asm__(".section .text.w57c_0801d070\n\t.byte 0, 0\n\t.previous");
