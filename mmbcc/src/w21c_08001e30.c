/* Wave21 worker C @0x08001E30 (66 B code + 2 B 00 inter-function fill).
 * Sram register-pressure: ROM holds a in r6 (lsls/lsrs zero-extend into r6)
 * and 0xE0000000 in r5 (movs #0xE0; lsls #20) across two Sram_RetryWrapper
 * calls; st in r4. Idioms: pin au->r6 + st->r4 + base->r5 (all pushed
 * callee-saved; safe per w20-C), pin-one-forces-another (w20-B), sh1 temp
 * hoists (au<<13) above base's init. FIXALIGN1 (no c046 pad; the 00 00 at
 * 0x1E72 is inter-function fill).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *Sram_RetryWrapper(u8 *dst, u8 *src, u32 len);
__attribute__((section(".text.w21c_08001e30")))
int Sram_08001E30(u8 a)
{
    register u32 au __asm__("r6") = a;
    u32 tmp = 0;
    register int st __asm__("r4");
    u32 sh1;
    if (au > 1)
        return -1;
    sh1 = au << 13;
    {
        register u32 base __asm__("r5") = ((u32)0xE0 << 20);
        st = (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(sh1 + base), 4);
        st |= (int)Sram_RetryWrapper((u8 *)&tmp, (u8 *)(((au + 2) << 13) + base), 4);
    }
    return st;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
