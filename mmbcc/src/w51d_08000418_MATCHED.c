/* W50-D 0x08000418 (228 B) v8 (v7 + barrier-split final mask) — absolute bases as extern symbols (so gcc
 * cannot fold base+offset into one pool word), p2/zero assigned at their
 * first-use points (matching ROM pool order + init placement).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile unsigned char vu8;

extern u8 base_03000400[];
extern u8 base_02002f50[];
extern u16 g_02003220;
extern u16 g_02003230;
extern u16 g_02003240;
extern u16 g_020031e0;
__asm__(".set base_03000400, 0x03000400");
__asm__(".set base_02002f50, 0x02002f50");
__asm__(".set g_02003220, 0x02003220");
__asm__(".set g_02003230, 0x02003230");
__asm__(".set g_02003240, 0x02003240");
__asm__(".set g_020031e0, 0x020031e0");

extern void Sub_08000F28(void);
extern void Sub_08002A04(void);
extern void Sub_08002F24(void);
extern void Sub_0804A2CC(void);
extern void Sub_0800CC24(void);
extern void Sub_0800D420(int a);
extern void Sub_0800D3A0(int a);
extern void Sub_0800456C(void);
extern void Sub_080045F8(void);
extern void Sub_08000DC0(int a);
extern void Sub_08000E80(u32 a);
__asm__(".set Sub_08000F28, 0x08000f28");
__asm__(".set Sub_08002A04, 0x08002a04");
__asm__(".set Sub_08002F24, 0x08002f24");
__asm__(".set Sub_0804A2CC, 0x0804a2cc");
__asm__(".set Sub_0800CC24, 0x0800cc24");
__asm__(".set Sub_0800D420, 0x0800d420");
__asm__(".set Sub_0800D3A0, 0x0800d3a0");
__asm__(".set Sub_0800456C, 0x0800456c");
__asm__(".set Sub_080045F8, 0x080045f8");
__asm__(".set Sub_08000DC0, 0x08000dc0");

__attribute__((section(".text.w51d_08000418")))
void Sub_08000418(void)
{
    u8 *p2;
    u32 zero;
    u8 *a165 = base_03000400;
    (void)*(volatile u8 *)(a165 + 0x165);
    zero = 0;
    a165[0x165] = 1;
    Sub_08000F28();
    base_02002f50[20] = 24;
    base_02002f50[21] = 4;
    base_02002f50[44] = 24;
    base_02002f50[45] = 4;
    p2 = (u8 *)0x03002420;
    p2[0x402] = 32;
    p2[0x401] = 32;
    p2[0x400] = 32;
    *(u16 *)(p2 + 0x404) = 0;
    *(u16 *)(p2 + 0x406) = 0x400;
    Sub_08002A04();
    g_02003220 = 0;
    g_02003230 = 0;
    *(u8 *)((u8 *)&g_02003230 + 14) = 0xff;
    g_02003240 = 0;
    *(u16 *)p2 = 0;
    Sub_08002F24();
    Sub_0804A2CC();
    Sub_0800CC24();
    Sub_0800D420(0);
    Sub_0800D3A0(0);
    Sub_0800456C();
    Sub_080045F8();
    {
        u16 t = g_020031e0 & 0xfff8;
        __asm__ volatile("" : "+r" (t));
        g_020031e0 = (u16)((t & 0xf0ff) | 0x100);
    }
    *(u32 *)((u8 *)&g_020031e0 + 12) = zero;
    Sub_08000DC0(1);
    Sub_08000E80(0x08026741);
}
