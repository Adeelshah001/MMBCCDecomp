typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Sub_2666C(u8 *s, u16 idx);
__attribute__((section(".text.w17d_0802508C")))
void F_0802508C(u16 idx)
{
    u16 i = idx;
    u8 *p;
    __asm__ volatile("" : "=r" (p) : "0" ((u8 *)0x02007090));
    if (i != 0) {
        Sub_2666C(p + 24, i);
    }
}

