/* Wave 22-B @0x0802493C (124 B). MATCHED with old_agbcc.
 * F_0802493C.
 * if (a > 29) return 1;
 * q = *(p+20) + (*(u8 *)(*(p+20) + 432)) * 144;
 * r = CheckPair_258D8(q, a); if (r == 0) return 0; if (r == 2) return 5;
 * r = GetStride4Byte20(q, a); Clear20_Set21_FF(q, a); F_080254E0(p, r);
 * return 0.
 * The address q is recomputed (not kept in a register).
 *
 * Idioms: old_agbcc register allocation (r2 = base+432, r4 = byte);
 * separate r1/r2 result variables so the CheckPair result stays in r0
 * (not live across) while the GetStride result goes to r4 (callee-saved,
 * live across Clear20_Set21_FF); (216 << 1) materializes 432 as
 * movs+ lsls; recomputed q blocks (no base temp).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 CheckPair_258D8(u8 *p, u16 idx);
extern u8 GetStride4Byte20_080258C0(u8 *s, u16 idx);
extern void Clear20_Set21_FF(u8 *s, u16 idx);
extern void Sub_254E0(u8 *s, u8 idx);

__attribute__((section(".text.w22b_0802493C")))
u32 F_0802493C(u8 *p, u8 a)
{
    u8 r1;
    u8 r2;

    if (a > 29)
        return 1;
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        r1 = CheckPair_258D8(q + (u32)b * 144, a);
        if (r1 == 0)
            return 0;
        if (r1 == 2)
            return 5;
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        r2 = GetStride4Byte20_080258C0(q + (u32)b * 144, a);
    }
    {
        u8 *q = (u8 *)(*(u32 *)(p + 20));
        u8 b = *(q + (216 << 1));
        Clear20_Set21_FF(q + (u32)b * 144, a);
    }
    Sub_254E0(p, r2);
    return 0;
}
