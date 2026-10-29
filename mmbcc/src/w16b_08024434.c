/* Wave 16 worker B: 0x08024434 (124 B).
 * Switch-like dispatcher on (a >> 12): 1->GetU32_38, 2->GetPtr14_265D0,
 * 3->ROM table double-indirect, 4->EWRAM u32, else 0.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;


extern u32 GetU32_38(u8 *s);
extern u8 *GetPtr14_265D0(void *ctx, s16 idx);
u32 GetU32_38(u8 *s);
u8 *GetPtr14_265D0(void *ctx, s16 idx);
extern u8 EwrBase_2007090[];
extern u8 EwrBase_20070A8[];
extern u8 EwrBase_20070DA[];
extern u16 RomTbl_82298F0[];
extern u32 RomTbl_822B9C0[];

u32 Dispatch_24434(u16 a) __attribute__((section(".text.w16b_08024434")));
u32 Dispatch_24434(u16 a)
{
    register u16 v __asm__("r4") = a;
    int x;
    if (v == 0)
        return 0;
    x = v >> 12;
    switch (x) {
    case 1:
        return GetU32_38(EwrBase_2007090);
    case 2:
        return (u32)GetPtr14_265D0(EwrBase_20070A8, (s16)(0xFFF & v));
    case 3: {
        u8 *b1 = (u8 *)RomTbl_82298F0;
        u8 *b2 = (u8 *)RomTbl_822B9C0;
        u32 i = 0xFFF & v;
        u8 *p = b1 + i * 20;
        u16 t = *(u16 *)(p + 16);
        return *(u32 *)(b2 + (t << 2));
    }
    case 4:
        return (u32)EwrBase_20070DA;
    default:
        return 0;
    }
}

__asm__(
    ".set EwrBase_2007090, 0x02007090\n"
    ".set EwrBase_20070A8, 0x020070A8\n"
    ".set EwrBase_20070DA, 0x020070DA\n"
    ".set RomTbl_82298F0, 0x082298F0\n"
    ".set RomTbl_822B9C0, 0x0822B9C0\n"
);