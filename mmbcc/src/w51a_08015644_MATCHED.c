/* W51-A 0x08015644 MATCH (232 B, 0 diffs) — ChipSlot state machine.
 * Fix vs W50-D v1 (5 diffs): byte-pair table declared as u8[][2] and indexed
 * tbl[s[17]][0] / tbl[s[17]][1]; this flips base/index allocation to base->r1,
 * idx->r2, matching the ROM exactly. Old_agbcc -O2 -mthumb-interwork.
 * TRUE extent 232 B (bx 0x15724, pad 0x15726, pool 0x15728 = 0xffffc400,
 * next fn 0x1572c). Pools raw LE: 0x08223e60 (at 0x156b8, byte-pair table),
 * 0x08223ed8 (at 0x156bc, s16-pair table), 0xffffc400 (at 0x15728, Vec2 x).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void ChipSlot_IncUse(u8 *s, u8 n);
extern void ChipSlot_Tick(u8 *s);
extern void Vec2_SetMirrored(u8 *o, int x, int y);
extern short Sub_08011F50(u8 *s);
extern void Sub_08011F68(u8 *s, int a);
extern u8 Sub_08017474(u32 a);
extern void Sub_08017464(u32 a);
extern void Sub_0801AA70(int a, int b, int c, int d, int e, u32 f);
__asm__(".set Sub_08011F50, 0x08011f50");
__asm__(".set Sub_08011F68, 0x08011f68");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_0801AA70, 0x0801aa70");

extern u8 tbl_08223E60[][2];
extern s16 tbl_08223ED8[][2];
__asm__(".set tbl_08223E60, 0x08223e60");
__asm__(".set tbl_08223ED8, 0x08223ed8");

__attribute__((section(".text.w51a_08015644")))
void Sub_08015644(u8 *s)
{
    u8 *t = s + 124;
    switch (s[14]) {
    case 0:
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 1: {
        int b0, b1, nib;
        s16 (*tp)[2];
        s16 *e;
        if (Sub_08011F50(s) == 0)
            break;
        b0 = tbl_08223E60[s[17]][0];
        b1 = tbl_08223E60[s[17]][1];
        nib = (int)(((u32)s[35] << 28) >> 28);
        tp = tbl_08223ED8;
        e = tp[t[0]];
        Sub_0801AA70(b0, b1, nib, e[0], e[1], *(u32 *)(s + 44));
        s[10] &= 0xfe;
        s[14]++;
        break;
    }
    case 2:
        if (Sub_08017474(*(u32 *)(s + 44)) <= 6)
            break;
        s[10] |= 1;
        ChipSlot_IncUse(s, 1);
        s[14]++;
        break;
    case 3:
        if (Sub_08011F50(s) == 0)
            break;
        Sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, -15360, 0);
        ChipSlot_IncUse(s, 0);
        t[4] = 0;
        Sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
