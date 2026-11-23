extern void sub_0804DB24(void *src, void *dst, unsigned mode);
extern void sub_0804DB28(void *src, void *dst, unsigned mode);

void sub_08000758(u8 *s, u8 *d, u32 n)
{
    n &= -2;
    if (n == 0)
        return;
    s = (u8 *)((u32)s & -2);
    d = (u8 *)((u32)d & -2);
    if (((u32)s & 2) || ((u32)d & 2)) {
        sub_0804DB28(s, d, (n << 10) >> 11);
        return;
    }
    if (n > 0x1F) {
        u32 bulk = n & -32;
        sub_0804DB24(s, d, (bulk >> 2) & 0x1FFFFF);
        if ((n & 0x1F) == 0)
            return;
    }
    s += n & -32;
    d += n & -32;
    {
        u32 cnt;
        cnt = n;
        cnt &= 0x1F;
        cnt >>= 1;
        sub_0804DB28(s, d, cnt);
    }
}
