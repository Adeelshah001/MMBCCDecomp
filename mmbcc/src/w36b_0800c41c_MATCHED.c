/* Wave 36-B MATCHED: 0x0800c41c, 112 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_0800c41c_patch.py).
   Extent basis: next function start 0x0800c48c - 0x0800c41c = 112,
   incl. 24 B literal pool (0x02003670, 0xfa000a20, 0x08322b80,
   0x02004f40, 0x08173180, 0x0817313c) + 2 B 00 00 pad before the pool
   (gcc .align 2,0 fill).
   Variant count: 11 (v11 = C89 layout, Table extern + barrier, int
   parameter with explicit (s16) casts, base pin ignored by gcc).
   Key idioms: (1) Table MUST be an extern symbol, NOT a .set in this
   file -- a .set folds Table+143 into a single pool word and drops
   ROM's 6 B entry computation (movs #143, lsl #2, adds r6,r4,r1);
   pass Table=0x02003670 as a harness symdef. (2) The empty asm barrier
   (=r / 0 matching constraint; old_agbcc rejects +r, and C89 forbids
   declarations after statements, so all declarations sit at block
   starts) hides Table's value so gcc emits the adds instead of
   folding. (3) The s8 conversion of the call result happens AFTER the
   entry computation (int raw, then (s8)raw), matching ROM's order.
   (4) gcc DOES emit ldrsb from C here (movs r2,#0; ldrsb r2,[r0,r2])
   for the signed-byte tail load -- no patch needed for it.
   Patch (asserted exactly-1): tail load reorder (pool5 into r1 first,
   pool6 into r0; sb addr from r0; ptr from r1 -- net size unchanged)
   + pool word swap (pool5 before pool6, as in ROM).
   Callees: Sub_0800C248 (s16) + Sub_08005268 + Sub_0804DCD8 via .set;
   Table via harness symdef Table=0x02003670.
   Harness: ./verify_patch.sh 0x0800c41c 112 .text.w36b_0800c41c
   w36b_0800c41c_MATCHED.c old w36b_0800c41c_patch.py Table=0x02003670
   -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;
struct S { u8 pad[12]; u32 *f12; };
extern u32 Table[];
extern int Sub_0800C248(s16 idx);
__asm__(".set Sub_0800C248, 0x0800c248");
extern void Sub_08005268(u32 *p, u32 v);
__asm__(".set Sub_08005268, 0x08005268");
extern void Sub_0804DCD8(void *a, u32 b, int c, u32 d);
__asm__(".set Sub_0804DCD8, 0x0804dcd8");
__attribute__((section(".text.w36b_0800c41c")))
void Sub_0800C41C(int idx)
{
    u32 *t;
    u32 *entry;
    int raw;
    s8 r;
    t = Table;
    __asm__ volatile("" : "=r"(t) : "0"(t));
    raw = Sub_0800C248((s16)idx);
    entry = t + 143;
    r = (s8)raw;
    if (r >= 0) {
        u32 v;
        u32 *p;
        v = entry[1] + 0xfa000a20u;
        p = (u32 *)(0x08322b80 + r * 20);
        Sub_08005268(p, v);
        ((struct S *)0x02004f40)->f12 = p;
    }
    {
        s8 sb;
        u32 *ptr;
        register u32 *base __asm__("r1") = (u32 *)0x08173180;
        sb = *(s8 *)(0x0817313c + (s16)idx);
        ptr = base + sb;
        Sub_0804DCD8((void *)0x02004f40, entry[0], 81, *ptr);
    }
}
