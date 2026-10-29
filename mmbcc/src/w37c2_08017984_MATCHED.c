/* W37-C2: 0x08017984, 192 B. Task step (void, s):
 * if ((u8)(s[119]-3)<=1) s[10]&=254;
 * ChipSlot_Tick(s);
 * if (s[13]==0) {
 *   s[18]++;
 *   if (s[18]==2) {
 *     ChipInit(tbl_08226388[s[16]],nibble(s[35]),15360,
 *       0xffffea00,s[44]); s[13]=1; } }
 * if (GetField17_U8(s[44])>5) {
 *   *(u32*)(s+12)=2;
 *   *(u32*)(s+20)=*(u32*)(tbl_082243d8[s[9]]+8);
 *   MaxAssign_17(s[44],7); DecIfNonZero(s[44]);
 *   *(u32*)(s+44)=0; }
 * Callees: ChipSlot_Tick 0x0800d9fc (MATCHED),
 * ChipInit 0x080178a8 (MATCHED), GetField17_U8
 * 0x08017474 (MATCHED), MaxAssign_17 0x08017478
 * (MATCHED), DecIfNonZero 0x08017464 (MATCHED).
 * Pools (LE): 0x08226388, 0xffffea00, 0x082243d8.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_Tick(u8 *s);
extern void ChipInit(u8 a, int b, int c, int d, u8 *e);
__asm__(".set ChipInit, 0x080178a8");
extern int GetField17_U8(u8 *p);
extern void MaxAssign_17(u8 *p, int v);
extern void DecIfNonZero(u8 *p);
__asm__(".set DecIfNonZero, 0x08017464");

__attribute__((section(".text.w37c2_08017984")))
void Sub_08017984(u8 *s)
{
    if ((u8)(s[119] - 3) <= 1)
        s[10] &= 254;
    ChipSlot_Tick(s);
    if (s[13] == 0) {
        s[18]++;
        if (s[18] == 2) {
            register u8 *tbl __asm__("r0") = (u8 *)0x08226388;
            __asm__ volatile("" : "+r"(tbl));
            ChipInit(tbl[s[16]],
                ((u32)s[35] << 28) >> 28,
                240 << 6, (int)0xffffea00, *(u8 **)(s + 44));
            s[13] = 1;
        }
    }
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5) {
        register u32 **tbl __asm__("r1") = (u32 **)0x082243d8;
        register u32 **addr __asm__("r0");
        __asm__ volatile("" : "+r"(tbl));
        addr = (u32 **)(s[9] * 4 + (int)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*addr + 8);
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
