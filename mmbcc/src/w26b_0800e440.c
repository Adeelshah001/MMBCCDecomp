/* Wave 26-B: 0x0800E440 ChipState_F_0800E440 — adapted from MATCHED sibling
 * ChipState_Tick_0800E748 (w24c, 128 B, 0 diffs). Same chip-init state
 * machine shape on the 0x02005130 struct; ternary is 5/3 (not 6/2).
 *
 * Idioms (from w24c_0800e748.c):
 * - inline asm for the branchy ternary (compilers emit speculative mov):
 *   cmp/beq/movs #5/b/movs #3, result in r0 for the bl.
 * - volatile u32 for the S+28 store+reload (forces str + ldr r1).
 * - second base variable S2 defeats pool folding for the mid-function
 *   0x02005130 literal (ldr r0,=pool; strh r1,[r0,#24]).
 * - u8 z = 0 idiom for case 1 (movs r0,#0 once, reused by bl).
 * True extent: 128 B (118 code + 2 pad + 8 pool).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 *ChipInit_0801709C(u8 a);
extern u8 Byte12_Gt1_080170c4(u8 *s);
extern void SetByte20_Clear21to23_02005130(u8 v);
extern void ListIterate_D568(u32 *p);

__attribute__((section(".text.w26b_0800e440")))
void ChipState_F_0800E440(void)
{
    register u8 *S __asm__("r4") = (u8 *)0x02005130;

    *(u16 *)(S + 24) = 1;
    switch (S[21]) {
    case 0: {
        u32 q;
        u8 t = *(S + 37);
        u8 arg;
        __asm__ volatile(
            "cmp %1, #0\n\t"
            "beq 1f\n\t"
            "movs %0, #5\n\t"
            "b 2f\n\t"
            "1:\n\t"
            "movs %0, #3\n\t"
            "2:"
            : "=r" (arg) : "r" (t) : "cc");
        *(volatile u32 *)(S + 28) = (u32)ChipInit_0801709C(arg);
        q = *(volatile u32 *)(S + 28);
        if (q == 0) {
            u8 *S2 = (u8 *)0x02005130;
            *(u16 *)(S2 + 24) = (u16)q;
            SetByte20_Clear21to23_02005130(0);
        } else {
            S[21]++;
        }
        break;
    }
    case 1:
        if (Byte12_Gt1_080170c4(*(u8 **)(S + 28))) {
            u8 z = 0;
            *(u16 *)(S + 24) = z;
            SetByte20_Clear21to23_02005130(z);
        }
        break;
    default:
        break;
    }
    ListIterate_D568(*(u32 **)0x02005270);
    ListIterate_D568(*(u32 **)0x020053C0);
}
