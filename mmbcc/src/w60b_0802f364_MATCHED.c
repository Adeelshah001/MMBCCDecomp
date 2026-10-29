/* W60-B v11 (v10 + "cc" clobber on copy asms) (v9 + trailing .balign 4, 0) (v8 + per-branch dst+mask blocks) (v3 + pin-arg only) (v15 + u8 temp + copy-only scoped asm) (t4 pinned r4 + nibLo shift + block2 fix) (nibLo shift only) (4096 early-exit guard) (hp ternary + nibLo declared before b) (result r9 + nibHi sl pins) (ternary else-path + result assigned after b) (hybrid: hp local for switch test/arg, field access inline in
 * else-path calls; no off variable): 0x0802F364, TRUE extent 492 B.
 * ROM order: b load, hp load, s[6]&16 check, nibLo store [sp,#0],
 * nibHi -> sl, base, switch test on hp, else-path reloads the field
 * fresh for each F_244B0 call. Side-byte offset recomputed at each use.
 */
/* FINAL W60-B: old_agbcc 0 DIFFS, 492 B exact (standalone linked-at-address, file as-is).
 * Techniques (all source-level): else-path u8 temp + copy-only scoped asm (compiler emits the
 * lsl/lsr zero-extension in r0, asm emits only `add t7/t4, r0, #0`; unsuffixed Thumb mnemonics
 * for this GAS dialect; "cc" clobber); block-scoped r1-pinned p132 = base+132 with the FE44
 * argument as *(p132+8) (pin live only to the arg load, before the call -- never call-clobbered);
 * per-branch dst+mask blocks whose identical tails the compiler cross-jumps into ROM's shared
 * address+mask+RMW tail (mask variable defeats the movs-#240 fold, giving movs #16 + negs);
 * trailing .balign 4, 0 for the 0000 pad (code 490 B, 2 mod 4). Main agbcc: 425 diffs (old-only).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Sub_08024384(u16 a);
__asm__(".set Sub_08024384, 0x08024384");
extern u8 Sub_080244B0(u16 a, int b);
__asm__(".set Sub_080244B0, 0x080244b0");
extern u16 Sub_080400A8(void);
__asm__(".set Sub_080400A8, 0x080400a8");
extern u8 Sub_0804DEE8(u16 a, int b);
__asm__(".set Sub_0804DEE8, 0x0804dee8");
extern u8 Sub_0803FEF8(u16 a);
__asm__(".set Sub_0803FEF8, 0x0803fef8");
extern u8 Sub_0803FE44(u16 a);
__asm__(".set Sub_0803FE44, 0x0803fe44");

__attribute__((section(".text.w60b_0802f364")))
int Sub_0802F364(u8 *s, u8 kind)
{
    u32 nibLo;
    u32 b;
    u16 hp;
    u8 *base;
    int t7;
    register int t4 __asm__("r4");
    register int res __asm__("r9");
    register u32 nh __asm__("sl");

    if (kind == 0)
        b = s[394];
    else
        b = s[395];
    res = 0;
    hp = kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22);
    if (s[6] & 16)
        return res;
    if (kind == 0 && *(u16 *)(s + 20) == 4096)
        return res;
    if (kind == 0)
        nibLo = ((u32)s[404] << 28) >> 28;
    else
        nibLo = ((u32)s[408] << 28) >> 28;
    if (kind == 0)
        nh = s[404] >> 4;
    else
        nh = s[408] >> 4;
    if (kind == 0)
        base = s + 32;
    else
        base = s + 176;
    if ((hp >> 12) == 2) {
        switch ((u8)Sub_08024384(hp) - 50) {
        case 0: t7 = 60; t4 = 60; break;
        case 1: t7 = 70; t4 = 70; break;
        case 2: t7 = 30; t4 = 30; break;
        case 3: t7 = 70; t4 = 70; break;
        case 4: t7 = 80; t4 = 80; break;
        case 5: t7 = 80; t4 = 80; break;
        default: t7 = 50; t4 = 50; break;
        }
    } else {
        { u8 tmp7 = Sub_080244B0(kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22), 0);
          __asm__ volatile("add %0, %1, #0" : "=r" (t7) : "r" (tmp7) : "cc"); }
        { u8 tmp4 = Sub_080244B0(kind == 0 ? *(u16 *)(s + 20) : *(u16 *)(s + 22), 1);
          __asm__ volatile("add %0, %1, #0" : "=r" (t4) : "r" (tmp4) : "cc"); }
    }
    if (Sub_0804DEE8(Sub_080400A8(), 100) <= 49) {
        if (base[120] != 0 && nh == 0 && b >= (u32)t4 &&
            Sub_0803FEF8(*(u16 *)(base + 128)) != 0) {
            if (kind == 0)
                s[404] = (s[404] & 15) | 16;
            else
                s[408] = (s[408] & 15) | 16;
            res = 1;
        }
    }
    if (Sub_0804DEE8(Sub_080400A8(), 100) <= 49) {
        if (res == 0) {
        register u8 *p132 __asm__("r1") = base + 132;
        if (*p132 != 0 && nibLo == 0 && b >= (u32)t7 &&
            Sub_0803FE44(*(u16 *)(p132 + 8)) != 0) {
            if (kind == 0) { u8 *dst = s + 404; int m = ~15; *dst = (*dst & m) | 1; }
            else { u8 *dst = s + 408; int m = ~15; *dst = (*dst & m) | 1; }
            res = 2;
        }
        }
    }
    return res;
}

/* Trailing pad: code size is 2 mod 4 (490 B through bx); ROM pads with 0000. */
__asm__(".balign 4, 0");
