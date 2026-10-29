/* W37-C attempt 1: 0x08042d80, 148 B. State-machine step on struct *s:
 * switch(s->f6): case 0 inits fields, calls EwGet16_18, thresholds,
 * calls F_08043630, f6++, falls into case 1: ret=(u8)F_08042f44(s);
 * default: ret=0.
 * Extern callees + addresses: EwGet16_18 0x08024760, F_08043630 0x08043630,
 * F_08042f44 0x08042f44 (unmatched callee, file-local .set).
 * Pools (LE): 0x02003670, 0x11ac, 0x46a8, 0x46ac, 0x46b2, 0x46b3.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 EwGet16_18(void);
extern void F_08043630(u8 *s);
extern u8 F_08042f44(u8 *s);
__asm__(".set F_08042f44, 0x08042f44");

__attribute__((section(".text.w37c_08042d80")))
u8 Sub_08042D80(u8 *s)
{
    u8 ret = 0;
    switch (s[6]) {
    case 0:
        {
            u8 *gp = (u8 *)0x02003670;
            __asm__ volatile("" : "+r"(gp));
            gp[0x11ac] = 0;
        }
        *(u32 *)(s + 0x46a8) = 0;
        *(u32 *)(s + 0x46ac) = 0;
        *(u32 *)(s + 0x46b0) = 0;
        s[0x46ac] = 5;
        s[0x46b0] = 0;
        s[0x46b2] = 0;
        s[0x46b1] = 1;
        if (EwGet16_18() > 7)
            s[0x46b3] = 1;
        else
            s[0x46b3] = 0;
        F_08043630(s);
        s[6]++;
    case 1:
        ret = F_08042f44(s);
        break;
    default:
        break;
    }
    return ret;
}
