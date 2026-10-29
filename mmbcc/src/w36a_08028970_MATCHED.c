typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

extern int sub_08028778(u8 *p, u8 v);
extern int F_0802FD68(u8 *p);

__attribute__((section(".text.w36a_08028970")))
u32 Check_08028970(u8 *s)
{
    u8 flags = s[6];
    s8 v;
    if (flags & 8)
        goto set0;
    if (flags & 32) {
        v = (s8)sub_08028778(s + 1, 0);
        if (v != 0)
            return 0;
        goto done;
    }
    if (s[1] == 0)
        s[1] = 1;
    else if (s[1] != 1)
        return 0;
    if ((u8)F_0802FD68(s) == 0)
        return 0;
set0:
    v = 0;
done:
    s[0] = 1;
    s[1] = v;
    return 0;
}

__asm__(".set sub_08028778, 0x08028778");
__asm__(".set F_0802FD68, 0x0802fd68");
