/* Wave 18-B: 0x08025524 (62 B, 1 caller, 4 bl). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 GetMaskedByte_08025324(u8 *p, u8 idx);
extern void F_0802533c(u8 *p, u8 idx);
extern void Sub_254E0(u8 *s, u8 idx);

__attribute__((section(".text.w18b_08025524")))
u8 sub_08025524(u8 *p, u8 x)
{
    u8 v = GetMaskedByte_08025324(*(u8 **)p, x);
    if (v <= 98) {
        F_0802533c(*(u8 **)p, x);
        Sub_254E0(p, x);
        return GetMaskedByte_08025324(*(u8 **)p, x);
    }
    return 0;
}
