/* Wave 20-D @0x0802611C (40 B). MATCHED with main agbcc.
 * Calls sub_080257BC(p + i*144, a) for i=0..2.
 */
typedef unsigned char u8;
typedef unsigned short u16;

extern void sub_080257BC(u8 *p, u16 x);

__attribute__((section(".text.w20d_0802611C")))
void F_0802611C(u8 *p, u16 a)
{
    u8 i;
    for (i = 0; i <= 2; i++) {
        sub_080257BC(p + i * 144, a);
    }
}
