/* Wave 36-A MATCHED: 0x08023110, 92 B, main agbcc, 9 variants.
   Extent basis: code 0x08023110-0x0802316b (bx r0), no pools, no pad -> 0x0802316c.
   Flag byte loaded once (r1), cleared via u32 temp pinned r0 (movs #9, negs, ands r0,r1);
   s[18] decrement branch; ldrsb loads via asm with offset in r0 itself (mov r0,#0/#1;
   ldrsb r0,[r5,r0]) since agbcc never emits ldrsb from C. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;
extern void Sub_0800D9EC(u32 *s, u32 a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800D9FC(u32 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w36a_08023110")))
void Sub_08023110(u32 *s)
{
    u8 *sub = (u8 *)s[10];
    u32 b = ((u8 *)sub)[31];
    register u32 t __asm__("r0");
    register s32 v0 __asm__("r0");
    register s32 v1 __asm__("r0");
    if (b & 8) {
        t = b & ~8;
        ((u8 *)sub)[31] = (u8)t;
        Sub_0800D9EC(s, 1);
        ((u8 *)s)[18] = 4;
    } else {
        if (((u8 *)s)[18] != 0) {
            ((u8 *)s)[18]--;
            if ((s8)((u8 *)s)[18] == 0)
                Sub_0800D9EC(s, 0);
        }
    }
    __asm__ volatile("mov r0, #0\n\tldrsb %0, [%1, r0]" : "=r"(v0) : "r"(sub));
    s[20] = (v0 + 7) * 2048;
    __asm__ volatile("mov r0, #1\n\tldrsb %0, [%1, r0]" : "=r"(v1) : "r"(sub));
    s[21] = v1 * 2048;
    Sub_0800D9FC(s);
}
