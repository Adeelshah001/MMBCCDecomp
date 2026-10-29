/* Wave 21 Worker B @0x08042ae4 (124 B incl. trailing pool; 120 B code).
 * MATCHED with main agbcc. Struct init: zeroes u32s at +18088/+18092/+18096,
 * copies a[4]->a[7], sets a[4]=1, a[5]=a[6]=0, a[18092]=5, a[18096]=0,
 * a[18098]=0, a[18097]=1, then a[18099]=(EwGet16_18()>7)?1:0.
 * Calls F_080248AC(0), EntryMgr_Teardown(), EntryMgr_Setup(); returns 0.
 * Mid-function pool at +0x4c (18088/18092/18098/18099); trailing pool at
 * +0x78 (18099, for else-branch; not CSE'd across branches).
 * Evidence: docs/match_notes_wave21_B.md.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 EwGet16_18(void);
extern void F_080248AC(u32);
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);

__attribute__((section(".text.w21b_08042AE4")))
u32 Sub_08042AE4(u8 *a)
{
    u32 off = 18099;
    *(u32 *)(a + 18088) = 0;
    *(u32 *)(a + 18092) = 0;
    *(u32 *)(a + 18096) = 0;
    a[7] = a[4];
    a[4] = 1;
    a[5] = 0;
    a[6] = 0;
    a[18092] = 5;
    a[18096] = 0;
    a[18098] = 0;
    a[18097] = 1;
    if (EwGet16_18() > 7) {
        a[off] = 1;
    } else {
        a[off] = 0;
    }
    F_080248AC(0);
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
