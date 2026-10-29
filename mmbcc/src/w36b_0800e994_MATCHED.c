/* Wave 36-B MATCHED: 0x0800e994, 116 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_0800e994_patch.py).
   Extent basis: next function start 0x0800ea08 - 0x0800e994 = 116,
   incl. 24 B literal pool (0x02005130, 0x02004830, 0x02004fa0,
   0x02005280, 0x020053d0, 0x02004f80).
   Variant count: 2 (v2 = C after B[0] + F struct field + patch).
   Key idioms: two zero variables (r2 for A[43], r4 for the other
   stores + B[0]); C is loaded AFTER B[0] so it reuses r4 (zero dead
   by then) instead of forcing an r5 push; F[2] uses a struct field
   (base + offset) so gcc does not fold F+2 into the pool constant.
   Patch (asserted exactly-1): zero-assignment order (r2 first,
   then r4).
   Callees: Sub_08004E50(2) + Sub_08011DF0(C,D,2) +
   Sub_08016FD0(C+40,E,36) + Sub_0800EE98() + Sub_08004DFC(F[2])
   via .set.
   Harness: ./verify_patch.sh 0x0800e994 116 .text.w36b_0800e994
   w36b_0800e994_MATCHED.c old w36b_0800e994_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct A { u16 f0; u16 f2; u8 pad4[4]; u8 f8; u8 f9; u8 f10; u8 pad11; u16 f12; u16 f14; u16 f16; u16 f18; u8 pad20[4]; u16 f24; u8 pad26[2]; u32 f28; u8 pad32[11]; u8 f43; };
struct F { u8 pad[2]; u8 f2; };
extern void Sub_08004E50(int x);
__asm__(".set Sub_08004E50, 0x08004e50");
extern void Sub_08011DF0(void *a, void *b, int c);
extern void Sub_08016FD0(void *a, void *b, int c);
extern void Sub_0800EE98(void);
extern void Sub_08004DFC(u8 x);
__asm__(".set Sub_08004DFC, 0x08004dfc");
__attribute__((section(".text.w36b_0800e994")))
void Sub_0800E994(void)
{
    struct A *a = (struct A *)0x02005130;
    int z2 = 0;
    int z1 = 0;
    a->f0 = z1;
    a->f2 = 60;
    a->f24 = z1;
    a->f28 = z1;
    a->f10 = 255;
    a->f8 = 50;
    a->f9 = 50;
    a->f12 = z1;
    a->f14 = z1;
    a->f16 = z1;
    a->f18 = z1;
    a->f43 = z2;
    Sub_08004E50(2);
    *(u16 *)0x02004830 = z1;
    {
        void *c = (void *)0x02004fa0;
        Sub_08011DF0(c, (void *)0x02005280, 2);
        Sub_08016FD0((u8 *)c + 40, (void *)0x020053d0, 36);
    }
    Sub_0800EE98();
    Sub_08004DFC(((struct F *)0x02004f80)->f2);
}
