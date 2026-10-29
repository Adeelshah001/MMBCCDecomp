/* Wave 36-B MATCHED: 0x0800ed44, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x0800edb0 (func_list v2) - 0x0800ed44 = 108,
   incl. 20 B literal pool in two clusters (0x02005020, 0x02005130;
   0x02005020, 0x02005130, 0x08223f9c).
   Variant count: 6 (v6 = pinned w r4 + pinned b-copy r5 + p assigned per branch
   and live into common code; v3 first found the 4-arg callee form).
   Patch (w36b_0800ed44_patch.py, asserted counts): store address uniformly in
   r2 with base in r0/r1, zero-branch jump past the nonzero-path base copy,
   common code in ROM order with ldrh + lsl/asr replaced by movs + ldrsh
   (agbcc never emits ldrsh from C), compensated by the base copy.
   No net instruction change on either path; pool position unchanged.
   Callees: Sub_080103E0 + Sub_0800E1F0 via .set (both unmatched in registry).
   Harness: ./verify_patch.sh 0x0800ed44 108 .text.w36b_0800ed44
   w36b_0800ed44_MATCHED.c old w36b_0800ed44_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
struct T { u16 a; s16 b; };
struct W { u32 f0; u32 f4; };
extern s8 Sub_080103E0(u8 b, u32 w, int zero, s16 x);
__asm__(".set Sub_080103E0, 0x080103e0");
extern void Sub_0800E1F0(int x);
__asm__(".set Sub_0800E1F0, 0x0800e1f0");
__attribute__((section(".text.w36b_0800ed44")))
s8 Sub_0800ED44(u8 a, u8 b)
{
    u8 *p;
    register u32 w __asm__("r4");
    register u8 bb __asm__("r5") = b;
    s16 x;
    s8 res;
    if (a == 0) {
        w = ((struct W *)0x02005020)->f0;
        p = (u8 *)0x02005130;
        p[43] = 0;
    } else {
        w = ((struct W *)0x02005020)->f4;
        p = (u8 *)0x02005130;
        p[43] = 1;
    }
    x = ((struct T *)0x08223f9c)[p[6]].b;
    res = Sub_080103E0(bb, w, 0, x);
    if (res == 1) {
        Sub_0800E1F0(16);
        return 1;
    }
    return res;
}
