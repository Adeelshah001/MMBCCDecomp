/* W37-C MATCHED: 0x0801757c, TRUE extent 132 B (TSV says 164, wrong —
 * the 0x08017600 function, 32 B, sits between 1757c and 17620; the
 * TSV neighbor skipped it), old_agbcc, pure C, 0 diffs.
 * Task step on struct *s, returns void. Idioms: base pinned r1 +
 * barrier for pool-load order; reversed addition lands sum in r0;
 * s[12] is a WORD store (str, not strb).
 * ChipSlot_Tick(s);
 * if (s[13] == 0 && ++s[18] == 15) {
 *   ChipInit(1, nibble, 15360, -5632, s[44]); Text_SelectBlobIdx(128);
 *   s[13] = 1;
 * }
 * if (GetField17_U8(s[44]) > 5) {
 *   s[12] = 2; s[20] = *(u32 *)(*(u32 *)(0x082243d8 + s[9]*4) + 8);
 *   MaxAssign_17(s[44], 7); DecIfNonZero_18(s[44]); *(u32*)(s+44) = 0;
 * }
 * Extern callees + addresses: ChipSlot_Tick 0x0800d9fc (MATCHED),
 * ChipInit_080178A8 0x080178a8 (MATCHED), Text_SelectBlobIdx
 * 0x0804a378 (MATCHED), GetField17_U8 0x08017474 (MATCHED),
 * MaxAssign_17 0x08017478 (MATCHED), DecIfNonZero_18 0x08017464
 * (MATCHED).
 * Pools (LE): 0xffffea00, 0x082243d8.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_Tick(u8 *s);
extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern int Text_SelectBlobIdx(int idx);
extern u8 GetField17_U8(u8 *p);
extern void MaxAssign_17(u8 *p, int v);
extern void DecIfNonZero_18(u8 *p);

__attribute__((section(".text.w37c_0801757c")))
void Sub_0801757C(u8 *s)
{
    u32 **t;
    ChipSlot_Tick(s);
    if (s[13] == 0 && ++s[18] == 15) {
        ChipInit_080178A8(1, ((u32)s[35] << 28) >> 28, 15360, -5632, *(u8 **)(s + 44));
        Text_SelectBlobIdx(128);
        s[13] = 1;
    }
    if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
        register u8 *base __asm__("r1");
        base = (u8 *)0x082243d8;
        __asm__ volatile("" : "+r"(base));
        t = (u32 **)(s[9] * 4 + (u32)base);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*t + 8);
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
