/* W39-C: 0x08023f28, 168 B, old_agbcc -O2 -mthumb-interwork, pure C.
 * W38-C (168/78) fixed, all in C:
 *  - first 32768 block: value pinned r1 via `v1 = 128; barrier; v1 <<= 8`
 *    (the barrier defeats constant folding to a pool load of -32768,
 *    which would not fit the extent), copy pinned r0 (`w1 = v1`) gives
 *    ROM's `adds r0, r1, #0`, stores from r0.
 *  - middle order: G[60]/G[61] stores, then i=0, then q62, then the
 *    hoisted zero — straight-line C order now matches ROM.
 *  - loop variable as s8 (not u8 + (s8) casts): gcc then emits ROM's
 *    loop exactly (address into r1, increment from the extended r0,
 *    rebuild via lsl/lsr). The u8 form preserved i in r1 and used r0
 *    for the address; the si-variable + barrier form added a copy.
 *  - tail block: pointer pinned r0, value pinned r1 via `vv = 128;
 *    barrier; vv <<= 8`, barrier on q before the last store defeats
 *    gcc's offset-fold (`strh [r0, #2]`) so the last store is
 *    `adds r0, #2; strh [r0]` like the others.
 * Callee .set blocks at END (GAS idiom).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern void F_080253F8(u8 *a, u8 *b);
extern void F_0802616C(u8 *a, u8 *b);
extern void F_0802617C(u8 *a, u8 *b);

__attribute__((section(".text.w39c_08023f28")))
void Sub_08023F28(u8 *s)
{
    u8 *G = (u8 *)0x02007090;
    s8 si;
    u8 *q62;
    *(u16 *)(G + 88) = 1;
    *(u32 *)(G + 52) = (u32)s;
    F_080253F8(G, s + 436);
    F_0802616C(G + 20, *(u8 **)(G + 52));
    F_0802617C(G + 24, *(u8 **)(G + 52) + 1184);
    s = s + 5028;
    *(u32 *)(G + 56) = (u32)s;
    {
        register u16 v1 __asm__("r1");
        register u16 w1 __asm__("r0");
        v1 = 128;
        __asm__ volatile("" : "+r"(v1));
        v1 <<= 8;
        w1 = v1;
        *(u16 *)(s + 0) = w1;
        *(u16 *)(s + 2) = w1;
        *(u16 *)(s + 4) = w1;
        *(u16 *)(s + 6) = w1;
        *(u16 *)(s + 8) = w1;
    }
    G[60] = 50;
    G[61] = 200;
    si = 0;
    q62 = G + 62;
    do {
        q62[si] = 0;
        si++;
    } while (si <= 9);
    {
        register u8 *q __asm__("r0");
        register u16 vv __asm__("r1");
        q = G + 72;
        *q = 0;
        q++;
        *q = 0;
        q++;
        vv = 128;
        __asm__ volatile("" : "+r"(vv));
        vv <<= 8;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        __asm__ volatile("" : "+r"(q));
        *(u16 *)q = vv;
    }
}

__asm__(".set F_080253F8, 0x080253f8");
__asm__(".set F_0802616C, 0x0802616c");
__asm__(".set F_0802617C, 0x0802617c");
