/* Wave 15-C: Fwd_0804C814 @ 0x0804c814 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void ClearSignBit(void);

void Fwd_0804C814(void) __attribute__((section(".text.w15c1_0804C814")));
void Fwd_0804C814(void) { ClearSignBit(); }

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl ClearSignBit\n"
    ".set ClearSignBit, 0x0804C5F4\n"
);
