/* w50b 0x0801EBD0 v11 — r1-pinned index, idx += base (dest = index reg).
 * Base unpinned + barrier (v5 order); no function-wide r2 pin. */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w50b_0801ebd0")))
void Func_0801EBD0(u8 *s) {
    u32 **base = (u32 **)0x082243D8;
    register u32 idx __asm__("r1");
    u32 *slot;
    s[10] &= 0xFE;
    __asm__ volatile("" : "+r"(base));
    idx = (u32)(s[9] << 2);
    idx += (u32)base;
    slot = (u32 *)idx;
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = ((u32 *)*slot)[4];
}
