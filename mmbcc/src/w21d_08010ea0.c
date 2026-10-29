/* Wave 21-D @0x08010EA0 (36 B). MATCHED with main agbcc.
 * Twin of 0x08010E7C: zero-extends arg0 (u8), sign-extends args1-3 (s8),
 * passes 1 as 5th arg to Setup_08010EC4.
 *
 * Idioms: same codegen-shaped callee extern as 0x08010E7C
 * ((u8,s8,s8,s8,u8)->u32; see src/w21d_08010e7c.c). Definition returns u32
 * (ROM has no post-call extend).
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;

extern u32 F_08010EC4(u8 a, s8 b, s8 c, s8 d, u8 e);

__attribute__((section(".text.w21d_08010EA0")))
u32 F_08010EA0(u8 a, s8 b, s8 c, s8 d)
{
    return F_08010EC4(a, b, c, d, 1);
}
