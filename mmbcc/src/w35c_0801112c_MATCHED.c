/* Wave 35-C v1: 0x0801112c — (s16) limit loop with (u8) workers */
typedef unsigned char u8;
typedef short s16;
extern s16 Worker_08016F98(u8 a);
extern u8 Worker_08016FAC(u8 a, u8 i);
extern void Worker_08002C24(u8 v);
__asm__(".set Worker_08016F98, 0x08016f98");
__asm__(".set Worker_08016FAC, 0x08016fac");
__asm__(".set Worker_08002C24, 0x08002c24");
__attribute__((section(".text.w35c_0801112c")))
void Sub_0801112C(u8 a)
{
    s16 n = Worker_08016F98(a);
    s16 i;
    if (n <= 0)
        return;
    for (i = 0; i < n; i++)
        Worker_08002C24((u8)Worker_08016FAC(a, (u8)i));
}
