/* Wave20 worker C @0x080173d4 (36 B). Twin of 0x0801e14c pattern.
 * ROM: ldr r2,[pc] (pool 0x082243D8) BEFORE ldrb r3,[r0,#9].
 * lsls r1,r3,#2; adds r1,r1,r2; s[12]=1; p=p[1]; s[20]=p; s[10]&=254; bl.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void F_173FC(u8 *p);
__attribute__((section(".text.w20c_080173d4")))
void TblSlotInit_080173D4(u8 *s)
{
    {
        register u32 base __asm__("r2") = 0x082243D8;
        register u32 idx __asm__("r3");
        u32 off;
        u32 *p;
        u32 t;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        {
            u32 addr = off + base;
            *(u32 *)(s + 12) = 1;
            p = *(u32 **)addr;
        }
        p = (u32 *)p[1];
        *(u32 *)(s + 20) = (u32)p;
        t = s[10];
        s[10] = t & 254;
    }
    F_173FC(s);
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
