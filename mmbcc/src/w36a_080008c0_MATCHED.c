typedef unsigned int u32;

extern void sub_08000a1c(void);
extern void sub_08000ad4(void);

__attribute__((section(".text.w36a_080008c0")))
void Shift_080008c0(void)
{
    u32 *B = (u32 *)0x03000580;
    B[-6] = B[-3];
    B[-5] = B[-2];
    B[-4] = B[-1];
    B[-1] = 0;
    sub_08000a1c();
    B[0] = B[4];
    B[1] = B[5];
    B[2] = B[6];
    B[6] = 0;
    B += 7;
    B[0] = B[4];
    B[1] = B[5];
    B[2] = B[6];
    B[6] = 0;
    sub_08000ad4();
}

__asm__(".set sub_08000a1c, 0x08000a1c");
__asm__(".set sub_08000ad4, 0x08000ad4");
