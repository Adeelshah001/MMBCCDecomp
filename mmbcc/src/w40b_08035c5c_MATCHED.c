/* W39-A: 0x08035c5c, 328 B (TSV; next 0x08035da4).
 * for (u8 i=0; i<=3; i++) {
 *   f1 = s[i*12+289];
 *   if (f1) CondRectFill((u8)(i+27), 3, i*2+30, 4, 0);
 *   else if (s[i*12+288]) CondRectFill((u8)(i+27), 0, i*2+30, 4, f1);
 *   else CondRectFill(0, 0, i*2+30, 4, s[i*12+288]); }
 * for (u8 i=0; i<=3; i++) {
 *   if (s[i*12+336]) CondRectFill((u8)(i+22), (u8)MapTableVal(i),
 *       (s16)(i*2+30), 7, 0);
 *   else CondRectFill(0, 0, (s16)(i*2+30), 7, s[i*12+336]); }
 * Sub_35C1C(s);
 * Sub_6DD8(s[36] u16, 41, 7, 4, 0);
 * Blit(*(int*)0x0822e994, 45, 7, 1, 0);
 * Sub_6DD8(s[38] u16, 46, 7, 4, 0);
 * Blit(*(int*)0x0822e99c, 50, 7, 1, 0);
 * Sub_6DD8(SDiv(s[36]*100, s[38]+s[36]), 51, 7, 3, 0);
 * Blit(*(int*)0x0822e9a4, 54, 7, 1, 0);
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void CondRectFill_080073D4(u8 a, int b, int c, int d, int e);
extern u8 MapTableVal_499AC(int i);
extern void Sub_08035C1C(u8 *s);
extern void Sub_08006DD8(int a, int b, int c, int d, int e);
extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);
extern int SDiv_0804DD08(int a, int b);

__attribute__((section(".text.w40b_08035c5c")))
void Sub_08035C5C(u8 *s)
{
    u8 i;

    for (i = 0; i <= 3; i++) {
        u8 *p = s + i * 12;
        register int f1 __asm__("r3");
        __asm__ volatile("ldrb %0, [%1]" : "=r"(f1) : "r"(p + 289));
        if (f1)
            CondRectFill_080073D4((u8)(i + 27), 3, i * 2 + 30, 4, 0);
        else {
            u8 f2 = p[288];
            if (f2)
                CondRectFill_080073D4((u8)(i + 27), 0, i * 2 + 30, 4, f1);
            else
                CondRectFill_080073D4(0, 0, i * 2 + 30, 4, f2);
        }
    }
    for (i = 0; i <= 3; i++) {
        u8 *p = s + i * 12;
        u8 f = p[336];
        if (f)
            CondRectFill_080073D4((u8)(i + 22), MapTableVal_499AC(i), (s16)(i * 2 + 30), 7, 0);
        else
            CondRectFill_080073D4(0, 0, (s16)(i * 2 + 30), 7, f);
    }
    Sub_08035C1C(s);
    Sub_08006DD8(*(u16 *)(s + 36), 41, 7, 4, 0);
    Gfx_BlitRequest(*(int *)0x0822e994, 45, 7, 1, 0);
    Sub_08006DD8(*(u16 *)(s + 38), 46, 7, 4, 0);
    Gfx_BlitRequest(*(int *)0x0822e99c, 50, 7, 1, 0);
    Sub_08006DD8(SDiv_0804DD08(*(u16 *)(s + 36) * 100, *(u16 *)(s + 38) + *(u16 *)(s + 36)), 51, 7, 3, 0);
    Gfx_BlitRequest(*(int *)0x0822e9a4, 54, 7, 1, 0);
}

__asm__(".set Sub_08035C1C, 0x08035c1c");
__asm__(".set Sub_08006DD8, 0x08006dd8");
