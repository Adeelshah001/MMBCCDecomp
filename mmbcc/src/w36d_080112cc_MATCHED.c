/* Wave 36-D v4 (file-scope pad): 0x080112cc — for loop, s8 worker result. */
typedef unsigned char u8;
typedef signed char s8;
extern s8 Worker_08010FB4(u8 i);
__asm__(".set Worker_08010FB4, 0x08010fb4");
__attribute__((section(".text.w36d_080112cc")))
int Sub_080112CC(void)
{
    int found = 0;
    s8 i;
    for (i = 0; i <= 6; i++) {
        if (Worker_08010FB4((u8)i) != 1)
            found = 1;
    }
    return found;
}
__asm__(".short 0x0000");
