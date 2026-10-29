/* Wave 16 worker B: 0x0801AB34 (60 B + pool).
 * If GetField17_U8(*(s+44)) > 5: MaxAssign_17(p,7), DecIfNonZero_18(p),
 * clear *(s+44), set *(s+12)=2, *(s+20)=*(tbl[*(s+9)]+8).
 */
typedef unsigned char u8;
typedef unsigned int u32;


extern u8 GetField17_U8(u8 *s);
extern void DecIfNonZero_18(u8 *s);
extern void MaxAssign_17(u8 *s, u8 v);
u8 GetField17_U8(u8 *s);
void DecIfNonZero_18(u8 *s);
void MaxAssign_17(u8 *s, u8 v);
extern u32 Tbl_082243D8[];

void Sub_1AB34(u8 *s) __attribute__((section(".text.w16b_0801ab34")));
void Sub_1AB34(u8 *s)
{
    u32 *tbase;
    u32 *p;
    if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        tbase = Tbl_082243D8;
        p = tbase + *(u8 *)(s + 9);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)(*p + 8);
    }
}

__asm__(
    ".set Tbl_082243D8, 0x082243D8\n"
);