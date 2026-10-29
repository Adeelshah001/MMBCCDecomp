/* Wave 36-A MATCHED: 0x0800b470, 88 B, main agbcc, 6 variants.
   Extent basis: code 0x0800b470-0x0800b4c5 (bx), pad 0x0800b4c6-0x0800b4c7 (00 00).
   Switch on (s[21] & 0xf) via shift-mask; r5 pool 0x02004e40 at 0x0800b48c, table-base
   pool (0x0800b494) at 0x0800b490, 5-entry table at 0x0800b494. Cases 1/3 share the
   7de8 handler, cases 2/4 share the 7c04 fall-through handler. Byte pinned r1,
   switch value pinned r0 to reproduce ldrb r1 / lsls r0,r1 / lsrs r0,r0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_08007DE8(u32 a, u32 b);
__asm__(".set Sub_08007DE8, 0x08007de8");
extern void Sub_08007C04(u32 a, u32 b);
__asm__(".set Sub_08007C04, 0x08007c04");
__attribute__((section(".text.w36a_0800b470")))
void Sub_0800B470(u16 idx)
{
    u8 *s = (u8 *)0x02004e40;
    register u8 b __asm__("r1");
    register u32 v __asm__("r0");
    b = s[21];
    v = ((u32)b << 28) >> 28;
    switch (v) {
    case 0:
        idx = 0;
        break;
    case 1:
    case 3:
        Sub_08007DE8(idx, 0);
        break;
    case 2:
    case 4:
        Sub_08007C04(idx, 0);
    default:
        break;
    }
    *(u16 *)(s + 6) = idx;
}
/* Explicit 00 00 pad: ROM has 00 00 after bx; GAS would otherwise emit a c0 46 nop. */
__asm__(".section .text.w36a_0800b470,\"ax\",%progbits\n\t.hword 0\n\t");
