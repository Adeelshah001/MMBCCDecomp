/* Wave 36-B MATCHED: 0x0801dd48, 124 B, old_agbcc -O2 -mthumb-interwork, 0 diffs. Callee ChipSlot_Tick Sub_0800D9FC via harness symdef (MATCHED registry). Variants: 9. Idioms: <=-form block order, load-both-then-store-both, barrier-forced reload sum in r4, two-step t=q;t+=35, ep pinned r0 with off-first add. */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_0800D9FC(u8 *o);
__attribute__((section(".text.w36bulk_0801dd48")))
void Sub_0801DD48(u8 *o)
{
    u8 *q = *(u8 **)(o + 40);
    if (o[13] == 0) {
        if (q[12] <= 1) {
            int sum;
            u32 a = *(u32 *)(q + 80);
            u32 b = *(u32 *)(q + 84);
            *(u32 *)(o + 80) = a;
            *(u32 *)(o + 84) = b;
            __asm__ volatile("" : "+r"(o));
            sum = *(int *)(o + 80) + *(int *)(o + 96);
            *(int *)(o + 80) = sum;
            *(int *)(o + 84) += *(int *)(o + 100);
            {
                u8 *t = q;
                t += 35;
                if ((t[0] & 15) == 1)
                    *(int *)(o + 80) = -sum;
            }
        } else {
            o[13]++;
        }
    }
    if ((u8)(o[119] - 3) <= 1) {
        u8 *p = *(u8 **)(o + 44);
        (*p)++;
        __asm__ volatile("" ::: "memory");
        {
            u32 *tbl = (u32 *)0x082243d8;
            register u32 *ep __asm__("r0");
            u32 off;
            __asm__ volatile("" : "+r"(tbl));
            off = o[9] * 4;
            ep = (u32 *)(off + (u32)tbl);
            *(u32 *)(o + 12) = 2;
            *(u32 *)(o + 20) = *(u32 *)(*ep + 8);
        }
    }
    Sub_0800D9FC(o);
}

__asm__(".set Sub_0800D9FC, 0x0800d9fc");
