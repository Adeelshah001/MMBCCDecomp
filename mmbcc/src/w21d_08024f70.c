/* Wave 21-D @0x08024F70 (20 B code + 4 B pool). MATCHED with main agbcc.
 * F_08024F70: calls Loop3_08026144(((u8 **)0x02007090)[5], a).
 *
 * Idioms: empty-asm barrier on the pool base prevents gcc from folding
 * base+20 into the pool constant (ROM pools 0x02007090 and uses
 * ldr r0, [r0, #20]).
 */
typedef unsigned char u8;
typedef unsigned short u16;

extern void Loop3_08026144(u8 *p, u16 a);

__attribute__((section(".text.w21d_08024F70")))
void F_08024F70(u16 a)
{
    u8 **base = (u8 **)0x02007090;
    u8 *p;
    __asm__ volatile ("" : "+r" (base));
    p = base[5];
    Loop3_08026144(p, a);
}
