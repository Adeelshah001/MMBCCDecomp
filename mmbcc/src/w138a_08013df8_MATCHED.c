/* Wave 138-A v2 (STAGED ONLY, NOT LANDED): 0x08013DF8, TRUE extent 300 B
 * (next fn 0x08013F24). Manual hand-read: switch dispatch on s[14]
 * (range-checked, jump table at 0x13E18, mov pc,r0 — ARMv4T stays in
 * Thumb, even entries correct, as in matched 0x080146C0), common
 * ChipSlot_Tick epilogue. Case 0: Vec2(s,0xFFFFC400,0) + IncUse(8) +
 * s[14]++. Case 1: s16-check 11F50, SetBit 174A4(f44,3), three
 * ChipInit 1AA70(30,0/1/2,nib,0xFFFFEC00,0xFFFFB000,f44) with nib =
 * (s[35]<<28)>>28 recomputed per call, IncUse(9) + s[14]++. Case 2:
 * 11F50 check, s[14]++ only. Case 3: (u8)17474(f44)<=5 break, else
 * IncUse(10) + s[14]++. Case 4: 11F50 check, 17478(f44,7), 17464(f44),
 * f44=0, Vec2(s,0xFFFFC400,0), IncUse(0), q[4]=0 (q=s+124),
 * 11F68(s,0). Plain C + file-scope .set stubs only (no pin, no inline
 * asm in body, no barrier). old_agbcc -O2 -mthumb-interwork.
 * v2 vs v1: nib via (u32)(p[0]<<28)>>28 (lsl;lsr, not lsl;asr;lsr)
 * and ChipInit params as int (pool loads for 0xFFFFEC00/0xFFFFB000)
 * -> 0 diffs, 300/300 B, CLEAN (no pin/asm/barrier/alias).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern void Vec2_SetMirrored(u8 *s, s32 x, s32 y);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void ChipSlot_Tick(u8 *s);
extern s16 Sub_08011F50(u8 *s);
extern void Sub_080174A4(u32 a, int b);
extern u32 *ChipInit_0801AA70(int a, int b, int c, int d, int e, u8 *f);
extern u32 Sub_08017474(u32 a);
extern void Sub_08017478(u32 a, int b);
extern void Sub_08017464(u32 a);
extern void Sub_08011F68(u8 *s, int a);

__asm__(".set Vec2_SetMirrored, 0x0800DD2C");
__asm__(".set ChipSlot_IncUse, 0x0800D9EC");
__asm__(".set ChipSlot_Tick, 0x0800D9FC");
__asm__(".set Sub_08011F50, 0x08011F50");
__asm__(".set Sub_080174A4, 0x080174A4");
__asm__(".set ChipInit_0801AA70, 0x0801AA70");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_08011F68, 0x08011F68");

__attribute__((section(".text.w138a_08013df8_v2")))
void Sub_08013DF8(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_080174A4(*(u32 *)(s + 44), 3);
        {
            u8 *p = s + 35;
            ChipInit_0801AA70(30, 0, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
            ChipInit_0801AA70(30, 1, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
            ChipInit_0801AA70(30, 2, (u32)(p[0] << 28) >> 28, 0xFFFFEC00, 0xFFFFB000, *(u8 **)(s + 44));
        }
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2:
        if (Sub_08011F50(s) == 0)
            break;
        s[14]++;
        break;
    case 3:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) <= 5)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_08017478(*(u32 *)(s + 44), 7);
        Sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        q[4] = 0;
        Sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
