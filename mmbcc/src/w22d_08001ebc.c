/* Wave 22-D @0x08001EBC (90 B code + 2 pad; both pools interior).
 * MATCHED with main agbcc.
 * Sram_TryInitSlot_08001EBC(a, b, c): if (a > 1 || S[0] != 0 ||
 * Sram_VerifySlot(a, c) == 0 || c > 0x2010) return -1; else init the
 * 0x02002F80 struct {S[1]=a, S[8]=b, S[20]=c, S[30]=S[0](=0), S[0]=1,
 * S[2]=2} and return 0.
 * Idioms: S assignment placed after the a>1 check (else gcc hoists the
 * ldr before the bhi); *(u16*)(S+30) = s0 reuses r6 (the S[0] local)
 * instead of a fresh zero; explicit `.byte 0, 0` section pad (linker
 * pads with c0 46, ROM has 00 00). r8 used for b (5th lo callee-saved
 * reg exhausted: S->r4, c->r5, s0->r6, a->r7).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern u32 Sram_VerifySlot(u32 a0, u32 key);

__attribute__((section(".text.w22d_08001EBC")))
s32 Sram_TryInitSlot_08001EBC(u8 a, u32 b, u32 c)
{
    register u8 *S __asm__("r4");
    u8 s0;

    if (a > 1)
        return -1;
    S = (u8 *)0x02002F80;
    s0 = S[0];
    if (s0 != 0)
        return -1;
    if (Sram_VerifySlot(a, c) == 0)
        return -1;
    if (c > 0x2010)
        return -1;
    S[1] = a;
    *(u32 *)(S + 8) = b;
    *(u32 *)(S + 20) = c;
    *(u16 *)(S + 30) = s0;
    S[0] = 1;
    *(u16 *)(S + 2) = 2;
    return 0;
}

/* Explicit 2-byte pad: ROM has 00 00 after the 90 B code, but the linker
 * pads with c0 46. */
__asm__(
    ".section .text.w22d_08001EBC,\"ax\",%progbits\n\t"
    ".byte 0, 0\n\t"
    ".previous"
);
