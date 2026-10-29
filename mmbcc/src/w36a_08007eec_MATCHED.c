typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void sub_0800dd74(u8 *p);

__attribute__((section(".text.w36a_08007eec")))
void SetBit_08007eec(u16 idx)
{
    u8 *p = (u8 *)0x02004e18 + idx * 8;
    u8 m = 2;
    u16 *g = (u16 *)0x08171ef4;
    p[7] |= m;
    if (idx == 0) {
        register u16 v __asm__("r0") = g[1];
        register u32 t __asm__("r1") = v << 5;
        t += 0x03002420;
        sub_0800dd74((u8 *)t);
    }
}

__asm__(".set sub_0800dd74, 0x0800dd74");
