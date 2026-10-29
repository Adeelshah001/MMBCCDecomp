/* Wave 34-C v1: 0x0804afac — r=(s8)worker(s+1,1); if (!r) { s[0]++; s[1]=r; } return 0.
 * New idiom: inline-asm lsl/asr pair (GAS wants unsuffixed) (agbcc's s8 split-alloc emits lsr+cmp r0;
 * ROM has asrs r1 + cmp r1). 6 C variants + old_agbcc exhausted first. */
typedef unsigned char u8;

extern int Worker_08028778(u8 *p, int one);
__asm__(".set Worker_08028778, 0x08028778");

__attribute__((section(".text.w34c_0804afac")))
int Sub_0804AFAC(u8 *s)
{
    int t = Worker_08028778(s + 1, 1);
    int r;
    __asm__ volatile("lsl %1, %1, #24\n\tasr %0, %1, #24" : "=r"(r), "+r"(t));
    if (r == 0)
    {
        s[0]++;
        s[1] = r;
    }
    return 0;
}
