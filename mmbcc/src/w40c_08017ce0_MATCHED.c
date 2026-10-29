/* W40-C v2: s[10] clear first, then a nested block for the pinned-barrier
 * table load so the pool load cannot be hoisted above the clear. */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w40c_08017ce0")))
void Sub_08017CE0(u8 *s)
{
    s[10] &= 254;
    {
        register u32 base __asm__("r2") = 0x082243D8;
        register u32 idx __asm__("r3");
        u32 off;
        u32 *e;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        e = (u32 *)(off + base);
        *(u32 *)(s + 12) = 4;
        *(u32 *)(s + 20) = *(u32 *)(*e + 16);
    }
}
