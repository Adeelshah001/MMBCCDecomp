/* Wave 15-C: IdxLookup_080246FC @ 0x080246fc (main). Coordinator-landed, 0-diff verified. */
/* IdxLookup_080246FC @0x080246FC — wave15_C_redo2 candidate (main agbcc).
 * if (x > 248) return 0; return (u8)DerefIdx_08025564(pp, (u8)x);
 * NOTE: literal pool (0x02007090) sits mid-function in ROM, after the b.n. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 DerefIdx_08025564(u8 *pp, u8 x);

__attribute__((section(".text.w15c2_080246FC")))
u8 IdxLookup_080246FC(u16 x)
{
    register u8 *pp __asm__("r2") = (u8 *)0x02007090;
    if (x > 248)
        return 0;
    return (u8)DerefIdx_08025564(pp, (u8)x);
}

