/* Wave 36-A MATCHED: 0x080429e0, 88 B, main agbcc, 2 variants.
   Extent basis: code 0x080429e0-0x08042a35 (bx r1), pad 0x08042a36-0x08042a37 (00 00).
   Loop over i=1..9 (u8): if (u8)Sub_080242A8(4096,i)!=0, acc=(u16)(acc+Sub_08024634(c))
   with c the u8 temp (forces lsls+lsrs #24) passed as the 24634 arg. Post-loop:
   y=Sub_08024634((u8)Sub_080241D0(4096)) as u32 (no truncation), r=(u16)(y+Sub_08024F08(y)),
   r=(u16)(r-acc), return r. File-scope 00 00 pad. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 Sub_080242A8(u32 a, u32 b);
__asm__(".set Sub_080242A8, 0x080242a8");
extern u32 Sub_08024634(u32 a);
__asm__(".set Sub_08024634, 0x08024634");
extern u32 Sub_080241D0(u32 a);
extern u32 Sub_08024F08(u32 a);
__asm__(".set Sub_08024F08, 0x08024f08");
__attribute__((section(".text.w36a_080429e0")))
u16 Sub_080429E0(void)
{
    u16 acc = 0;
    u8 i;
    u8 c;
    u8 t;
    u32 y;
    u16 r;
    for (i = 1; i <= 9; i++) {
        c = (u8)Sub_080242A8(4096, i);
        if (c != 0)
            acc = (u16)(acc + Sub_08024634(c));
    }
    t = (u8)Sub_080241D0(4096);
    y = Sub_08024634(t);
    r = (u16)(y + Sub_08024F08(y));
    r = (u16)(r - acc);
    return r;
}
/* Explicit 00 00 pad: ROM has 00 00 after bx; GAS would otherwise emit a c0 46 nop. */
__asm__(".section .text.w36a_080429e0,\"ax\",%progbits\n\t.hword 0\n\t");
