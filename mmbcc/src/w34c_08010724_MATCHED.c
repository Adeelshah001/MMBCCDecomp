/* Wave 34-C v1: 0x08010724 — 7-arg call: W(0,19,30,1, 0x0000020d, 5, *(0x08173e28)). */
typedef unsigned int u32;

extern void Worker_080062B4(int a, int b, int c, int d, void *e, int f, u32 g);
__asm__(".set Worker_080062B4, 0x080062b4");

__attribute__((section(".text.w34c_08010724")))
void Sub_08010724(void)
{
    Worker_080062B4(0, 19, 30, 1, (void *)0x0000020d, 5, *(u32 *)0x08173e28);
}
