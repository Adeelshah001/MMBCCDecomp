/* Wave 36-A MATCHED: 0x0801db40, 92 B, main agbcc, 6 variants.
   Extent basis: code 0x0801db40-0x0801db97 (bx r0), pool 0x0801db98 (0x082243d8) -> 0x0801db9c.
   s pinned r2, sub pinned r3; copy via temps + barrier (prevents copy/add merge);
   sub[12] byte pinned r3 (sub dead after); table address via stmt-expr asm (pool first,
   byte in r3, shift into r0) with pool in trailing block; s[12]=2 stored between address
   computation and dereference. No trailing pad: extent ends with pool. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D9FC(u32 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w36a_0801db40")))
void Sub_0801DB40(u32 *s_in)
{
    register u32 *s __asm__("r2");
    register u32 *sub __asm__("r3");
    u32 t0, t1;
    u8 *p;
    u8 *tp;
    register u8 b12 __asm__("r3");
    s = s_in;
    sub = (u32 *)s[10];
    t0 = sub[20];
    t1 = sub[21];
    s[20] = t0;
    s[21] = t1;
    __asm__ volatile("" : : : "memory");
    s[20] += s[24];
    s[21] += s[25];
    if ((u8)(((u8 *)s)[119] - 3) <= 1) {
        b12 = ((u8 *)sub)[12];
        if (b12 <= 1) {
            p = (u8 *)s[11];
            (*p)++;
        }
        tp = ({ register u8 *addr __asm__("r0");
                __asm__ volatile(
                    "ldr r1, .Ldb40_tbl\n\t"
                    "ldrb r3, [%1, #9]\n\t"
                    "lsl %0, r3, #2\n\t"
                    "add %0, %0, r1\n\t"
                    : "=r"(addr) : "r"(s) : "r1", "r3");
                addr; });
        s[3] = 2;
        s[5] = *(u32 *)(*(u32 *)tp + 8);
    }
    Sub_0800D9FC(s);
}
__asm__(
    ".section .text.w36a_0801db40,\"ax\",%progbits\n\t"
    ".align 2\n"
    ".Ldb40_tbl: .word 0x082243d8\n\t");
