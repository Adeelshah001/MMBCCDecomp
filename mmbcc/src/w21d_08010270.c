/* Wave 21-D @0x08010270 (42 B). MATCHED with main agbcc + FIXALIGN1
 * (section-leading .align 2,0 -> .align 1,0 for an exact 42 B section;
 * no literal pool in this function).
 * Wrapper: Setup_0801029C(b, a==0 ? 1 : 3, (s16)c, (s8)d).
 * Entry extends: r0 u8, r1 untouched (u32), r2 u16, r3 u8. The call-site
 * (s16)/(s8) conversions emit the second lsl/asr pairs on r2/r3.
 *
 * Idioms: codegen-shaped callee extern ((u32,u8,s16,s8)->u32; the s16/s8
 * params produce the call-site sign extends, the u32 return suppresses
 * gcc's post-call extend which the ROM lacks). ABI-identical to the u8
 * definition in src/w20d_0801029c.c. The observed caller (0x0800ECF8)
 * sign-extends the result itself (s8 use).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed char s8;

extern u32 Setup_0801029C(u32 a0, u8 a1, s16 a2, s8 a3);

__attribute__((section(".text.w21d_08010270")))
u32 F_08010270(u8 a, u32 b, u16 c, u8 d)
{
    return Setup_0801029C(b, (a == 0) ? 1 : 3, (s16)c, (s8)d);
}
