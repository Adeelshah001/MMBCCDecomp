typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Poke80_08016f74(u8 *p);
extern u32 Byte128_IsZero(u8 *s);
extern void SetByte20_Clear21to23_02005130(u8 v);
extern void ListIterate_D568(u8 *s);
__attribute__((section(".text.w18c_0800e6d0")))
void StateMachine_0800E6D0(void)
{
    u8 *g = (u8 *)0x02005130;
    u32 v;
    u8 st;
    *(u16 *)(g + 24) = 1;
    {
        volatile u32 *p;
        if (g[0x29] == 0) {
            p = (volatile u32 *)0x02005020;
            v = p[0];
        } else {
            p = (volatile u32 *)0x02005020;
            v = p[1];
        }
    }
    st = g[21];
    if (st == 0) goto L0;
    if (st == 1) goto L1;
    goto Lend;
L0:
    Poke80_08016f74((u8 *)v);
    g[21]++;
    goto Lend;
L1:
    if ((u16)Byte128_IsZero((u8 *)v) != 0) {
        u8 *g2;
        u32 z;
        __asm__ volatile("" : "=r" (g2) : "0" ((u8 *)0x02005130));
        z = 0;
        *(u16 *)(g2 + 24) = z;
        SetByte20_Clear21to23_02005130(z);
    }
Lend:;
    ListIterate_D568(*(u8 **)0x02005270);
    ListIterate_D568(*(u8 **)0x020053c0);
}

