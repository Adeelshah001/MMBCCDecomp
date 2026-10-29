/* Wave 22-D @0x08010F34 (84 B incl. 4 B mid-function pool). MATCHED, main agbcc.
 * Entry_TryActivate_08010F34(a, b, c): if bit a of tbl[3] (u8 @0x020051B0)
 * is set and the 12 B entry (tbl+24+a*12) is inactive, fill it with
 * {2,?,b,?,?,c,0,...} and return 1, else return 0.
 *
 * Idioms: bit test via inline asm (`ldrb r0,[r2,#3]; asr r0,r3` -- neither
 * gcc emits ROM's shape from C: main adds lsl/asr extends, old uses ldrsb;
 * the & 1 makes signed/unsigned shift identical); tbl pinned r2 + barrier
 * against pool folding (else tbl+24 folds to a 0x020051C8 pool word); base
 * pinned r1 (adds r1,r2,#0; adds r1,#24); `(u32)a12 + (u32)base` order for
 * ROM's adds r4,r0,r1; store constants via u32 pins (r1=0, r0=2) forcing
 * ROM's movs-first-then-stores order. NOTE: pre-UAL GAS wants `asr`, not
 * `asrs` (objdump UAL display misleads).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern s8 sub_08010FB4(u8 a);

__attribute__((section(".text.w22d_08010F34")))
u8 Entry_TryActivate_08010F34(u8 a, u8 b, u8 c)
{
    register u8 *tbl __asm__("r2") = (u8 *)0x020051B0;
    u32 shifted;
    int a12;
    u8 *e;

    /* ROM: ldrb r0,[r2,#3]; asrs r0,r3 */
    __asm__ volatile(
        "ldrb %0, [%1, #3]\n\t"
        "asr %0, %2"
        : "=&r" (shifted)
        : "r" (tbl), "r" ((u32)a)
    );
    if ((shifted & 1) == 0)
        return 0;
    a12 = a * 12;
    __asm__ volatile("" : "+r" (tbl));   /* barrier against pool folding */
    {
        register u8 *base __asm__("r1") = tbl;  /* adds r1, r2, #0 */
        base += 24;                             /* adds r1, #24 */
        e = (u8 *)((u32)a12 + (u32)base); /* adds r4, r0, r1 */
    }
    if (sub_08010FB4(a) != 1)
        return 0;
    {
        register u32 z __asm__("r1") = 0;   /* movs r1, #0 */
        register u32 t __asm__("r0") = 2;   /* movs r0, #2 */
        e[0] = (u8)t;
        e[6] = (u8)z;
        e[2] = b;
        e[5] = c;
    }
    return 1;
}
