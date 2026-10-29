/* W37-C MATCHED: 0x0804cb28, 164 B, old_agbcc, pure C, 0 diffs. HW
 * register setup on u32 keys.
 * p = *(u32**)0x03007ff0; t = (keys & 0xF0000) >> 16; z = 0;
 * p[8] = t; p[16] = *(u16*)(0x08105e3c + (t-1)*2);
 * p[11] = SDiv(1584, p16); v = SDiv(0x91d1b * p16 + 5000, 10000);
 * p[20] = v; p[24] = (SDiv(0x1000000, v) + 1) / 2;
 * *(u16*)0x04000102 = z; *(u16*)0x04000100 = -SDiv(0x44940, p16);
 * Sub_0804CD34(); while (*(u8*)0x04000006 == 159) ;
 * while (*(u8*)0x04000006 != 159) ; *(u16*)0x04000102 = 128.
 * Extern callees + addresses: SDiv_0804DD08 0x0804dd08 (ASM),
 * Sub_0804CD34 0x0804cd34 (BLOCKED, .set).
 * Pools (LE): 0x03007ff0, 0x08105e3c, 0x91d1b, 0x1388, 0x2710,
 * 0x04000102, 0x04000100, 0x44940, 0x04000006.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern s32 SDiv_0804DD08(s32 a, s32 b);
extern void Sub_0804CD34(void);
__asm__(".set Sub_0804CD34, 0x0804cd34");

__attribute__((section(".text.w37c_0804cb28")))
void Sub_0804CB28(u32 keys)
{
    u8 *p;
    register u32 k __asm__("r2");
    register u32 t __asm__("r2");
    u16 z;
    u16 p16;
    s32 v;
    register u32 tm __asm__("r0");
    u16 *dst;
    u8 *tbl;
    k = keys;
    __asm__ volatile("" : "+r"(k));
    p = *(u8 **)0x03007ff0;
    t = (k & 0xF0000) >> 16;
    z = 0;
    p[8] = (u8)t;
    tbl = (u8 *)0x08105e3c;
    tm = t - 1;
    __asm__ volatile("" : "+r"(tm));
    p16 = *(u16 *)(tbl + tm * 2);
    *(u32 *)(p + 16) = p16;
    p[11] = (u8)SDiv_0804DD08(1584, p16);
    v = SDiv_0804DD08(0x91d1b * p16 + 5000, 10000);
    *(u32 *)(p + 20) = v;
    *(u32 *)(p + 24) = (SDiv_0804DD08(0x1000000, v) + 1) >> 1;
    *(u16 *)0x04000102 = z;
    dst = (u16 *)0x04000100;
    *dst = (u16)-SDiv_0804DD08(0x44940, p16);
    Sub_0804CD34();
    while (*(volatile u8 *)0x04000006 == 159)
        ;
    while (*(volatile u8 *)0x04000006 != 159)
        ;
    *(u16 *)0x04000102 = 128;
}
