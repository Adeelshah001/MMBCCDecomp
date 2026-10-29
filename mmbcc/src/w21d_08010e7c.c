/* Wave 21-D @0x08010E7C (36 B). MATCHED with main agbcc.
 * Wrapper: zero-extends arg0 (u8), sign-extends args1-3 (s8), passes 0 as
 * 5th arg to Setup_08010EC4. Twin of 0x08010EA0 (which passes 1).
 *
 * Idioms: the callee extern is declared (u8,s8,s8,s8,u8)->u32 so the s8
 * args pass through with their entry sign-extension (a u8-param prototype
 * would make gcc emit a second lsl/lsr pair) and so the call result is
 * word-sized (gcc emits a post-call lsl/lsr extend when a u8-typed call
 * feeds a u8 return; ROM has none). ABI-identical to the u8 definition
 * in src/w20d_08010ec4.c. The definition returns u32 for the same reason.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;

extern u32 F_08010EC4(u8 a, s8 b, s8 c, s8 d, u8 e);

__attribute__((section(".text.w21d_08010E7C")))
u32 F_08010E7C(u8 a, s8 b, s8 c, s8 d)
{
    return F_08010EC4(a, b, c, d, 0);
}
