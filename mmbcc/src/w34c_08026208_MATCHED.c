/* Wave 34-C v1: 0x08026208 — two Worker_08025230 calls with offset arithmetic. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_08025230(u8 *a, u8 *b, int c);
__asm__(".set Worker_08025230, 0x08025230");

__attribute__((section(".text.w34c_08026208")))
void Sub_08026208(u8 *s, u8 *t)
{
    u8 *aa = s;
    u8 *bb = t;
    u32 off = 224 << 4;
    Worker_08025230(s + 8, bb + off, 130);
    aa += 16;
    bb += 0xe82;
    Worker_08025230(aa, bb, 130);
}
