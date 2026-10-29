/* W37-C MATCHED (C + verified .s patch, see w37c_0801e028.patch.txt):
 * 0x0801e028, 168 B, old_agbcc, 0 diffs after patch. Init task on
 * struct *s, same
 * family as 0x0801ec44 (tbl + tp address-first, bitfield clamp,
 * Setup/IncUse, s[69]).
 * tbl = 0x020051c8 + s[16]*12; tp = 0x082243d8 + s[9]*4;
 * s[12] = 1; s[20] = *(u32 *)(*tp + 4); s[18] = tbl[2]; s[19] = 0;
 * s[108] = 0; s[10] = (s[10] | 2) | 1 (two-step, constant first);
 * ChipSlot_Setup(s, s[17] | *(u16 *)(0x08226a70 + s[16]*2), 0);
 * ChipSlot_IncUse(s, 6); bitfield clamp; s[69] update;
 * F_0801E0D0(s).
 * Extern callees + addresses: ChipSlot_Setup 0x0800d6e0 (MATCHED),
 * ChipSlot_IncUse 0x0800d9ec (MATCHED), F_0801E0D0 0x0801e0d0
 * (MATCHED).
 * Pools (LE): 0x020051c8, 0x082243d8, 0x08226a70, 0x081705b0,
 * 0x020031e4.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void F_0801E0D0(u8 *s);
__asm__(".set F_0801E0D0, 0x0801e0d0");

__attribute__((section(".text.w37c_0801e028")))
void Sub_0801E028(u8 *s)
{
    register u8 *tbl __asm__("r2");
    register u8 *tbase __asm__("r0");
    register u8 *pbase __asm__("r1");
    register u8 *sbase __asm__("r1");
    u32 *tp;
    u16 *taddr;
    u8 s17;
    u8 *q108;
    u8 *q69;
    int v;
    int w;
    u8 t10;
    int tmp;
    u8 v18;
    u8 z;
    tbl = (u8 *)(s[16] * 12);
    tbase = (u8 *)0x020051c8;
    __asm__ volatile("" : "+r"(tbl));
    tbl = (u8 *)((u32)tbl + (u32)tbase);
    pbase = (u8 *)0x082243d8;
    __asm__ volatile("" : "+r"(pbase));
    tp = (u32 *)(s[9] * 4 + (u32)pbase);
    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
    v18 = tbl[2];
    z = 0;
    s[18] = v18;
    s[19] = z;
    q108 = s + 80;
    __asm__ volatile("" : "+r"(q108));
    *(u32 *)(q108 + 28) = 0;
    t10 = 2;
    t10 |= s[10];
    t10 |= 1;
    s[10] = t10;
    sbase = (u8 *)0x08226a70;
    __asm__ volatile("" : "+r"(sbase));
    taddr = (u16 *)(s[16] * 2 + (u32)sbase);
    s17 = s[17];
    ChipSlot_Setup(s, s17 | *taddr, 0);
    ChipSlot_IncUse(s, 6);
    v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
    w = v;
    __asm__ volatile("" : "+r"(w));
    if (w > 3)
        v = 3;
    q69 = s + 69;
    {
        int sh = v << 2;
        tmp = (s[69] & -13) | sh;
    }
    *q69 = tmp;
    F_0801E0D0(s);
}
