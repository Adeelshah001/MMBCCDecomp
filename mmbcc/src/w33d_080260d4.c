/* W33-D MATCHED: F_080260D4 @ 0x080260D4, 52 B. main agbcc.
 * Wall (W15-D): loop-top s16 extend hoist resists LICM.
 * Try volatile barrier to force the explicit (s16) extend.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void SetIfGt199(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w33d_080260d4")))
void F_080260D4(u8 *a0, u8 a1, u8 a2)
{
    s16 i = 0;
    do {
        SetIfGt199(a0 + (s32)i * 144, a1, a2);
        {
            s32 t = (s32)i + 1;
            __asm__ volatile("" : "+r" (t));
            i = (s16)t;
        }
    } while (i <= 2);
}
