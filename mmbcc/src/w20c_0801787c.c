/* Wave20 worker C @0x0801787c (38 B). Same scheduling pattern as 0x0801e14c.
 * Prologue: DecIfNonZero_18(*(s+44)); *(s+44)=0. Then pinned-barrier idiom.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void DecIfNonZero_18(u8 *s);
__attribute__((section(".text.w20c_0801787c")))
void SlotClear_0801787C(u8 *s)
{
    DecIfNonZero_18(*(u8 **)(s + 44));
    *(u32 *)(s + 44) = 0;
    {
        register u32 base __asm__("r1") = 0x082243D8;
        register u32 idx __asm__("r2");
        u32 off;
        u32 *p;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        {
            u32 addr = off + base;
            *(u32 *)(s + 12) = 4;
            p = *(u32 **)addr;
        }
        *(u32 *)(s + 20) = p[4];
    }
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
