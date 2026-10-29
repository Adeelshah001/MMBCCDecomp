/* W46-D v1: 0x0801ba94, 256 B (NOT the W38 TSV 288 B — the W38 window
 * spans TWO functions: this function ends at 0x0801bb94 (code through
 * bx 0x1bb8c + 2 B pad + 4 B pool at 0x0801bb90), and a separate 32 B
 * leaf starts at 0x0801bb94; see w46d_0801bb94_v1.c. VOID (epilogue
 * pops lr into r0, so no value is returned — W38's "int/return 0"
 * note is wrong; the shared tail calls ChipSlot_Tick and returns).
 * Pools (raw LE ROM): guard -3840 (0xfffff100) at 0x0801badc;
 * byte table 0x08226858 at 0x0801bb4c; pointer table 0x082243d8
 * at 0x0801bb90 (trailing, after bx).
 * Callees: all MATCHED except Vec2_CopyMirrored (BLOCKED, keep .set;
 * coordinator drops the MATCHED .sets at landing, as usual). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void SetBit16(u8 *s, u8 bit);
extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);
extern u8 GetField17_U8(u8 *s);
extern void MaxAssign_17(u8 *s, u8 v);
extern u8 TestBit16(u8 *s, u8 bit);
extern void DecIfNonZero_18(u8 *s);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w46d_0801ba94")))
void Sub_0801BA94(u8 *s)
{
    int out[2];
    int mode;
    register int o0 __asm__("r6");
    int o1;
    u8 *tbl;
    u8 *entry;
    register int idx __asm__("r2");
    register u8 *tbase __asm__("r1");
    register u8 *tbaddr __asm__("r0");
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    goto tail;
c0:
    Vec2_AddMirrored(s, 212 << 2, *(u32 *)(s + 92));
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    if (*(int *)(s + 84) <= -3840)
        goto tail;
    s[10] &= 254;
    s[10] &= 253;
    goto shared;
c1:
    Vec2_CopyMirrored((u8 *)out, s);
    o0 = out[0];
    o1 = out[1];
    if (TestBit16((u8 *)*(u32 *)(s + 44), 1) != 0) {
        ChipInit_080178A8(14, (int)(((u32)s[35] << 28) >> 28), (short)o0, (short)o1, *(u32 *)(s + 44));
        goto shared;
    }
    SetBit16((u8 *)*(u32 *)(s + 44), 3);
    tbl = (u8 *)0x08226858;
    __asm__ volatile("" : "+r"(tbl));
    idx = s[16];
    __asm__ volatile("" : "+r"(idx));
    tbaddr = (u8 *)(idx + (int)tbl);
    ChipInit_080178A8(*tbaddr, (int)(((u32)s[35] << 28) >> 28), (short)o0, (short)o1, *(u32 *)(s + 44));
shared:
    s[13]++;
    goto tail;
c2:
    if ((u8)GetField17_U8((u8 *)*(u32 *)(s + 44)) <= 5)
        goto tail;
    MaxAssign_17((u8 *)*(u32 *)(s + 44), 7);
    DecIfNonZero_18((u8 *)*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    tbase = (u8 *)0x082243d8;
    __asm__ volatile("" : "+r"(tbase));
    entry = (u8 *)(s[9] * 4 + (int)tbase);
    *(u32 *)(s + 12) = mode;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)entry + 8);
tail:
    ChipSlot_Tick(s);
}
