/* Wave 36-B MATCHED: 0x0802142c, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08021498 (func_list v2) - 0x0802142c = 108,
   incl. 16 B literal pool (0x08173760, 0x08226f34, 0x081738f2, 0x03002620).
   Variant count: 8 (v8 = base pinned to r2 + tbl variable + tt temp +
   q/w pins after i=0; v5-v7 fixed the base chase, the +12 temp and the
   pinned-load position in turn).
   Patch (w36b_0802142c_patch.py, asserted counts): reorder only -- table pool
   load ahead of the s[17] byte load, index computation kept in r1.
   No instructions added or removed; pool position unchanged.
   Callee: Sub_0800DDE4 via .set (BLOCKED in registry).
   Harness: ./verify_patch.sh 0x0802142c 108 .text.w36b_0802142c
   w36b_0802142c_MATCHED.c old w36b_0802142c_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
struct S88 { u8 pad[88]; u32 f88; };
struct S44 { u8 pad[44]; u16 f44; };
extern void Sub_0800DDE4(u8 *r3, u16 *buf, u32 x, u8 flag);
__asm__(".set Sub_0800DDE4, 0x0800dde4");
__attribute__((section(".text.w36b_0802142c")))
void Sub_0802142C(u8 *s, u8 flag)
{
    register u32 base __asm__("r2") = ((struct S88 *)0x08173760)->f88;
    u8 *tbl = (u8 *)0x08226f34;
    u8 t = tbl[s[17]];
    u32 *p = (u32 *)(base + t * 4);
    u8 *r3;
    u8 *tt;
    s16 i;
    u16 buf[16];
    p = (u32 *)((u32)p + *p);
    tt = (u8 *)p + 12;
    r3 = tt + *(u32 *)((u8 *)p + 12);
    i = 0;
    {
        register u32 *q __asm__("r4") = (u32 *)0x081738f2;
        register u32 *w __asm__("r5") = (u32 *)0x03002620;
        for (; i <= 15; i++) {
            buf[i] = *(u16 *)(r3 + 30);
        }
        Sub_0800DDE4(r3, buf, ((struct S44 *)q)->f44 * 32 + (u32)w, flag);
    }
}
