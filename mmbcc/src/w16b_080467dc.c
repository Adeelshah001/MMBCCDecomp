/* Wave 16 worker B: 0x080467DC (52 B).
 * Counts non-zero F_080247C4(idx) for i=1..243, idx=i+(i>194?5:0).
 */
typedef unsigned char u8;
typedef unsigned short u16;


extern u16 F_080247C4(u8 idx);
u16 F_080247C4(u8 idx);

u8 Count_467DC(void) __attribute__((section(".text.w16b_080467dc")));
u8 Count_467DC(void)
{
    u8 n = 1;
    u8 i = 1;
    do {
        u8 idx = i;
        u16 v;
        if (i > 194)
            idx = i + 5;
        v = F_080247C4(idx);
        if (v)
            n++;
        i++;
    } while (i <= 243);
    return n;
}

