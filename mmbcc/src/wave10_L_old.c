/* Wave 10 batch L: leaves-up bulk batch (old_agbcc).
 * 7 functions matched byte-identical. See docs/match_notes_wave10_L.md.
 * Uses canonical absolute symbols (gTbl_0817313C, gEwram020070F0,
 * g_082240b8) already defined in wave3_d.c / wave5_h1.c / wave7_g2_old.c;
 * no new .set directives needed.
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern s8 gTbl_0817313C[];
extern u8 gEwram020070F0[];
extern unsigned char g_082240b8_L[];

__asm__(
    ".globl g_082240b8_L\n"
    ".set g_082240b8_L, 0x082240b8\n"
);

/* 0x0800C248 (28B): s8 table lookup; -1 if idx==-1 or idx<=59. */
__attribute__((section(".text.w10l_0800c248")))
int S8TableLookup_0C248(s16 idx)
{
    int x = idx;
    int r = -1;
    u8 b;
    if (x == -1) goto done;
    if (x <= 59) goto done;
    b = ((u8 *)gTbl_0817313C)[x];
    r = (s8)b;
done:
    return r;
}

/* 0x0802D460 (40B): pair-bonus check; 6 if (y,x) in {(4,4),(3,1),(2,4)}. */
__attribute__((section(".text.w10l_0802d460")))
u8 PairBonus_2D460(u8 x, u8 y)
{
    u8 r = 0;
    if (y == 4 && x == 4)
        r = 6;
    else if (y == 3 && x == 1)
        r = 6;
    else if (y == 2 && x == 4)
        r = 6;
    return r;
}

/* 0x08026720 (32B): clamp/offset; >84->239, >48->+150, else +200 (u8). */
__attribute__((section(".text.w10l_08026720")))
u8 Clamp_26720(u8 v)
{
    u8 w = v;
    u8 r;
    if (v > 84)
        r = 239;
    else if (v > 48)
        r = (u8)(v + 150);
    else
        r = (u8)(w + 200);
    return r;
}

/* 0x08026D94 (26B): EWRAM byte lookup; -1 if [1]==0 else (s8)[2]. */
__attribute__((section(".text.w10l_08026d94")))
int EwramLookup_26D94(void)
{
    u8 *p = gEwram020070F0;
    if (p[1] == 0)
        return -1;
    return (s8)p[2];
}

/* 0x08016FAC (34B): ROM table byte; 0 if null entry. */
typedef struct { u8 *p; u8 _pad[4]; } TblEntry_16FAC;
__attribute__((section(".text.w10l_08016fac")))
u8 TableByte_16FAC(u8 idx, u8 off)
{
    u8 *tbl = g_082240b8_L;
    u8 *p = ((TblEntry_16FAC *)tbl)[idx].p;
    if (p != 0)
        return p[off];
    return 0;
}

/* 0x08049934 (54B): rank from EWRAM u16; 254->2, 255->3, 253->1. */
__attribute__((section(".text.w10l_08049934")))
u8 Rank_49934(u8 idx)
{
    u8 *pool = gEwram020070F0;
    u8 r = 0;
    u8 *base = pool + idx * 12;
    int v = *(u16 *)(base + 50);
    if (v == 254) goto yes2;
    if (v > 254) goto big;
    if (v == 253) goto yes1;
    goto no;
big:
    if (v != 255) goto no;
    r = 3;
    goto no;
yes2:
    r = 2;
    goto no;
yes1:
    r = 1;
no:
    return r;
}

/* 0x08023CE4 (44B): XOR-fold 14 bytes with ((i*2)&7) key stream. */
__attribute__((section(".text.w10l_08023ce4")))
void Xor_23CE4(u8 *p0, u8 *p1)
{
    u8 *a = p1;
    u8 *b = p0;
    u8 i = 0;
    do {
        u8 *dst = a + i;
        u8 *src = b + ((i * 2) & 7);
        *dst ^= *src;
        i++;
    } while (i <= 13);
}
