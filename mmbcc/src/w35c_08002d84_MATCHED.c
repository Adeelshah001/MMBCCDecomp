/* Wave 35-C v3: 0x08002d84 — volatile C[2] reload */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_08002DCC(u32 v);
__asm__(".set Worker_08002DCC, 0x08002dcc");
__attribute__((section(".text.w35c_08002d84")))
void Sub_08002D84(void)
{
    register u32 A __asm__("r1") = 0x03002830;
    u32 *C;
    u32 tmp;
    __asm__ volatile("" : "+r"(A));
    *(u32 *)(A + 1028) = (128 << 5);
    *(u32 *)(A + (128 << 3)) = A;
    tmp = (128 << 2);
    C = (u32 *)0x040000d4;
    C[0] = (u32)&tmp;
    C[1] = A;
    C[2] = 0x85000100;
    Worker_08002DCC(*(volatile u32 *)&C[2]);
}
