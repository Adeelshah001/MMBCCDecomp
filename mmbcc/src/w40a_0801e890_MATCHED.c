/* W37-C2: 0x0801e890, 172 B.
 * W40-A: o3s lineage (old_agbcc) + .s patch for sv-copy/off-order/
 * IncUse-idx/clamp-pool; trailing .hword dropped (patch restores 172 B).
 * Init task (1ec44 family): s[12]=1; s[20]=*(u32*)(*(u32*)
 * (0x082243d8+s[9]*4)+4); s[108]=0; s[10]=(s[10]|2)|1;
 * t=0x08226aec+s[16]*3; ChipSlot_Setup(s,1024|t[0],t[2]);
 * ChipSlot_IncUse(s,t[1]); s[18]=0; bitfield clamp (same as
 * 0x0801ec44); s[34]=s[17]+14; F_0801E93C(s).
 * Callees: ChipSlot_Setup 0x0800d6e0 (MATCHED), ChipSlot_IncUse
 * 0x0800d9ec (MATCHED), F_0801E93C 0x0801e93c (MATCHED).
 * Pools (LE): 0x082243d8, 0x08226aec, 0x081705b0, 0x020031e4.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, int b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void F_0801E93C(u8 *s);
__asm__(".set F_0801E93C, 0x0801e93c");

__attribute__((section(".text.w40a_0801e890")))
void Sub_0801E890(u8 *s)
{
    u8 *t;
    int v;
    {
        u8 *q;
        int tmp;
        int w;
        u8 t10;
        register int one __asm__("r1");
        register u8 *base1 __asm__("r1");
        u32 *tp;
        register u8 *base2 __asm__("r1");
        base1 = (u8 *)0x082243d8;
        __asm__ volatile("" : "+r"(base1));
        tp = (u32 *)(s[9] * 4 + (u32)base1);
        one = 1;
        *(u32 *)(s + 12) = one;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
        *(u32 *)(s + 108) = 0;
        t10 = 2 | s[10];
        t10 = t10 | one;
        s[10] = t10;
        {
            register u32 base __asm__("r4");
            register int off __asm__("r0");
            int idx;
            u32 e;
            int sv;
            u8 a;
            u8 b;
            u8 c;
            base = 0x08226aec;
            __asm__ volatile("" : "+r"(base));
            idx = s[16];
            off = idx << 1;
            off += idx;
            e = off + base;
            sv = 128 << 3;
            sv |= *(u8 *)e;
            {
                u32 p2 = base + 2;
                b = *(u8 *)(off + p2);
            }
            ChipSlot_Setup(s, sv, b);
            idx = s[16];
            off = idx << 1;
            off += idx;
            base = base + 1;
            ChipSlot_IncUse(s, *(u8 *)(off + base));
        }
        s[18] = 0;
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        __asm__ volatile("" : "+r"(w));
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
    }
    {
        u8 t34 = s[17] + 14;
        s[34] = t34;
    }
    F_0801E93C(s);
}
