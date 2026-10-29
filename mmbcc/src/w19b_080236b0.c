/* Worker B wave19 @0x080236b0 (64 B). MATCHED with old_agbcc.
 * Idioms: pin cc->r4 + dd->r6 (not r7: agbcc won't push a pinned r7),
 * aa left natural -> lands r5 with lsl/lsr #24 truncation; nibble via
 * u32 w35 temp + old_agbcc -> ldrb r0 / lsl r2,r0,#28 / lsr r2,r2,#28
 * (main agbcc merges the load into r2); in-if u32 temps (declared after
 * the byte stores) force load-load-store-store word copy. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_080236B0")))
u8 *NewNode_080236B0(u32 a, u8 *b, u8 *c, u8 *d)
{
    register u8 *cc __asm__("r4") = c;
    register u8 *dd __asm__("r6") = d;
    u8 aa = (u8)a;
    u8 nib;
    u32 w35;
    u8 *p;
    w35 = cc[35];
    nib = (w35 << 28) >> 28;
    p = (u8 *)Node_PopAndInit_20ED4(0, 1, nib, 7);
    if (p != 0) {
        u8 z = 0;
        u32 dw0;
        u32 dw1;
        p[16] = z;
        p[17] = aa;
        dw0 = *(u32 *)dd;
        dw1 = *(u32 *)(dd + 4);
        *(u32 *)(p + 96) = dw0;
        *(u32 *)(p + 100) = dw1;
        *(u8 **)(p + 40) = b;
        *(u8 **)(p + 44) = cc;
    }
    return p;
}
