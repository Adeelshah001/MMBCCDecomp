typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Sub_266AC(u8 *s);
__attribute__((section(".text.w17d_080250A8")))
void F_080250A8(void)
{
    u8 *p;
    __asm__ volatile("" : "=r" (p) : "0" ((u8 *)0x02007090));
    Sub_266AC(p + 24);
}

