/* Wave 34-D: 0x08007678 v7.
 * Mirror ROM control flow: duplicated FillRect tail per branch (ROM does NOT
 * tail-merge; x!=0 has its own bl + jump-over-pool, x==0 has its own bl).
 * - 0x08172074 via pool-const pin to r2 + barrier (force early ldr r2).
 * - base opaque via pin (prevent +28/+44 fold); separate loads per sub-branch.
 * - ctx loaded separately in each branch (defeat CSE).
 * main agbcc.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern void FillRect_6374(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);

__attribute__((section(".text.w34d_08007678")))
void sub_08007678(u8 a, u8 b, u8 c, u8 d)
{
    register u32 v __asm__("r4");
    if (c != 0) {
        register u8 *tbl __asm__("r2") = (u8 *)0x08172074;
        u32 t;
        __asm__ volatile("" : "+r"(tbl));
        t = (((*(u32 *)0x02003670) >> 3) & 3) + (d << 2);
        {
            register u32 *base __asm__("r1") = (u32 *)0x08170e7c;
            t += (u32)tbl;
        v = base[*(u8 *)t];
        }
        FillRect_6374((void *)0x0200483c, (s8)(a - 2), (s8)(b - 2), 2, 2, 53, 11, v);
    } else {
        if (d == 0) {
            register u32 *b1 __asm__("r0") = (u32 *)0x08170e7c;
            v = b1[7];
        } else {
            register u32 *b2 __asm__("r0");
            __asm__ volatile("" : "=r"(b2));
            b2 = (u32 *)0x08170e7c;
            v = b2[11];
        }
        FillRect_6374((void *)0x0200483c, (s8)(a - 2), (s8)(b - 2), 2, 2, 53, 11, v);
    }
}
