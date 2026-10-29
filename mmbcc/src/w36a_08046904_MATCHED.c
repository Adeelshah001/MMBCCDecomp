/* Wave 36-A MATCHED: 0x08046904, 92 B, main agbcc, 4 variants.
   Extent basis: code 0x08046904-0x0804695b (bx r0), pool 0x0804695c (0x0200b7a8)
   -> 0x08046960.
   16-byte zero loop with u16 increment trick (lsls #16, movs r6=#128, lsls #9,
   adds, lsrs #16) and unsigned compare (bls); s16 counter with (u16) comparison
   gives the trick + bls. Prologue order: counter init before m92 computation. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern void Sub_08046CA0(u8 *a, u8 *b, u32 c, u32 d);
__asm__(".set Sub_08046CA0, 0x08046ca0");
extern void Sub_08004E44(void);
__asm__(".set Sub_08004E44, 0x08004e44");
extern void Sub_08004DFC(u32 a);
__asm__(".set Sub_08004DFC, 0x08004dfc");
extern void Sub_0800BEE0(u32 a, u32 b);
__asm__(".set Sub_0800BEE0, 0x0800bee0");
extern void Sub_08002FC4(u32 a);
__asm__(".set Sub_08002FC4, 0x08002fc4");
extern void Sub_08046960(u8 *a);
__asm__(".set Sub_08046960, 0x08046960");
__attribute__((section(".text.w36a_08046904")))
void Sub_08046904(u8 *arg0)
{
    u8 *pool = (u8 *)0x0200b7a8;
    u8 *p = pool;
    s16 i;
    u8 *m92;
    i = 0;
    m92 = pool - 92;
    for (; (u16)i <= 15; i++) {
        *p++ = 0;
    }
    Sub_08046CA0(pool + 4, m92, 4, 0);
    Sub_08004E44();
    Sub_08004DFC(2);
    Sub_0800BEE0(63, 128);
    arg0[2]++;
    Sub_08002FC4(3);
    Sub_08046960(arg0);
}
