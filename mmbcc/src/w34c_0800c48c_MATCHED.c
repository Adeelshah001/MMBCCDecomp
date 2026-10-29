/* Wave 34-C v1: 0x0800c48c — if (x) { W(0,1); if (s[26]) V(s+32); } */
typedef unsigned char u8;

extern void W_08005274(int x, int y, int z);
extern void V_0800E144();
__asm__(".set W_08005274, 0x08005274");
__asm__(".set V_0800E144, 0x0800e144");

__attribute__((section(".text.w34c_0800c48c")))
void Sub_0800C48C(u8 *s, int x)
{
    int xx = x;
    if (xx == 0)
        return;
    W_08005274(xx, 0, 1);
    if (s[26] == 0)
        return;
    V_0800E144(s + 32);
}
__asm__(".short 0x0000");
