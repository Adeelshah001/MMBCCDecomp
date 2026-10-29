/* Wave 36-B MATCHED: 0x08045fcc, 108 B, old_agbcc -O2 -mthumb-interwork, pure C.
   Extent basis: next function start 0x08046038 (func_list v2) - 0x08045fcc = 108,
   incl. 12 B literal pool (0x02004830, 618, 619).
   Variant count: 3 (v3 = base pointer variable declared after the value call,
   so gcc keeps base + index loads unfolded; v2 folded base+index into pool
   constants and came out 8 B short).
   Key idioms: switch with case-0 fallthrough into case 1 (compare chain,
   default jumps to return); arr[618]/arr[619] stores via base + pool-index
   adds; case-1 test on the shifted byte only (lsl + cmp, no lsr).
   Callees: Sub_08005A9C + Sub_080467DC + Sub_08046038 + Sub_080460C0 +
   Sub_080466AC + Sub_08046810 + Sub_080462A8 via .set (all unmatched;
   0x08046038 is the next function).
   Harness: ./verify.sh 0x08045fcc 108 .text.w36b_08045fcc
   w36b_08045fcc_MATCHED.c old -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_08005A9C(int x);
__asm__(".set Sub_08005A9C, 0x08005a9c");
extern u8 Sub_080467DC(u8 *p);
__asm__(".set Sub_080467DC, 0x080467dc");
extern void Sub_08046038(u8 *p);
__asm__(".set Sub_08046038, 0x08046038");
extern void Sub_080460C0(u8 *p);
__asm__(".set Sub_080460C0, 0x080460c0");
extern void Sub_080466AC(u8 *p);
__asm__(".set Sub_080466AC, 0x080466ac");
extern void Sub_08046810(u8 *p);
__asm__(".set Sub_08046810, 0x08046810");
extern u8 Sub_080462A8(u8 *p);
__asm__(".set Sub_080462A8, 0x080462a8");
__attribute__((section(".text.w36b_08045fcc")))
int Sub_08045FCC(u8 *p)
{
    int ret = 0;
    switch (p[6]) {
    case 0:
        Sub_08005A9C(9);
        {
            u8 v = Sub_080467DC(p);
            u8 *arr = (u8 *)0x02004830;
            arr[618] = v;
            arr[619] = 0;
        }
        Sub_08046038(p);
        Sub_080460C0(p);
        Sub_080466AC(p);
        Sub_08046810(p);
        p[6]++;
        /* fallthrough */
    case 1:
        if (Sub_080462A8(p) != 0) {
            ret = 1;
        }
        break;
    default:
        break;
    }
    return ret;
}
