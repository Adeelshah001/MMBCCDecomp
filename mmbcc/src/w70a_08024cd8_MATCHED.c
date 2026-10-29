/* Wave 70-A v3 (outer condition flipped: F1==0 branch first, to match ROM block layout): 0x08024CD8, fresh. True (tiling) extent 340 B
 * (340 code through bx @0x24E2A; next fn @0x24E2C; no pool, no pad).
 * u16 F(u8 *s, u8 a, u8 b): tbl = *(u8 **)(s + 20); elem =
 * (*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144) (recomputed at every call site in ROM).
 * if (F1(elem, a) != 0) {
 *     if (F2(elem, b) == 0) return F4(elem, a);
 *     if (F2(elem, b) == 2) { v = F3(elem, b); if (v == a) return 0;
 *         return F6(elem, a, v); }
 *     return F5(elem, a, b);
 * } else {
 *     if (F2(elem, b) == 0) return 0;
 *     if (F2(elem, b) == 2) return F6(elem, a, F3(elem, b));
 *     return F5(elem, a, b);
 * }
 * F1/F2/F3 return u8 (ROM tests lsl #24 / lsl+lsr #24); F4/F5/F6
 * declared u32 so the u16 caller truncates (ROM lsl #16 / lsr #16
 * epilogue; literal-0 returns skip truncation).
 * .set stubs are verification-only; coordinator strips landed-callee stubs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

u8 Call_08025730(u8 *e, u8 a);
u8 Call_080258D8(u8 *e, u8 b);
u8 Call_080258F8(u8 *e, u8 b);
u32 Call_08025A10(u8 *e, u8 a);
u32 Call_08025CA0(u8 *e, u8 a, u8 b);
u32 Call_08025B60(u8 *e, u8 a, u8 v);

__attribute__((section(".text.w70a_08024cd8")))
u16 sub_08024CD8(u8 *s, u8 a, u8 b)
{
    if (Call_08025730((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a) == 0) {
        if (Call_080258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 0)
            return 0;
        if (Call_080258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 2)
            return Call_08025B60((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, Call_080258F8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b));
        return Call_08025CA0((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, b);
    } else {
        if (Call_080258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 0)
            return Call_08025A10((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a);
        if (Call_080258D8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b) == 2) {
            u8 v = Call_080258F8((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), b);
            if (v == a)
                return 0;
            return Call_08025B60((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, v);
        }
        return Call_08025CA0((*(u8 **)(s + 20) + (*(u8 **)(s + 20))[432] * 144), a, b);
    }
}

__asm__(
    ".globl Call_08025730\n.set Call_08025730, 0x08025730\n"
    ".globl Call_080258D8\n.set Call_080258D8, 0x080258D8\n"
    ".globl Call_080258F8\n.set Call_080258F8, 0x080258F8\n"
    ".globl Call_08025A10\n.set Call_08025A10, 0x08025A10\n"
    ".globl Call_08025CA0\n.set Call_08025CA0, 0x08025CA0\n"
    ".globl Call_08025B60\n.set Call_08025B60, 0x08025B60\n"
);
