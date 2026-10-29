/* Wave 22 worker A @0x08011E20 (120 B incl. trailing pool; 112 B code).
 * MATCHED with main agbcc. Sibling of w16b_08017000 (Node_PopAndInit):
 * pops a node via sub_08004424 on *(u32*)0x02005270, early-out 0 if null;
 * else bit-ops at node+35 from a/b (with b==0 ? &0x7F : |0x80), node[9]=c,
 * node[5]=**(u32**)(0x08223cc0 + c*4) double-deref, then
 * *(u32*)(0x02005020 + b*4) = node.
 * Trailing pool (0x08223cc0, 0x02005020) is 0/4 B past the 112-B code end;
 * TRUE extent 120 B per staging/wave22_A/fix_extents.py.
 * Idioms: pinned-barrier for pool loads (forces ldr before strb/lsls);
 * array-index form *(u32*)tbl[c] steers tbl->r1/index->r0 (explicit
 * (tbl+(c<<2)) puts tbl in r0); sibling-shape transfer from w16b_08017000.
 * Evidence: docs/match_notes_wave22_A.md.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 *sub_08004424(u32 list);

u32 *Node_PopAndInit_11E20(u8 a, u8 b, u8 c) __attribute__((section(".text.w22a_08011E20")));
u32 *Node_PopAndInit_11E20(u8 a, u8 b, u8 c)
{
    register u32 *s __asm__("r4");
    u8 *p;
    u32 *tbl;
    u32 *base;
    int v;
    int w;
    u8 x, t;

    s = sub_08004424(*(u32 *)0x02005270);
    if (s != 0) {
        p = (u8 *)s;
        p += 35;
        x = (a & 7) << 4;
        v = -113;
        v &= *p;
        v |= x;
        t = b & 15;
        w = -16;
        v &= w;
        v |= t;
        *p = v;
        if (b == 0)
            v &= 0x7F;
        else
            v |= 0x80;
        *p = v;
        tbl = (u32 *)0x08223cc0;
        __asm__ volatile("" : "+r" (tbl));
        ((u8 *)s)[9] = c;
        ((u32 *)s)[5] = *(u32 *)tbl[c];
        base = (u32 *)0x02005020;
        __asm__ volatile("" : "+r" (base));
        base[b] = (u32)s;
    }
    return s;
}
