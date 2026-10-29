/* Wave 36-B MATCHED: 0x08021c2c, 128 B, old_agbcc, 0 diffs. Variants: 3. Idioms: decl order i/t2/t1, split bv/w, idx-first ep add, barrier table pointers for pool-before-shift order. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
extern void Sub_08002300(u8 *p, int v);
extern void Sub_08002904(u8 *p, int a, u8 b);
__attribute__((section(".text.w36bulk_08021c2c")))
void Sub_08021C2C(void)
{
    short i = 0;
    u32 *t2 = (u32 *)0x08173760;
    u16 *t1 = (u16 *)0x08227104;
    for (i = 0; i <= 7; i++) {
        u16 *ep = (u16 *)((i * 2) + (u32)t1);
        u16 v = *ep;
        u32 bv = t2[v];
        u16 w = ((u16 *)0x08227114)[i];
        u8 *q = (u8 *)(bv + w * 4);
        q = (u8 *)((u32)q + *(u32 *)q);
        {
            u16 *t4 = (u16 *)0x0817386c;
            __asm__ volatile("" : "+r"(t4));
            Sub_08002300(q, t4[v] * 32 + 0x10000);
        }
        q = (u8 *)q + 12;
        {
            u8 *t5 = (u8 *)0x081738f2;
            __asm__ volatile("" : "+r"(t5));
            Sub_08002904(q, 0, t5[*ep * 2]);
        }
    }
}

__asm__(".set Sub_08002300, 0x08002300");
__asm__(".set Sub_08002904, 0x08002904");
