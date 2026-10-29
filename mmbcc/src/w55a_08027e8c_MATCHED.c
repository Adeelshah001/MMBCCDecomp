/* W55-A (MATCHED candidate, 0 diffs): 0x08027e8c, true extent 244 B.
 * W54-B nv+goto base + pool-order fixes for the three lookup spots:
 * tables via extern arrays (.set at end, project idiom) so the table
 * address loads from the pool; lookup spot 1 via an unpinned tbl
 * variable (from the extern array, so it cannot constant-fold) +
 * idx variable before the p28 assignment (ROM order: pool, idx,
 * p28, adds, ldrb, adds, ldrb) + v variable + tbl[v]/tbl+v call;
 * spot 2 via a direct extern-array index in one statement (pool
 * first); tail via an unpinned tblt variable + a BLOCK-SCOPED r0
 * pin for the index (idx2r) so idx and v both land in r0 exactly
 * as ROM. Pin safety: idx2r's live range is assign -> v computation
 * only; it is dead before the tail call (call args are the byte in
 * r0, c in r1, b2>>4 in r2), so no call-clobbered preservation is
 * relied on -- the .s shows the genuine ldrsb into r0 and its
 * consumption by the adds. (W54-B nv+goto header follows.)
 * v11 base (244 exact / 158 diffs) restructured
 * + int nv, p28 lookup, equal asm-copy (170d4 trick: asm "add",
 * not "adds", sh block-pinned r1) so the three s[3]
 * producers (dec, clear, or-8) all feed ONE source-level store:
 * dec/clear assign nv then goto store; or-8 assigns nv and FALLS
 * THROUGH to store (exactly ROM's layout: dec b->store, clear
 * b->store, or-8 fall-through, store, p28, b->tail). Lookup and
 * equal blocks are reached by goto from the compare chain and sit
 * AFTER the store block in source, so the emitted order matches
 * ROM: [dec/clear][compare/or-8][store/p28][lookup][pools][equal]
 * [tail]. nv is unpinned (r0 pins are function-wide toxic, W53 v7).
 * All else carried from v11: pins s->r5/p28->r4/c->r6, fd-form
 * clear, u32 b, s8 t7, tail b2, inline-asm shift pair (lsl/lsr).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

extern void Sub_0802800C(int a, int b);
__asm__(".set Sub_0802800C, 0x0802800c");
extern void Sub_0800E068(u8 *s, int a, int b);
__asm__(".set Sub_0800E068, 0x0800e068");
extern int Sub_080280E8(int a, int b, int c);
extern u8 Tbl_0822DDA4[];
extern u8 Tbl_0822DDB0[];

__attribute__((section(".text.w55a_08027e8c")))
int Sub_08027E8C(u8 *s0)
{
    register u8 *s __asm__("r5") = s0;
    register int c __asm__("r6") = 0x3A10;
    register u8 *p28 __asm__("r4");
    u32 b;
    u8 v;
    int ret;
    u32 hi;
    if (s[4] == 0)
        return 1;
    b = s[3];
    {
        register int nv __asm__("r0");
    if (b & 8) {
        if ((b & 240) != 0 && !(b & 1)) {
            register int sh __asm__("r1") = ((b >> 4) - 1) << 4;
            register int lo __asm__("r0") = b & 15;
            nv = lo | sh;
            goto store;
        }
        {
            int t = s[3] & 15;
            nv = t & -9;
            goto store;
        }
    }
    if (s[5] != s[6]) {
        if (b & 240) {
            nv = 8;
            nv |= b;
        } else {
            goto lookup;
        }
    } else {
        goto equal;
    }
store:
    s[3] = nv;
    p28 = s + 28;
    goto tail;
    }
lookup:
    {
        s8 t7;
        u8 *tbl;
        int idx;
        s[5] = s[6];
        tbl = Tbl_0822DDA4;
        idx = (s8)s[5];
        p28 = s + 28;
        v = p28[idx];
        Sub_0802800C(tbl[v], tbl + v);
        t7 = Tbl_0822DDB0[(s8)s[5]];
        s[7] = t7;
        if (t7 >= 0)
            Sub_0800E068(s + 8, s[7], 2);
    }
    goto tail;
equal:
    {
        register u32 tmphi __asm__("r1");
        __asm__ volatile("lsl %0, %2, #24\n\tlsr %1, %0, #28" : "=r"(tmphi), "=r"(hi) : "r"(b));
    }
    p28 = s + 28;
    if (hi <= 14) {
        register int sh __asm__("r1");
        __asm__ volatile("add %0, %1, #0" : "=r" (sh) : "r" (hi));
        sh = (sh + 1) << 4;
        {
            register int lo __asm__("r0") = b & 15;
            s[3] = lo | sh;
        }
    }
tail:
    {
        u32 b2 = s[3];
        u8 *tblt;
        register int idx2r __asm__("r0");
        if (b2 & 1)
            c = 0xFFFF;
        tblt = Tbl_0822DDA4;
        idx2r = (s8)s[5];
        v = p28[idx2r];
        ret = Sub_080280E8(tblt[v], c, b2 >> 4);
    }
    return ret;
}

__asm__(".set Tbl_0822DDA4, 0x0822dda4");
__asm__(".set Tbl_0822DDB0, 0x0822ddb0");
