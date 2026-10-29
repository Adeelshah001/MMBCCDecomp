/* Wave 16-D: ObjInit_21E64 @ 0x08021e64 (112 B: 100 code + 12 pool).
 * Coordinator-landed, 0-diff verified vs ROM (bl immediates are
 * R_ARM_THM_CALL relocs). Compiler: old_agbcc.
 * Behavior: *(u32*)(s+108)=0; s[10]=(2|s[10])|1 (two-step OR);
 * ChipSlot_Setup(s,0x2d01,0); ChipSlot_IncUse(s,0);
 * idx=((u8*)(0x20031e4+((*(u16*)0x81705b0>>4)*2))&3), clamped to <=3;
 * s[69]=(s[69]&-13)|(idx*4); s[0x22]=0; s[0x12]=0xff.
 * Idioms: opaque zero (tied empty asm) defeats r5 zero-CSE -> fresh
 * movs r0,#0 for both stores (push {r4,lr}, not {r4,r5,lr}); two-step OR
 * via int temp (defeats 2|1 folding); tied-opaque pool3 load into r1
 * placed after the shift; divided-syntax "add %0,%0,%1" forces
 * adds r0,r0,r1 address order; divided-syntax "add %0,%1,#0" forces the
 * redundant adds r0,r1,#0 copy before cmp; int mask=-0xd gives
 * movs+negs; sh=idx*4 computed before mask materialization. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
void ChipSlot_Setup(u8 *s, u16 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
void ObjInit_21E64(u8 *s) __attribute__((section(".text.w16d_08021e64")));
void ObjInit_21E64(u8 *s)
{
    int idx;
    *(u32 *)(s + 108) = 0;
    {
        int t = 2 | s[10];
        t |= 1;
        s[10] = t;
    }
    ChipSlot_Setup(s, 0x2d01, 0);
    ChipSlot_IncUse(s, 0);
    {
        int t = ((*(u16 *)0x81705b0 >> 4) * 2);
        register u8 *p3 __asm__("r1");
        register int a __asm__("r1");
        __asm__ volatile("" : "=r" (p3) : "0" ((u8 *)0x20031e4));
        __asm__ volatile("add %0, %0, %1" : "+r" (t) : "r" (p3));
        a = ((((u8 *)t)[0]) & 3);
        {
            register int b __asm__("r0");
            __asm__ volatile("add %0, %1, #0" : "=r" (b) : "r" (a));
            if (b > 3)
                a = 3;
            idx = a;
        }
    }
    {
        u8 *q = s + 69;
        int sh = idx * 4;
        int mask = -0xd;
        *q = (*q & mask) | sh;
    }
    {
        u8 *q = s + 0x22;
        int z;
        __asm__ volatile("" : "=r" (z) : "0" (0));
        *q = z;
    }
    s[0x12] = 0xff;
}
