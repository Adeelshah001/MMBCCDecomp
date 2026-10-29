/* Wave 36-B MATCHED: 0x08007798, 128 B, old_agbcc -O2 -mthumb-interwork, 0 diffs. Callees via harness symdefs (both BLOCKED in registry). Variants: 6. Idioms: barrier-kept table pointers, idx-first add, split addr computation to order pool load between adds and byte load. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;
extern void Sub_08006374(u8 *ctx, s8 a, s8 b, int c, int d, int e, u8 f, u32 g);
extern void Sub_08006124(s8 a, s8 b, int c, int d, int e, u8 f);
__attribute__((section(".text.w36bulk_08007798")))
void Sub_08007798(u8 a, u8 b, u8 c, u8 d)
{
    if (d != 0) {
        u8 *tblA = (u8 *)0x08172074;
        u32 idx;
        u32 r4;
        __asm__ volatile("" : "+r"(tblA));
        idx = ((*(u32 *)0x02003670 >> 3) & 3);
        tblA += 4;
        {
            u8 *addr = (u8 *)(idx + (u32)tblA);
            u8 *tblB = (u8 *)0x08170e7c;
            u8 byte;
            __asm__ volatile("" : "+r"(tblB));
            byte = *addr;
            r4 = *(u32 *)(tblB + byte * 4);
        }
        Sub_08006374((u8 *)0x0200483c, (s8)(a - 2), (s8)b, 2, 2, 53, c, r4);
    } else {
        Sub_08006124((s8)(a - 2), (s8)b, 2, 2, 50, c);
    }
}

__asm__(".set Sub_08006124, 0x08006124");
__asm__(".set Sub_08006374, 0x08006374");
