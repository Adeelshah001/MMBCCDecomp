/* Wave20 worker C @0x0801e14c (34 B), attempt 3. Explicit off temp for lsls r0,r2,#2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 ClearSlot_10F88(u8 x);
__attribute__((section(".text.w20c_0801e14c")))
void SlotCopy_0801E14C(u8 *s)
{
    ClearSlot_10F88(s[16]);
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
