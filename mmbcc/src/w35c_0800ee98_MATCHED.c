/* Wave 35-C v4: 0x0800ee98 — explicit shifted increment to match ROM loop */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int Worker_08010508(int a);
extern void Worker_0801052C(int a);
extern void Worker_08010724(void *p);
extern void Worker_08010ACC(void *p);
__asm__(".set Worker_08010508, 0x08010508");
__asm__(".set Worker_0801052C, 0x0801052c");
__asm__(".set Worker_08010724, 0x08010724");
__asm__(".set Worker_08010ACC, 0x08010acc");
__attribute__((section(".text.w35c_0800ee98")))
void Sub_0800EE98(void)
{
    u8 *base = (u8 *)0x02005160;
    u8 *q = base;
    u16 i = 0;
    while (1) {
        *q++ = 0;
        __asm__ volatile("lsl %0, %0, #16\n\tmovs r3, #128\n\tlsl r3, r3, #9\n\tadd %0, %0, r3\n\tlsr %0, %0, #16" : "+r"(i) :: "r3");
        if (i > 75)
            break;
    }
    Worker_0801052C(Worker_08010508(0));
    Worker_08010724(base);
    Worker_08010ACC(base);
}
