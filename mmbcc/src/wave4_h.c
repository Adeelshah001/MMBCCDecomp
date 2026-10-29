/* MMBCCDecomp — Wave 4 batch H staged matches (worker H).
 * MATCHED 2026-10-20. Functions byte-identical (main agbcc -O2
 * -mthumb-interwork unless noted). See docs/wave4_h_results.tsv.
 *
 * All names are TENTATIVE (inferred from behavior only).
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void CpuFastSet(void *src, void *dst, unsigned mode);
extern void CpuSet(void *src, void *dst, unsigned mode);
extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern u8 gWram_03002420[];
extern u16 GetLimit_11C50(void);
extern u8 gRom_0817A9C4[];
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);

/* 0x08000758: 16-bit memcpy via CpuFastSet/CpuSet. Tentative.
 * The `cnt = n; cnt &= 0x1F; cnt >>= 1` sequence is required for the
 * exact `movs r2,#31; ands r2,r4; lsrs r2,r2,#1` (see match notes). */
__attribute__((section(".text.w4h_memcpy16")))
void Memcpy16(u8 *src, u8 *dst, u32 size)
{
    u8 *s;
    u8 *d;
    u32 n;

    s = src;
    __asm__ volatile("" : "+r" (s));
    d = dst;
    __asm__ volatile("" : "+r" (d));
    n = size;
    n &= -2;
    if (n == 0)
        return;
    s = (u8 *)((u32)s & -2);
    d = (u8 *)((u32)d & -2);
    if (((u32)s & 2) || ((u32)d & 2)) {
        CpuSet(s, d, (n << 10) >> 11);
        return;
    }
    if (n > 0x1F) {
        u32 bulk = n & -32;
        CpuFastSet(s, d, (bulk >> 2) & 0x1FFFFF);
        if ((n & 0x1F) == 0)
            return;
    }
    s += n & -32;
    d += n & -32;
    {
        u32 cnt;
        cnt = n;
        cnt &= 0x1F;
        cnt >>= 1;
        CpuSet(s, d, cnt);
    }
}

/* 0x080028D0: copy 8 bytes via CpuFastSet if *(u16*)(s+4)!=0 and s[6]==0.
 * Tentative. Destination is 0x03002420 + (b<<5); source is s + *(u32*)s + (a<<5).
 * The `b5 = (u8)b << 5` hoisted to prologue is required for the
 * `lsls #24; lsrs #19` sequence. */
__attribute__((section(".text.w4h_cpy8")))
void Copy8_28D0(u8 *s, u8 a, u8 b)
{
    u8 *src;
    u8 *dst;
    u32 b5;

    b5 = (u32)(u8)b << 5;
    if (*(u16 *)(s + 4) == 0)
        return;
    if (s[6] != 0)
        return;
    src = s + *(u32 *)s + ((u32)(u8)a << 5);
    dst = gWram_03002420 + b5;
    CpuFastSet(src, dst, 8);
}

/* 0x080216A8: init with ChipSlot_Setup(s, 0x1600, 0). Tentative.
 * The two-step `v=2; v|=s[0xA]; v|=1` is required for the exact
 * `movs r0,#2; ldrb r1; orrs; movs r1,#1; orrs` sequence. */
__attribute__((section(".text.w4h_init216a8")))
void Init_216A8(u8 *s)
{
    *(u32 *)(s + 0x6C) = 0;
    {
        u8 v = 2;
        v |= s[0xA];
        v |= 1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0xB0 << 5, 0);
    *(u32 *)(s + 0x50) = 0;
    *(u32 *)(s + 0x54) = 0;
}

/* 2-byte zero pad: ROM has 0000 at 0x080216D2 (next function at
 * 0x080216D4); GAS would otherwise end the section with c046. */
__attribute__((section(".text.w4h_init216a8")))
static const u8 sPad_Init_216A8[2] = { 0, 0 };

__asm__(
    ".globl gWram_03002420\n.set gWram_03002420, 0x03002420\n"
    ".globl gRom_0817A9C4\n.set gRom_0817A9C4, 0x0817A9C4\n"
);

/* 0x08011C80: table lookup with 32-byte entries at 0x0817A9C4. Tentative.
 * Returns NULL if idx==0 or idx >= GetLimit_11C50() (0x4867). */
__attribute__((section(".text.w4h_tbl11c80")))
u8 *TableLookup_11C80(u16 idx)
{
    u16 lim;

    if (idx == 0)
        return 0;
    lim = GetLimit_11C50();
    if (idx >= lim)
        return 0;
    return gRom_0817A9C4 + (idx << 5);
}

/* 0x080350D0: reinit struct, then EntryMgr_Teardown/Setup. Tentative.
 * Returns 0. The large offsets (0x46A8+) force pool loads. */
__attribute__((section(".text.w4h_reinit350d0")))
u32 Reinit_350D0(u8 *s)
{
    *(u32 *)(s + 0x46A8) = 0;
    *(u32 *)(s + 0x46AC) = 0;
    s[4] = 1;
    s[5] = 0;
    *(u8 *)(s + 0x46A8) = 0;
    *(u8 *)(s + 0x46A9) = 0;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
