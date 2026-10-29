/* Wave 36-B MATCHED: 0x0800cc94, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x0800cd00 (func_list v2) - 0x0800cc94 = 108,
   incl. 20 B literal pool in two clusters (0x02000ec0, 0x08173530, 0x020031e0;
   0x020031e0, 0x0000c7ff).
   Variant count: 7 (v3 base = s8 value with shifted sign test, struct-field +10;
   v4/v5/v6/v7 prologue variants did not beat it).
   Patch (w36b_0800cc94_patch.py, asserted counts): reorder only + register
   renames -- both pool loads first with index in r3, first-branch OR value in
   r3, else-branch base/value swapped to r2/r1, field load after mask constant.
   No instructions added or removed; pool position unchanged.
   Callees: Sub_0800CF10 + Sub_080006DC via .set (both unmatched in registry).
   Harness: ./verify_patch.sh 0x0800cc94 108 .text.w36b_0800cc94
   w36b_0800cc94_MATCHED.c old w36b_0800cc94_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Q { u16 a; u16 b; u16 c; u16 d; u16 e; u16 f; };
extern void Sub_0800CF10(u8 *p, u8 v, int one);
__asm__(".set Sub_0800CF10, 0x0800cf10");
extern void Sub_080006DC(int a, u32 b, int c);
__asm__(".set Sub_080006DC, 0x080006dc");
__attribute__((section(".text.w36b_0800cc94")))
void Sub_0800CC94(void)
{
    s8 v = *(s8 *)(0x08173530 + *(u8 *)0x02000ec0 * 2);
    if (v >= 0) {
        Sub_0800CF10((u8 *)0x02000ec0, (u8)v, 1);
        ((struct Q *)0x020031e0)->a |= 0x3800;
    } else {
        ((struct Q *)0x020031e0)->a &= 0xc7ff;
        Sub_080006DC(0, ((((struct Q *)0x020031e0)->f & 0x1f00) << 3) + 0x06000000, 0x1000);
    }
}
