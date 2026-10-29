/* W38-A: 0x08035a24, 216 B. Graphics setup (count loop + blits).
 * c7 (u16) = 0; c6 (u8) = 0; for (u8 i = 1; i <= 243; i++):
 * ret = (u8)F_080247C4(i <= 194 ? i : (u8)(i + 5));
 * if (ret != 0) { c7 += ret; c6++; } c7++; c6++;
 * BlitRequest(Dispatch_24434(4096), 2, 4, 4, 0);
 * BlitRequest(TblGetW_BB8C((u8)Sub_080241D0(4096)), 8, 4, 8, 0);
 * Sub_08006DD8(c6, 17, 4, 3, 0);
 * BlitRequest(*(u32*)0x0822E9AC, 20, 4, 1, 0);
 * Sub_08006DD8(c7, 21, 4, 4, 0);
 * BlitRequest(*(u32*)0x0822E9B4, 25, 4, 1, 0);
 * F_08024F88(buf); Sub_080068F0(buf, 2, 7, 25, 0).
 * Callees: F_080247C4 0x080247c4, Dispatch_24434 0x08024434,
 * Gfx_BlitRequest 0x08006a54 (UNLISTED, .set),
 * Sub_080241D0 0x080241d0, TblGetW_BB8C 0x080246a8,
 * Sub_08006DD8 0x08006dd8 (UNLISTED, .set),
 * F_08024F88 0x08024f88, Sub_080068F0 0x080068f0
 * (all MATCHED except 6a54/6dd8).
 * NOTE: 247C4/241D0 staged as returning int (real callees return
 * u8) — ROM caller truncates their returns with lsls/lsrs, so
 * the caller's prototypes must be 32-bit; flag for coordinator.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern int F_080247C4(int idx);
extern u32 Dispatch_24434(u16 a);
extern void Gfx_BlitRequest(u32 a, int b, int c, int d, int e);
extern int Sub_080241D0(int a);
extern u32 TblGetW_BB8C(u16 idx);
extern void Sub_08006DD8(int a, int b, int c, int d, int e);
__asm__(".set Sub_08006DD8, 0x08006dd8");
extern void F_08024F88(u8 *a);
__asm__(".set F_08024F88, 0x08024f88");
extern void Sub_080068F0(u8 *a, int b, int c, int d, int e);

__attribute__((section(".text.w38a_08035a24")))
void Sub_08035A24(void)
{
    u8 buf[48];
    u16 c7 = 0;
    u8 c6 = 0;
    u8 i;
    for (i = 1; i <= 243; i++) {
        u8 arg = i;
        u8 ret;
        if (i > 194)
            arg = (u8)(i + 5);
        ret = (u8)F_080247C4(arg);
        if (ret != 0) {
            c7 += ret;
            c6++;
        }
    }
    c7++;
    c6++;
    Gfx_BlitRequest(Dispatch_24434(4096), 2, 4, 4, 0);
    Gfx_BlitRequest(TblGetW_BB8C((u8)Sub_080241D0(4096)), 8, 4, 8, 0);
    Sub_08006DD8(c6, 17, 4, 3, 0);
    Gfx_BlitRequest(*(u32 *)0x0822E9AC, 20, 4, 1, 0);
    Sub_08006DD8(c7, 21, 4, 4, 0);
    Gfx_BlitRequest(*(u32 *)0x0822E9B4, 25, 4, 1, 0);
    F_08024F88(buf);
    Sub_080068F0(buf, 2, 7, 25, 0);
}
