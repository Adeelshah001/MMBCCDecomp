/* Wave 20-D @0x080247E8 (48 B). MATCHED with main agbcc.
 * Flag check wrapper: if (TblGet11(a)&2) return 0; else return sub_08025524(p,a)
 * with p=0x02007090. Mid-function literal pool (pool word at +0x24, code resumes
 * after with `movs r0,#0`).
 *
 * Idioms: pinned `register u8 *p __asm__("r5")` forces the pool load to the top
 * into r5 (compiler otherwise sinks it late into r0); int-decl callee avoidance —
 * real u8 prototypes reproduce ROM exactly (no spurious truncation after
 * TblGet11; (u8) cast on sub_08025524 return gives the lsls/lsrs pair).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 TblGet11(u8 a);
extern u8 sub_08025524(u8 *p, u8 x);

__attribute__((section(".text.w20d_080247E8")))
u8 ChkFlag_080247E8(u8 a)
{
    register u8 *p __asm__("r5") = (u8 *)0x02007090;
    if ((TblGet11(a) & 2) != 0) {
        return 0;
    }
    return (u8)sub_08025524(p, a);
}
