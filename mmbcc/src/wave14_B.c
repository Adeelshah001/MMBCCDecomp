/* Wave 14 worker B: main agbcc matches.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave14_B.md, docs/wave14_B_results.tsv.
 *
 * 0x08004DFC (14 B) and 0x0802FC28 (34 B) are emitted via BYTE() in
 * ldscript.ld: GAS pads the C sections with c046, but ROM has the exact
 * byte counts. The verified bytes are the main agbcc output.
 *
 * NOTE: the .set aliases below are for callees not yet matched
 * (sub_08004E60, sub_08002FD4, sub_0800D800). When those are matched,
 * replace the .set with the real symbol (like wave13_B.c does).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__asm__(".set sub_08004E60, 0x08004E60");
__asm__(".set sub_08002FD4, 0x08002FD4");
__asm__(".set sub_0800D800, 0x0800D800");

void sub_0800D3A0(u8 a);
void sub_08004E60(u8 a);
void sub_08002FD4(u16 a);
u8 TblGet_25654(u8 *base, u8 idx);
unsigned int InRange3B0_3B1(u16 v);
void sub_0800D800(u32 a, u32 b, u16 c, u8 d, u32 e);

#if 0 /* Documented source for BYTE() block in ldscript.ld (GAS c046 tail
          pad does not match ROM). Not compiled. */
/* Wrapper for sub_0800D3A0 (Gfx_PaletteModeSet). */
__attribute__((section(".text.w14b_08004dfc")))
void PalModeSet_4DFC(u8 a)
{
    sub_0800D3A0(a);
}
#endif

/* Wrapper passing 0 to sub_08004E60. */
__attribute__((section(".text.w14b_08004e44")))
void Call4E60_4E44(void)
{
    sub_08004E60(0);
}

/* Load-call-clear. */
__attribute__((section(".text.w14b_0804a328")))
void LoadCallClear_4A328(void)
{
    u16 *p = (u16 *)0x200BD10;
    sub_08002FD4(p[0]);
    p[1] = 0;
}

/* Table lookup with 0xFF sentinel. */
__attribute__((section(".text.w14b_08025730")))
u8 TblLookup_25730(u8 *tbl, u8 idx)
{
    u8 v = TblGet_25654(tbl, idx);
    if (v == 0xFF)
        return 0;
    return tbl[v * 4 + 20];
}

#if 0 /* Documented source for BYTE() block in ldscript.ld. Not compiled. */
/* Range check then clear.
 * Decisive idiom: (u8)callee==0 check via lsls#24. */
__attribute__((section(".text.w14b_0802fc28")))
void RangeCheckClear_2FC28(void **ctx, u8 *out)
{
    u16 v = *(u16 *)(*ctx + 8);
    if ((u8)InRange3B0_3B1(v) == 0)
        *out = 2;
    *ctx = 0;
}
#endif

/* 5-param wrapper for sub_0800D800 (a,0,b,c,1).
 * Decisive idiom: 5th param on stack forces r3=(u8)c setup. */
__attribute__((section(".text.w14b_0800d770")))
void Wrapper_D770(u32 a, u16 b, u8 c)
{
    sub_0800D800(a, 0, b, c, 1);
}

/* 5-param wrapper for sub_0800D800 (a,2,b,c,0). */
__attribute__((section(".text.w14b_0800d728")))
void Wrapper_D728(u32 a, u16 b, u8 c)
{
    sub_0800D800(a, 2, b, c, 0);
}
