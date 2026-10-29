/* Wave 35-C v2: 0x080110e0 — unsigned shift for the b term */
typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;
extern s16 Worker_08016F98(u8 a);
extern u8 Worker_08016FAC(u8 a, u8 i);
extern void Worker_08002AFC(u8 v, int w);
__asm__(".set Worker_08016F98, 0x08016f98");
__asm__(".set Worker_08016FAC, 0x08016fac");
__asm__(".set Worker_08002AFC, 0x08002afc");
__attribute__((section(".text.w35c_080110e0")))
void Sub_080110E0(u8 a, u8 b)
{
    s16 n = Worker_08016F98(a);
    s16 i;
    if (n <= 0)
        return;
    for (i = 0; i < n; i++)
        Worker_08002AFC((u8)Worker_08016FAC(a, (u8)i), ((u32)b << 21) >> 16);
}
