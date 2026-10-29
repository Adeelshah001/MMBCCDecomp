/* W33-D MATCHED: LoopSet_0804C8A4, NO pins. Four vars live across the bl
 * (p, n, m1, m2) should take r4-r7 naturally; copy-asm forces the
 * adds r0,rX,#0 copies. Declaration order m1, n, p.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void CallVia_Mem1(u8 *s);

__attribute__((section(".text.w33d_0804c8a4")))
void LoopSet_0804C8A4(u8 *s)
{
    s32 n = s[8];
    u8 *p = *(u8 **)(s + 44);
    if (n > 0) {
        u32 m1 = 128;
        do {
            u32 v = p[0];
            u32 a;
            __asm__ volatile("add %0, %1, #0" : "=r" (a) : "r" (m1));
            if ((a & v) == 0)
                goto next;
            {
                u32 m2 = 64;
                u32 b;
                __asm__ volatile("add %0, %1, #0" : "=r" (b) : "r" (m2));
                if ((b & v) == 0)
                    goto next;
                CallVia_Mem1(p);
                p[0] = (u8)m1;
                p[15] = 2;
                p[19] = (u8)m2;
                p[25] = 22;
                {
                    u8 *q = p + 36;
                    *q = 1;
                }
            }
        next:
            n--;
            p += 80;
        } while (n > 0);
    }
}
