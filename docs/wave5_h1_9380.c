typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
extern u32 gTbl_0817212C[];
extern u8 gEwram_02004CE0[];
void __attribute__((section(".text.p9380i"))) P9380i(void) {
    u16 i = 0;
    s16 j = i;
    u32 *tbl = gTbl_0817212C;
    while (j <= 5) {
        u8 *p = gEwram_02004CE0 + j * 0x34;
        u8 b = *(p + 0x2c);
        if (b & 1) {
            u16 v = *(u16 *)(p + 0x2c);
            u32 idx = ((u32)v << 22) >> 28;
            ((void (*)(u8 *))tbl[idx])(p);
        }
        i = j + 1;
        j = i;
    }
}
__asm__(
".thumb\n"
".set gTbl_0817212C, 0x0817212C\n"
".set gEwram_02004CE0, 0x02004CE0\n"
".set _call_via_r1, 0x0804DCD0\n"
);
