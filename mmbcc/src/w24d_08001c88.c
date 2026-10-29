typedef unsigned char u8;

/* sub_08001ca8 is BLOCKED (unmatched) -- absolute-symbol stub per the
   extern-absolute-symbol idiom. */
__asm__(
    ".set sub_08001ca8, 0x08001CA8\n"
);
void sub_08001ca8(u8 *p, int i);

__attribute__((section(".text.w24d_08001c88")))
void F_08001C88(void)
{
    int i = 0;
    u8 *p = (u8 *)0x02002F50;
    do {
        sub_08001ca8(p, i);
        p += 24;
        i++;
    } while (i <= 1);
}
