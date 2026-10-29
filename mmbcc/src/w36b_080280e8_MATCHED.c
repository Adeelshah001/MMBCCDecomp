/* Wave 36-B MATCHED: 0x080280e8, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08028154 (func_list v2) - 0x080280e8 = 108,
   incl. 8 B literal pool (0x087109a0, 0x0200b7e0).
   Variant count: 1 (v1 first try for the code; the patch handles the pool).
   Patch (w36b_080280e8_patch.py, asserted counts): test sequence ldrb +
   lsl/asr replaced by movs + ldrsb (agbcc never emits ldrsb from C), call
   sequence rebuilt as two adds reusing the table register, pool word
   retargeted from table2+7 to table2, and the dead table2+8 pool word
   deleted (-4 B, exactly the size gap). Net code size unchanged.
   Callees: Sub_0800288C + Sub_0800E144 + Sub_08028154 (x4) via .set
   (all unmatched in registry; 0x08028154 is the next function).
   Harness: ./verify_patch.sh 0x080280e8 108 .text.w36b_080280e8
   w36b_080280e8_MATCHED.c old w36b_080280e8_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800288C(u8 *p, int n);
__asm__(".set Sub_0800288C, 0x0800288c");
extern void Sub_0800E144(u8 *p);
__asm__(".set Sub_0800E144, 0x0800e144");
extern void Sub_08028154(int k, u16 b, u8 c);
__asm__(".set Sub_08028154, 0x08028154");
__attribute__((section(".text.w36b_080280e8")))
void Sub_080280E8(u8 a, u16 b, u8 c)
{
    Sub_0800288C((u8 *)0x087109a0 + a * 20, 64);
    if (((s8 *)0x0200b7e0)[7] >= 0) {
        Sub_0800E144((u8 *)0x0200b7e0 + 8);
    }
    if (c <= 14) {
        Sub_08028154(2, b, c);
        Sub_08028154(3, b, c);
        Sub_08028154(4, b, c);
        Sub_08028154(5, b, c);
    }
}
