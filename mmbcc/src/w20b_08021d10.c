/* 0x08021d10: BuildList_08021D10 (114 B, main agbcc + custom pool sed).
 * Linked-list builder guarded by *(s16 *)(*(u8 **)0x020066f0 + 10) > 5.
 * Builds up to 6 nodes (head + 5) via Node_PopAndInit_20ED4(0,0,0,3).
 * Idioms: pin prev->r4 to force i->r5 (natural allocation swaps them);
 * u16 increment via t=(u32)i<<16; t+=0x80<<9; i=(u16)(t>>16);
 * mid-function pool: replace pool's .align 2,0 with .short 0x0000
 * (avoids 4-byte section padding; pool stays 4-aligned at +0x14).
 * Wave 20 Worker B. Evidence: docs/match_notes_wave20_B.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w20b_08021D10")))
u8 *BuildList_08021D10(void)
{
    s16 v = *(s16 *)(*(u8 **)0x020066f0 + 10);
    register u8 *n __asm__("r2");
    u8 *head;
    register u8 *prev __asm__("r4");
    u16 i;
    u32 z;
    u32 t;

    if (v <= 5)
        return 0;
    n = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (n != 0)
    {
        u8 z2 = 0;
        n[16] = 2;
        n[17] = z2;
        *(u8 **)(n + 40) = n;
    }
    head = n;
    i = 1;
    z = 0;
    goto loop;
loop:
    prev = n;
    n = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (n == 0)
        goto done;
    n[16] = 2;
    n[17] = (u8)i;
    *(u8 **)(n + 40) = head;
    *(u32 *)(n + 44) = z;
    *(u8 **)(prev + 44) = n;
    t = (u32)i << 16;
    t += 0x80 << 9;
    i = (u16)(t >> 16);
    if ((s16)(t >> 16) <= 5)
        goto loop;
done:
    return head;
}
