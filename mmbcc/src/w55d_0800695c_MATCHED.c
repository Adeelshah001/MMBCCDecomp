/* Wave 55-D v26 MATCHED-CANDIDATE: 0x0800695c Tilemap_DecodeBlit, 248 B (246 code + 2 pad). Keys: u16 s[4] (8B local -> frame 32, a3 at #16); guarded final call (ROM beq at 0x6a22); s16 c temp across the loop call (c=(s16)a2; call; a2=(u16)(c+1)) leaves a2 dead at the call so it stays in r2 with save-around-call via r4 -- breaks the coord-home allocator rotation (v20's wall, 57 diffs). Trailing .balign 4, 0 pad. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
extern u16 Tbl_080733A6[];
extern u16 Tbl_080733B2[];
extern void Sub_08006AD8(void *dst, u16 *s, s16 x, s16 y, s8 m, u8 f);

__attribute__((section(".text.w55d_0800695c")))
void sub_0800695c(void *dst, u16 *src, u16 a2, u16 a3, s8 a4, u8 a5) {
    s16 h;
    s16 row;
    s16 j;
    u16 s[4];
    if (a4 != 0)
        h = (u16)a4;
    else
        h = 32;
    s[1] = 0x8000;
    for (row = 0; row < h; row++) {
        s[0] = *src++;
        for (j = 0; j <= 4; j++) {
            if (s[0] == Tbl_080733A6[j]) {
                s[0] = Tbl_080733B2[j];
                break;
            }
        }
        {
            s16 c = (s16)a2;
            Sub_08006AD8(dst, s, c, (s16)a3, 1, a5);
            a2 = (u16)(c + 1);
        }
    }
    if (a4 != 0)
        Sub_08006AD8(dst, src, (s16)a2, (s16)a3, (s8)(a4 - row), a5);
}

__asm__(
    ".set Tbl_080733A6, 0x080733a6\n"
    ".set Tbl_080733B2, 0x080733b2\n"
    ".set Sub_08006AD8, 0x08006ad8\n"
);

/* Trailing pad: code ends 2 mod 4; ROM has 00 00 here. */
__asm__(".balign 4, 0");
