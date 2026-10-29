/* Wave 35-D v3: 0x0804990C — v1 kept v in r1 and dropped the re-extension.
 * New angle: pin v to r0, separate vp1 temp (adds r1,r0,#1), opaque barrier
 * on v after the store to defeat range analysis, tbl+v pointer form.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void FlagBit_Set_11D68(u8 w, u8 one);

__attribute__((section(".text.w35d_0804990c")))
void Sub_0804990C(void)
{
    register u8 *base __asm__("r2") = (u8 *)0x020070F0;
    register u8 *tbl __asm__("r3") = (u8 *)0x082344E0;
    register u8 v __asm__("r0");
    u8 vp1;
    u8 w;
    __asm__ volatile("" : "+r"(base), "+r"(tbl));
    v = base[21];
    vp1 = v + 1;
    base[21] = vp1;
    __asm__ volatile("" : "+r"(v));
    {
        u32 idx = v;
        idx += (u32)tbl;
        w = *(u8 *)idx;
    }
    FlagBit_Set_11D68(w, 1);
}
