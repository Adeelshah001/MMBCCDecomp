/* Wave 42 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + patched rebuild + independent ROM-extract cmp).
 * See staging/w42coord_verify/ for coordinator verification artifacts.
 */
/* Wave 42 Worker C: 0x0800e068, TRUE extent 220 B.
 * Semantics (re-read from disassembly): init + CpuSet copy.
 *   s[0] = tbl1[a] + &tbl1[a]   (relative-offset table 0x086f0934)
 *   q = tbl2[a] (0x086f190c); s[4] = q;
 *   s[16] = b * 32;
 *   Init_08004244(s+8, q); StateUpdate_08004258(s+8, 0);
 *   p = *(u8 **)(s+0); p1 = p[1]; ucnt = p[2]-p[1]+1; cnt = (short)ucnt;
 *   f16 = *(u32 *)(s+16);
 *   if ((f16 & 0x1ff) == 0) { path1 } else { path2 }
 *   each path: tbl = *(u32 *)(s+8); ent = tbl[s[12]];
 *     off = (s8)s[13] (inline-asm ldrsb: agbcc never emits ldrsb);
 *     byte = *(u8 *)(ent + off*2);
 *     src = p + byte*cnt*2 + 4;
 *     path1 dst = f16 + p1*2 + 0x03002420;
 *     path2 dst = (f16 + p1*2 & 0x3ff) + 0x03002420;
 *     CpuSet(src, dst, cnt & 0x1fffff);
 * Pool constants re-derived from raw LE pool bytes at 0x0800e0e8..:
 *   0x086f0934, 0x086f190c, 0x000001ff, 0x03002420, 0x001fffff,
 *   0x000003ff, 0x03002420, 0x001fffff.
 * Callees via .set at END. Init_08004244 + CpuSet are MATCHED;
 * StateUpdate_08004258 (0x08004258) is BLOCKED - needs .set adjudication.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

void Init_08004244(void *s, void *pp);
void StateUpdate_08004258(u8 *p, u8 idx);
void CpuSet(void *src, void *dst, u32 count);

__attribute__((section(".text.w42c_0800e068")))
void F_0800E068(u8 *s, u8 a, u16 b)
{
    u32 *tbl1 = (u32 *)0x086f0934;
    u32 *tbl2 = (u32 *)0x086f190c;
    u8 *q;
    u8 *p;
    u8 p1;
    u16 ucnt;
    s16 cnt;
    u32 f16;
    *(u32 *)(s + 0) = tbl1[a] + (u32)&tbl1[a];
    q = (u8 *)tbl2[a];
    *(u32 *)(s + 4) = (u32)q;
    *(u32 *)(s + 16) = b * 32;
    Init_08004244(s + 8, q);
    StateUpdate_08004258(s + 8, 0);
    p = *(u8 **)(s + 0);
    p1 = p[1];
    ucnt = p[2] - p1 + 1;
    cnt = ucnt;
    f16 = *(u32 *)(s + 16);
    if ((f16 & 0x1ff) == 0) {
        u32 *tbl = *(u32 **)(s + 8);
        u32 *entp = &tbl[s[12]];
        int off;
        u8 byte;
        u8 *src;
        u8 *dst;
        __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=r" (off) : "r" (s));
        byte = *(u8 *)(*entp + off * 2);
        {
            int off2 = byte * cnt * 2 + 4;
            src = p + off2;
        }
        dst = (u8 *)(p1 * 2 + f16 + 0x03002420);
        CpuSet(src, dst, cnt & 0x1fffff);
    } else {
        u32 *tbl = *(u32 **)(s + 8);
        u32 *entp = &tbl[s[12]];
        int off;
        u8 byte;
        u8 *src;
        u8 *dst;
        __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=r" (off) : "r" (s));
        byte = *(u8 *)(*entp + off * 2);
        {
            int off2 = byte * cnt * 2 + 4;
            src = p + off2;
        }
        dst = (u8 *)(((p1 * 2 + f16) & 0x3ff) + 0x03002420);
        CpuSet(src, dst, cnt & 0x1fffff);
    }
}

__asm__(".set StateUpdate_08004258, 0x08004258");
