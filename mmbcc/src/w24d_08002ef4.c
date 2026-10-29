typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void F_0804C630(void);
/* Link-time constant anchor: absolute symbol at 0x0.
   (u32)&gAddrZero[0xAA] is NOT foldable at compile time, so agbcc is forced
   to emit it as a literal-pool word (with reloc); after linking it is
   exactly 0x000000AA. Proven: every pure-constant spelling of 0xAA
   compiles to `movs r0,#170` under agbcc/old_agbcc -O2 (brute-forced). */
__asm__(
    ".set gAddrZero, 0x0\n"
    ".set F_0804C630, 0x0804C630\n"
);
extern u8 gAddrZero[];

__attribute__((section(".text.w24d_08002ef4")))
void F_08002EF4(void)
{
    register u32 *pa __asm__("r1");
    register u32 va __asm__("r0");
    register u8 *p __asm__("r0");
    F_0804C630();
    __asm__ volatile("" : "=r" (pa) : "0" (0x02003244));
    __asm__ volatile("" : "=r" (va) : "0" ((u32)&gAddrZero[0xAA]));
    *pa = (u16)va;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000818));
    *p = 0;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000819));
    *p = 0;
}
