/* MMBCCDecomp — Wave 10 worker T.
 * Task_3AFFC unblock path: callee matching.
 *
 * MATCHED: sub_0800B368 @ 0x0800B368 (72 B, old_agbcc, 0 diffs).
 * Evidence: docs/match_notes_wave10_T.md.
 * Verification: staging/wave10_T/w10t_0800b368_v2.c via mk.sh harness
 * ( hardened: non-empty assertions, file offset = addr - 0x08000000,
 *  full 72 B extent, cmp -l zero diffs).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__asm__(
    ".set gBase0B368, 0x02004E40\n"
    ".set sub_0800B520, 0x0800B520\n"
    ".set sub_0800B4E4, 0x0800B4E4\n"
    ".set sub_0800B4C8, 0x0800B4C8\n"
);

extern u8 gBase0B368[];
void sub_0800B520(u32 a, u32 b, u32 c);
void sub_0800B4E4(void);
void sub_0800B4C8(void);

/* sub_0800B368 @ 0x0800B368 (72 B).
 * If (gEwram_02004E40[4] & 128) != 0: clear base[0..3], base[5]=3,
 * *(u32*)(base+32)=a, call B520(b,c,d)/B4E4()/B4C8(), return 1.
 * Else: base[5]=1, return 0.
 * Key idiom: inverted if ((x & 128) == 0) { else-branch } gives ROM's
 * beq-to-else layout; store order 0,3,2,1 matches ROM's scheduling. */
__attribute__((section(".text.w10t_0x0800b368")))
u8 sub_0800B368(u32 a, u32 b, u32 c, u32 d)
{
    u8 *base = gBase0B368;
    if ((base[4] & 128) == 0) {
        base[5] = 1;
        return 0;
    }
    base[0] = 0;
    base[3] = 0;
    base[2] = 0;
    base[1] = 0;
    base[5] = 3;
    *(u32 *)(base + 32) = a;
    sub_0800B520(b, c, d);
    sub_0800B4E4();
    sub_0800B4C8();
    return 1;
}
