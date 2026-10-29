/* Wave 15-C: SetFlag_0800EB24 @ 0x0800eb24 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void SetByte20_Clear21to23_0800E1F0(u8 x);

void SetFlag_0800EB24(void) __attribute__((section(".text.w15c1_0800EB24")));
void SetFlag_0800EB24(void) { SetByte20_Clear21to23_0800E1F0(3); }

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
);
