/* Wave 15-C: Fwd_08000630 @ 0x08000630 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void F_08002F4C(void);

void Fwd_08000630(void) __attribute__((section(".text.w15c1_08000630")));
void Fwd_08000630(void) { F_08002F4C(); }

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl F_08002F4C\n"
    ".set F_08002F4C, 0x08002F4C\n"
);
