/* Wave 22-D @0x080405D8 (180 B code + 12 B pool). MATCHED with main agbcc.
 * DrawObj_080405D8: sibling of DrawObj_080439D8. Renders an object via
 * table lookups and blit requests.
 * idx = TblStride_24818(p[0x46A8] + p[0x46A9]); v = Wrap_GetRomTableU16(idx);
 * if (idx > 199) v += GetEnt_U16_14(); three GatedDispatch calls with
 * coordinate args from the 0x082329E0 table, then a Gfx_BlitRequest using
 * a pointer from the 0x08232B90 table indexed by (TblGet_f08(idx) >> 12).
 *
 * Idioms: the whole prologue is one inline-asm block because the final
 * `adds r0, r1, r0` (0x1808) cannot be written as GAS pre-UAL text
 * (Rd==Rm is rejected: "instruction not supported in Thumb16 mode" also
 * applies to the `adds` spelling -- pre-UAL wants `add`), so it is emitted
 * via `.short 0x1808`. u32 pins to r0/r2 are safe; sub-word (u8) register
 * pins are NOT honored by this gcc (silently misallocates) and must not
 * be used. r0v doubles as the TblStride call arg (already in r0, so the
 * call is a bare bl). FIXALIGN1 (first .align 2,0 -> .align 1,0) keeps the
 * 12 B trailing pool at the ROM extent. Codegen-shaped callee externs:
 * TblStride_24818 takes u32 (avoids a conversion extend ROM lacks);
 * Gfx_BlitRequest takes u32s (ROM passes s8-derived ints with no extends).
 * ABI-identical to the definitions.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

/* codegen-shaped externs (ABI-identical to definitions; shaped so gcc
 * emits no extra extends/conversions vs ROM).
 * TblStride_24818 takes u32 in this TU to avoid a u8->u16 conversion extend
 * before the call (ROM has none). */
extern u8 TblStride_24818(u32 idx);
extern u16 Wrap_GetRomTableU16(u8 idx);
extern u16 GetEnt_U16_14(void);
extern u16 TblGet_f00(u8 idx);
extern u16 TblGet_f04(u8 idx);
extern u16 TblGet_f08(u8 idx);
extern u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d);
extern void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);

__attribute__((section(".text.w22d_080405D8")))
void DrawObj_080405D8(u8 *p)
{
    u8 b1;
    u8 b2;
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

    /* Entire prologue in one asm block. The final adds (0x1808 =
     * adds r0, r1, r0) cannot be written as GAS pre-UAL text (Rd==Rm
     * is rejected), so it is emitted via .short. u32 pins to r0/r2
     * are safe; sub-word (u8) pins are NOT honored by this gcc and
     * must not be used (new idiom). r0v doubles as the call arg. */
    {
        register u32 r0v __asm__("r0") = (u32)p;
        register u32 poffr __asm__("r2") = 0x46A8;
        __asm__ volatile (
            "add r1, %0, %1\n\t"
            "add %1, #1\n\t"
            "add %0, %0, %1\n\t"
            "ldrb r1, [r1, #0]\n\t"
            "ldrb r0, [r0, #0]\n\t"
            ".short 0x1808"
            : "+r" (r0v), "+r" (poffr)
            :
            : "r1", "cc"
        );
        idx = (u8)TblStride_24818(r0v);
    }
    v = (u16)Wrap_GetRomTableU16(idx);
    if (idx > 199) {
        v = (u16)(v + GetEnt_U16_14());
    }
    t0 = (u16)TblGet_f00(idx);
    r4 = (u8 *)0x082329E0;
    {
        int a1 = (s8)r4[20] + 2;
        int a2 = (s8)r4[21];
        zero = 0;
        GatedDispatch((void *)t0, a1, a2, 3, zero);
    }
    t1 = (u16)TblGet_f04(idx);
    {
        int a1 = (s8)r4[20] + 7;
        int a2 = (s8)r4[21];
        GatedDispatch((void *)t1, a1, a2, 3, zero);
    }
    {
        int a1 = (s8)r4[20] + 2;
        int a2 = (s8)r4[21] + 2;
        GatedDispatch((void *)v, a1, a2, 3, zero);
    }
    tbl = (u32 *)0x08232B90;
    __asm__ volatile("" : "+r" (tbl));
    off = ((u16)TblGet_f08(idx) >> 12);
    pp = (u32 *)tbl[off];
    p0 = *pp;
    {
        a1 = (s8)r4[20] + 6;
        a2 = (s8)r4[21] + 2;
        Gfx_BlitRequest(p0, a1, a2, 4, zero);
    }
}
