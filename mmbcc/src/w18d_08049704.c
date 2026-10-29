/* Worker D wave18 @0x08049704 (124 B). attempt 5
 * xx->r5 (u32 pin, C mask first), base->r8; preheader q=p copy;
 * do-while for the ROM's entry-test + bottom-test shape.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 AddTableEntry_082344CC(u32 a, u32 b);
extern u8 g_082344d6[];
__attribute__((section(".text.w18d_08049704")))
u8 AllChipCopiesValid_08049704(u8 x)
{
    register u32 xx __asm__("r5");
    register u32 base __asm__("r8");
    u8 ok;
    u8 i;
    u8 *p;
    u8 *q;
    xx = x;
    base = 0x020070f0;
    ok = 1;
    if (xx <= 4) {
        i = 0;
        p = g_082344d6 + xx;
        if (i < *p) {
            q = p;
            do {
                u8 v = AddTableEntry_082344CC(xx, i);
                if (*(u16 *)(base + 12 * v + 50) <= 252)
                    ok = 0;
                i++;
            } while (i < *q);
        }
    } else {
        u8 v = AddTableEntry_082344CC(xx, 0);
        if (*(u16 *)(base + 12 * v + 50) != 255)
            ok = 0;
    }
    return ok;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl g_082344d6\n"
    ".set g_082344d6, 0x082344d6\n"
);
