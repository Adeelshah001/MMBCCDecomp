/* Wave 36-B MATCHED: 0x08024c40, 128 B, old_agbcc, code 0-diff; trailing 2 B are GAS c046 pad (ROM 00 00) - explicit pad object at landing per precedent. Callees via harness symdefs (5a64 unmatched -> .set). Variants: 3. Idioms: block-local base reload, literal 432 CSE into r6, arg copy r7. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
extern int Sub_080258D8(u8 *p, u8 arg);
extern int Sub_08025A64(u8 *p, u8 arg);
extern int Sub_080258F8(u8 *p, u8 arg);
extern int Sub_08025A10(u8 *p, u8 arg);
__attribute__((section(".text.w36bulk_08024c40")))
u16 Sub_08024C40(u8 *s, u8 arg)
{
    u8 *sp = s;
    u8 arg2 = arg;
    u8 t;
    {
        u32 b = *(u32 *)(sp + 20);
        t = Sub_080258D8((u8 *)(b + *(u8 *)(b + 432) * 144), arg);
    }
    if (t == 0)
        return 0;
    if (t == 2) {
        u8 r;
        {
            u32 b = *(u32 *)(sp + 20);
            r = Sub_080258F8((u8 *)(b + *(u8 *)(b + 432) * 144), arg2);
        }
        {
            u32 b = *(u32 *)(sp + 20);
            return Sub_08025A10((u8 *)(b + *(u8 *)(b + 432) * 144), r);
        }
    }
    {
        u32 b = *(u32 *)(sp + 20);
        return Sub_08025A64((u8 *)(b + *(u8 *)(b + 432) * 144), arg);
    }
}

__asm__(".set Sub_080258D8, 0x080258d8");
__asm__(".set Sub_080258F8, 0x080258f8");
__asm__(".set Sub_08025A10, 0x08025a10");
__asm__(".set Sub_08025A64, 0x08025a64");
