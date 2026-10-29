/* Wave 15 worker D: blocked revisits cracked with Wave-14 idioms (main agbcc).
 * Coordinator-landed after independent clean-room re-verification (0 diffs).
 * Evidence: docs/match_notes_wave15_D.md, docs/wave15_D_results.tsv.
 *
 * 0x08000DC0: Task_ActivateSlot (68 B) — task-slot init, calls ContextSwitch.
 * 0x08024818: TblStride_24818 (48 B) — stride lookup via GetStride4Byte20.
 * 0x08011170: Tbl_ClearEntries (68 B) — table-entry clear loop.
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef signed short s16;

extern void ContextSwitch(u8 *p, u8 *q, u32 w);
extern u8 GetStride4Byte20(u8 *s, u16 idx);
extern u32 GetRomTableEntry_082240B8(u8 a);
extern u8 TableByte_16FAC(u8 a, u8 b);
extern void TblFindClear_02C74(u8 v);

__attribute__((section(".text.w15d_08000dc0")))
void Task_ActivateSlot(u32 v)
{
    register u32 base __asm__("r2");
    register u32 t1 __asm__("r1");
    u32 t;
    u8 *p;
    __asm__ volatile("" : "=r" (base) : "0" (0x030005C0));
    t1 = *(u32 *)(base + 0x1E50);
    t = (t1 << 1) + t1;
    t <<= 3;
    base += 0x1E08;
    p = (u8 *)(t + base);
    if (v != 0) {
        u8 *q;
        u8 *r;
        u32 w;
        *(u16 *)(p + 2) = (u16)v;
        *p = 4;
        q = p + 4;
        r = p + 8;
        __asm__ volatile("" : "+r" (q), "+r" (r));
        __asm__ volatile("" : "=r" (w) : "0" (0x02000800));
        w = *(u32 *)w;
        ContextSwitch(q, r, w);
    }
}

__attribute__((section(".text.w15d_08024818")))
u8 TblStride_24818(u16 idx)
{
    u8 * volatile *pp = (u8 * volatile *)0x2007090;
    u8 *p = pp[5];
    register u8 *q __asm__("r3") = p + (216 << 1);
    register u8 k __asm__("r4") = *q;
    return (u8)GetStride4Byte20(p + k * 144, idx);
}

__attribute__((section(".text.w15d_08011170")))
void Tbl_ClearEntries(u8 a)
{
    s16 n = (s16)GetRomTableEntry_082240B8(a);
    u16 i;
    if (n <= 0)
        return;
    for (i = 0; (s16)i < n; ) {
        u32 t;
        TblFindClear_02C74(TableByte_16FAC(a, (u8)i));
        t = (u32)i << 16;
        t += 0x80 << 9;
        i = (u16)(t >> 16);
    }
}

/* Absolute callees with no symbol in the build (must FOLLOW the code per the
 * GAS 2.42 .set ordering rule):
 * - ContextSwitch @0x08000300: ASM in crt0_thumb_helpers region, no label.
 * - GetStride4Byte20 @0x080258C0: build defines GetStride4Byte20_080258C0
 *   (suffixed); the canonical registry name gets the absolute alias here.
 * GetRomTableEntry_082240B8 / TableByte_16FAC / TblFindClear_02C74 resolve
 * to real definitions elsewhere in the build (externs above).
 */
__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl ContextSwitch\n"
    ".set ContextSwitch, 0x08000300\n"
    ".thumb_func\n"
    ".globl GetStride4Byte20\n"
    ".set GetStride4Byte20, 0x080258C0\n"
);
