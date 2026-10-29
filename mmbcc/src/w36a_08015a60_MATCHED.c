/* Wave 36-A MATCHED: 0x08015a60, 100 B, main agbcc, 4 variants.
   Extent basis: code 0x08015a60-0x08015abd (bx r0), pad 0x08015abe-0x08015abf, pool
   0x08015ac0 (0xffffc400) -> 0x08015ac4.
   Flag-init (arg0[14]), decrement arg0[18] via int temp so the store precedes the
   u8 truncation (ROM order: ldrb, subs, strb, lsls, lsrs); conditional calls on
   decremented value == 0. Pool value 0xffffc400 (LE bytes, not 0x00ffffc4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800DD2C(u8 *a, u32 b, u32 c);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0800D9EC(u8 *a, u32 b);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800D9FC(u8 *a);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
extern void Sub_08017464(u32 a);
__asm__(".set Sub_08017464, 0x08017464");
extern void Sub_08011F68(u8 *a, u32 b);
__asm__(".set Sub_08011F68, 0x08011f68");
__attribute__((section(".text.w36a_08015a60")))
void Sub_08015A60(u8 *arg0)
{
    u8 *r6 = arg0 + 124;
    u8 v;
    if (arg0[14] == 0) {
        arg0[14] = 1;
        Sub_0800DD2C(arg0, 0xffffc400, 0);
        Sub_0800D9EC(arg0, 0);
        arg0[18] = 20;
    }
    Sub_0800D9FC(arg0);
    {
        int t = arg0[18] - 1;
        arg0[18] = t;
        v = (u8)t;
    }
    if (v == 0) {
        Sub_08017464(*(u32 *)(arg0 + 44));
        *(u32 *)(arg0 + 44) = 0;
        Sub_0800DD2C(arg0, 0xffffc400, 0);
        r6[4] = 0;
        Sub_08011F68(arg0, 0);
    }
}
