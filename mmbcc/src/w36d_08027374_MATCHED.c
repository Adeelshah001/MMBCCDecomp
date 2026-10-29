/* Wave 36-D MATCHED (C + .s patch w36d_08027374_patch.py, old_agbcc, 0 diffs over 140 B true extent 0x08027374-0x08027400; fallthrough switch, u8 call returns, case 3 arg copy via patch, zero-in-r1 scheduling), 140 B, extent next-func 0x08027400. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_0802756C(void);
extern u8 Sub_08004E0C(u32 a);
__asm__(".set Sub_08004E0C, 0x08004e0c");
extern u32 Sub_08021D10(void);
__asm__(".set Sub_08021D10, 0x08021d10");
extern u8 Sub_08021D84(u32 a);
__asm__(".set Sub_08021D84, 0x08021d84");
extern void Sub_08002FC4(u32 a);
__asm__(".set Sub_08002FC4, 0x08002fc4");

__attribute__((section(".text.w36d_08027374")))
void Sub_08027374(u8 *s)
{
    switch (s[3]) {
    case 0:
        s[3] = 1;
        Sub_0802756C();
        *(u16 *)0x020031e0 |= 4608;
        /* fall through */
    case 1:
        if (Sub_08004E0C(0) == 0)
            break;
        s[3]++;
        /* fall through */
    case 2: {
        u32 v = Sub_08021D10();
        if (v == 0)
            break;
        *(u32 *)(s + 0x4698) = v;
        s[3]++;
        /* fall through */
    }
    case 3:
        if (Sub_08021D84(*(u32 *)(s + 0x4698)) == 0)
            break;
        {
            u32 f2new = s[2] + 1;
            u32 zero = 0;
            s[2] = f2new;
            s[3] = zero;
        }
        Sub_08002FC4(5);
        break;
    default:
        break;
    }
}
