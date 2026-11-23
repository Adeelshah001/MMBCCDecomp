/* identical to sub_0800CDE8 (matched), with its names changed by decompdecomp */
extern u8 sub_0800D12C(u8 *s, u8 *a, u8 *b, u8 *c);
extern u8 sub_0800D278(u8 *s, u8 *a, u8 *b, u8 *c);

int sub_0800CE7C(u8 *s)
{
    int ret = 1;
    switch (s[1]) {
    case 0:
        if (s[6] == 0) {
            s[1] = 1;
        } else {
            s[1] = 2;
        }
        break;
    case 1:
        if (sub_0800D12C(s, s + 3, s + 4, s + 5) != 0)
            break;
        s[1] = 3;
        break;
    case 2:
        if (sub_0800D278(s, s + 3, s + 4, s + 5) != 0)
            break;
        s[1] = 3;
        break;
    case 3:
        if (s[0] != s[7]) {
            int zero = 0;
            s[6] = s[0];
            s[0] = s[7];
            s[3] = zero;
            s[2] = zero;
            s[1] = zero;
            {
                u16 *p = (u16 *)0x020031E0;
                u32 mask = 0xedff;
                u16 v = *p;
                mask &= v;
                mask &= 0xdbff;
                *p = mask;
            }
        } else {
            ret = 0;
        }
        break;
    default:
        break;
    }
    return ret;
}
