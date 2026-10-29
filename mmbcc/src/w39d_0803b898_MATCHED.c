/* W39-D v3: t is u8 (truncation at assignment, before e=0, matching ROM order). Based on v2: 0x0803b898, TRUE extent 256 B.
 * Fixes vs v1 (33 diffs, both compilers): pin s->r5 and e->r4
 * (v1's compiler swapped them: s in r4, e in r5); move the e=0
 * assignment to AFTER the first MapTableVal call (ROM sets r4=0
 * there, not at entry) and the e=2 assignment to AFTER the first
 * 6a54 deref (ROM sets r4=2 there, not before the call). Both are
 * done by splitting the first call of each group into a temp.
 * Otherwise identical decode to v1 (see w39d_0803b898.c header).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int Sub_0800499AC(u8 a);
extern void Sub_080073D4(int a, int b, int c, int d, int e);
extern void Sub_08006A54(u32 a, int b, int c, int d, int e);
extern void Sub_08006DD8(u32 a, int b, int c, int d, int e);

__attribute__((section(".text.w39d_0803b898")))
void Sub_0803B898(u8 *s_in)
{
    register u8 *s __asm__("r5") = s_in;
    register int e __asm__("r4");
    {
        u8 t = Sub_0800499AC(0);
        e = 0;
        Sub_080073D4(22, t, 2, 1, e);
    }
    {
        u8 t = Sub_0800499AC(1);
        Sub_080073D4(23, t, 2, 3, e);
    }
    {
        u8 t = Sub_0800499AC(2);
        Sub_080073D4(24, t, 2, 5, e);
    }
    {
        u8 t = Sub_0800499AC(3);
        Sub_080073D4(25, t, 2, 7, e);
    }
    {
        u32 a0 = *(u32 *)0x08231960;
        e = 2;
        Sub_08006A54(a0, 4, 1, 13, e);
    }
    Sub_08006A54(*(u32 *)0x08231968, 4, 3, 13, e);
    Sub_08006A54(*(u32 *)0x08231970, 4, 5, 13, e);
    Sub_08006A54(*(u32 *)0x08231978, 4, 7, 13, e);
    Sub_08006DD8(*(u32 *)(s + 32), 20, 1, 7, e);
    Sub_08006A54(*(u32 *)0x08231958, 27, 1, 1, e);
    {
        u8 *dst = (u8 *)0x02004ce0;
        u8 b;
        *(u16 *)(dst + 40) = 20;
        s += 0x4698;
        b = *s;
        *(u16 *)(dst + 42) = (b << 4) + 8;
    }
}

__asm__(".set Sub_0800499AC, 0x080499ac");
__asm__(".set Sub_080073D4, 0x080073d4");
__asm__(".set Sub_08006A54, 0x08006a54");
__asm__(".set Sub_08006DD8, 0x08006dd8");
