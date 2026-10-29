/* Wave 40 Worker D: 0x0804b7f0, 356 B, state machine (s[3] = state,
   u16 timer at s[6]). Sibling of 0x0804b634. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *BuildNodePair_08020340(u8 *a);
extern u8 *F_08020514(u8 *p);
extern void Sub_080006DC(u32 a, u32 b, u32 c);
extern int Sub_08004E0C(u32 a);
extern void Sub_08004E24(u8 a);
extern void Sub_08004DFC(u32 a);
extern void CpuFastSet(void *src, void *dst, unsigned mode);
extern u16 KeyInputBase[];
__asm__(".set KeyInputBase, 0x02002f50\n");

__attribute__((section(".text.w40d_0804b7f0")))
void F_0804B7F0(u8 *p)
{
    register u8 *s __asm__("r5") = p;
    u32 zero_buf[2];
    switch (s[3]) {
    case 0:
        if (BuildNodePair_08020340(s) == 0)
            return;
        s[10] |= 1;
        s[3]++;
        *(u16 *)(s + 6) = 240;
    case 1:
        if ((KeyInputBase[2] & 1) != 0)
            goto tick30;
        if (--(*(u16 *)(s + 6)) != 0)
            return;
    tick30:
        s[3]++;
        *(u16 *)(s + 6) = 30;
        return;
    case 2:
        s[3]++;
        {
            int t = s[10] & ~1;
            s[10] = t;
        }
    case 3:
        if ((s[10] & 2) != 0)
            return;
        s[3]++;
        Sub_08004E24(0);
        return;
    case 4:
        if ((u8)Sub_08004E0C(3) == 0)
            return;
        {
            u32 z;
            void *dst;
            register u32 n __asm__("r4");
            u8 ns = s[3] + 1;
            z = 0;
            s[3] = ns;
            s[10] |= 1;
            dst = (void *)(0x06000000 + ((*(u16 *)0x020031e6 & 0x1f00) << 3));
            zero_buf[0] = z;
            n = 512;
            CpuFastSet(zero_buf, dst, 0x01000200);
            Sub_080006DC(0, 0x03002420, n);
        }
    case 5:
        if (F_08020514(s) == 0)
            return;
        s[3]++;
    case 6:
        s[3]++;
        Sub_08004DFC(1);
        return;
    case 7:
        if ((u8)Sub_08004E0C(0) == 0)
            return;
        s[3]++;
    case 8:
        if ((KeyInputBase[2] & 1) == 0)
            return;
        s[3]++;
        Sub_08004E24(0);
        return;
    case 9:
        if ((u8)Sub_08004E0C(3) == 0)
            return;
        *(u32 *)s = 0;
        s[0] = 2;
        return;
    default:
        return;
    }
}
__asm__(
    ".set Sub_080006DC, 0x080006dc\n"
    ".set Sub_08004E0C, 0x08004e0c\n"
    ".set Sub_08004E24, 0x08004e24\n"
    ".set Sub_08004DFC, 0x08004dfc\n"
);
