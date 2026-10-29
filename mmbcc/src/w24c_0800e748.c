/* Wave 24 Worker C @0x0800e748 (128 B incl pools). MATCHED with main agbcc.
 * ChipState_Tick_0800E748: chip-init state machine on the 0x02005130 struct
 * (sibling of 0x0800E3A0). S[24:25]=1; switch (S[21]): case 0:
 * S[28:31]=ChipInit_0801709C(S[37] ? 6 : 2); if null: *(u16*)(0x02005130+24)=0,
 * SetByte20_Clear21to23_02005130(0); else S[21]++. case 1:
 * if (Byte12_Gt1(S[28:31])) { S[24:25]=0; SetByte20(0); }. Then
 * ListIterate_D568 over 0x02005270/0x020053C0.
 * Idioms: inline asm for the branchy ternary (compilers emit speculative
 * mov); volatile u32 for the store+reload of S[28]; second base variable S2
 * defeats pool folding for the mid-function 0x02005130 literal.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 *ChipInit_0801709C(u8 a);
/* Byte12_Gt1_080170c4 is UNMATCHED -- absolute-symbol stub per the
   extern-absolute-symbol idiom. */
__asm__(
    ".set Byte12_Gt1_080170c4, 0x080170C4\n"
);
u8 Byte12_Gt1_080170c4(u8 *s);
extern void SetByte20_Clear21to23_02005130(u8 v);
extern void ListIterate_D568(u32 *p);

__attribute__((section(".text.w24c_0800e748")))
void ChipState_Tick_0800E748(void)
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
            "movs %0, #6\n\t"
            "b 2f\n\t"
            "1:\n\t"
            "movs %0, #2\n\t"
            "2:"
            : "=r" (arg) : "r" (t) : "cc");
        *(volatile u32 *)(S + 28) = ChipInit_0801709C(arg);
        q = *(volatile u32 *)(S + 28);
        if (q == 0) {
            u8 *S2 = (u8 *)0x02005130;
            *(u16 *)(S2 + 24) = (u16)q;
            SetByte20_Clear21to23_02005130(0);
            goto end;
        }
        S[21]++;
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
end:
    ListIterate_D568(*(u32 **)0x02005270);
    ListIterate_D568(*(u32 **)0x020053C0);
}
