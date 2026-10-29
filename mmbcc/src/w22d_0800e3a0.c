/* Wave 22-D @0x0800E3A0 (86 B code + 2 pad + 8 B pool; interior pool
 * holds 0x02005130). MATCHED with main agbcc.
 * ChipState_Tick_0800E3A0: chip-init state machine on the 0x02005130 struct.
 * S[24:25]=1; switch (S[21]) { case 0: S[28:31]=ChipInit_0801709C(0);
 * if null break; S[21]++; case 1: if (Byte12_Gt1_080170c4(S[28:31])) {
 * S[24:25]=0; SetByte20_Clear21to23_02005130(); } }; then ListIterate_D568
 * over the 0x02005270 and 0x020053C0 lists.
 * Codegen-shaped callee extern: Byte12_Gt1_080170c4 declared (u8*)->u8
 * (definition returns u32; ABI-identical, shapes ROM's lsls/cmp check).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 *ChipInit_0801709C(u8 a);
extern u8 Byte12_Gt1_080170c4(u8 *s);
extern void SetByte20_Clear21to23_02005130(void);
extern void ListIterate_D568(u32 *p);

__attribute__((section(".text.w22d_0800E3A0")))
void ChipState_Tick_0800E3A0(void)
{
    register u8 *S __asm__("r4") = (u8 *)0x02005130;

    *(u16 *)(S + 24) = 1;
    switch (S[21]) {
    case 0: {
        u32 *p = ChipInit_0801709C(0);
        *(u32 **)(S + 28) = p;
        if (p == 0)
            break;
        S[21]++;
        break;
    }
    case 1:
        if (Byte12_Gt1_080170c4(*(u8 **)(S + 28))) {
            *(u16 *)(S + 24) = 0;
            SetByte20_Clear21to23_02005130();
        }
        break;
    default:
        break;
    }
    ListIterate_D568(*(u32 **)0x02005270);
    ListIterate_D568(*(u32 **)0x020053C0);
}
