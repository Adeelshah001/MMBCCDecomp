typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
extern u8 gTbl_0817313C[];
extern u32 gTbl_081731A0[];
void __attribute__((section(".text.pbb78d"))) PBB78d(u8 *s) {
    s16 v = *(s16 *)(s + 0x14);
    u32 *tbl;
    s8 idx;
    if (v != -1) {
        tbl = gTbl_081731A0;
        idx = gTbl_0817313C[v];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}
__asm__(
".thumb\n"
".set gTbl_0817313C, 0x0817313C\n"
".set gTbl_081731A0, 0x081731A0\n"
".set _call_via_r1, 0x0804DCD0\n"
);
