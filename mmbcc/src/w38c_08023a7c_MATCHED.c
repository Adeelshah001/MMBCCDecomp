/* W37-C2: 0x08023a7c, TRUE extent 112 B (TSV 174 WRONG;
 * next function starts at 0x08023aec).
 * G=0x02000840. Sub_08023BC4(G,a1,(s[0]+s[4])&127);
 * Xor_23CE4(s,G); Sub_08023C38(G+16,G,(s[2]+s[6])&127);
 * G[30]=F_23D10(G+16); Xor_23CE4(s,G+16);
 * Sub_08023D68(G+16,a2); F_23B64(a2).
 * Callees: Sub_08023BC4 0x08023bc4 (MATCHED), Xor_23CE4
 * 0x08023ce4 (MATCHED), Sub_08023C38 0x08023c38 (BLOCKED,
 * .set), F_23D10 0x08023d10 (MATCHED), Sub_08023D68
 * 0x08023d68 (MATCHED), F_23B64 0x08023b64 (MATCHED).
 * Pool (LE): 0x02000840.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_08023BC4(u8 *dst, u8 *base, u32 arg2);
extern void Xor_23CE4(u8 *p0, u8 *p1);
extern void Sub_08023C38(u8 *dst, u8 *src, u8 sl);
__asm__(".set Sub_08023C38, 0x08023c38");
extern u8 F_23D10(u8 *p);
extern void Sub_08023D68(u8 *src, u16 *dst);
extern void F_23B64(u16 *p);

__attribute__((section(".text.w38c_08023a7c")))
void Sub_08023A7C(u8 *s, u8 *a1, u16 *a2)
{
    register u16 *r9 __asm__("r9");
    register int mask __asm__("r8");
    u8 *g;
    u8 *q;
    r9 = a2;
    g = (u8 *)0x02000840;
    mask = 127;
    Sub_08023BC4(g, a1, (s[0] + s[4]) & mask);
    Xor_23CE4(s, g);
    q = g;
    q += 16;
    Sub_08023C38(q, g, (s[2] + s[6]) & mask);
    g[30] = F_23D10(q);
    Xor_23CE4(s, q);
    Sub_08023D68(q, r9);
    F_23B64(r9);
}
