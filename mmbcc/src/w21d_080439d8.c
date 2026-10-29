/* Wave 21-D @0x080439D8 (184 B code + 12 B pool). MATCHED with old_agbcc.
 * DrawObj_080439D8: renders an object via table lookups and blit requests.
 * idx = F_0802478C((p[0x46A9] >> 4) + p[0x46AA]); v = Wrap_GetRomTableU16(idx);
 * if (idx > 199) v += GetEnt_U16_14(); three GatedDispatch calls with
 * coordinate args from the 0x08232D84 table, then a Gfx_BlitRequest using
 * a pointer from the 0x08232DF0 table indexed by (TblGet_f08(idx) >> 12).
 *
 * Idioms: old_agbcc's scheduler emits ROM's `ldrb; lsr #4` before the
 * second address computation (main agbcc interleaves it late); pinned
 * `register u8 *r4 __asm__("r4")` (0x08232D84 table) and `register u32
 * zero __asm__("r6")` (5th-arg slot filler) reproduce ROM's allocation
 * (idx->r7, v->r5); empty-asm barrier pins the 0x08232DF0 pool load before
 * the TblGet_f08 call; explicit u32 p0 forces the *pp load early.
 * Codegen-shaped callee externs: F_0802478C takes u32 (avoids a conversion
 * extend ROM lacks); Gfx_BlitRequest takes u32s (ROM passes s8-derived
 * ints with no extends). ABI-identical to the definitions.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u8 F_0802478C(u32 idx);
extern u16 Wrap_GetRomTableU16(u8 idx);
extern u16 GetEnt_U16_14(void);
extern u16 TblGet_f00(u8 idx);
extern u16 TblGet_f04(u8 idx);
extern u16 TblGet_f08(u8 idx);
extern u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d);
extern void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);

__attribute__((section(".text.w21d_080439D8")))
void DrawObj_080439D8(u8 *p)
{
    u8 b0;
    u8 idx;
    u16 v;
    register u8 *r4 __asm__("r4");
    register u32 zero __asm__("r6");
    u16 t0;
    u16 t1;
    u32 *tbl;
    u32 off;
    u32 *pp;
    u32 p0;
    int a1;
    int a2;

    b0 = p[0x46A9];
    b0 >>= 4;
    idx = (u8)F_0802478C(b0 + p[0x46AA]);
    v = (u16)Wrap_GetRomTableU16(idx);
    if (idx > 199) {
        v = (u16)(v + GetEnt_U16_14());
    }
    t0 = (u16)TblGet_f00(idx);
    r4 = (u8 *)0x08232D84;
    {
        int a1 = (s8)r4[16] + 2;
        int a2 = (s8)r4[17];
        zero = 0;
        GatedDispatch((void *)t0, a1, a2, 3, zero);
    }
    t1 = (u16)TblGet_f04(idx);
    {
        int a1 = (s8)r4[16] + 7;
        int a2 = (s8)r4[17];
        GatedDispatch((void *)t1, a1, a2, 3, zero);
    }
    {
        int a1 = (s8)r4[16] + 2;
        int a2 = (s8)r4[17] + 2;
        GatedDispatch((void *)v, a1, a2, 3, zero);
    }
    tbl = (u32 *)0x08232DF0;
    __asm__ volatile("" : "+r" (tbl));
    off = ((u16)TblGet_f08(idx) >> 12);
    pp = (u32 *)tbl[off];
    p0 = *pp;
    {
        a1 = (s8)r4[16] + 6;
        a2 = (s8)r4[17] + 2;
        Gfx_BlitRequest(p0, a1, a2, 4, zero);
    }
}
