/* Wave 33-B v6: 0x0800cd5c — v5 with u32 mask to defeat pool sign-extension. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void BitCtl_520C(u32 x);
extern u8 NodeInitSwitch_0800D1E0(u8 *a, u8 *b, u8 *c, u8 *d);

__attribute__((section(".text.w33b_0800cd5c_v6")))
int StateMachine_0800CD5C(u8 *s)
{
    int ret = 1;
    switch (s[1]) {
    case 0:
        if (s[6] == 0) {
            s[1] = 2;
            BitCtl_520C(1);
        } else {
            s[1] = 1;
        }
        s[3] = 0;
        break;
    case 1:
        if (NodeInitSwitch_0800D1E0(s, s + 3, s + 4, s + 5) != 0)
            break;
        s[1] = 2;
        break;
    case 2: {
        if (s[0] != s[7]) {
            int zero = 0;
            s[6] = s[0];
            s[0] = s[7];
            s[3] = zero;
            s[2] = zero;
            s[1] = zero;
            {
                u16 *p = (u16 *)0x020031e0;
                u32 mask = 0xedff;
                u16 v;
                __asm__ volatile("" : "+r"(mask));
                v = *p;
                mask &= v;
                mask &= 0xdbff;
                *p = mask;
            }
        } else {
            ret = 0;
        }
        break;
    }
    default:
        break;
    }
    return ret;
}
