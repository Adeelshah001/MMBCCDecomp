/* Wave 22-C: 0x08016D2C (128 B incl. 12 B trailing pool, old_agbcc).
 * Blocked revisit (w15-C2, 26 diffs: r2=s / pool->r1 allocation).
 * Idioms: clobber-reservation denies r4+r0 for the tbl pool pseudo (-> r1)
 *   and r4 for the tab2 pool pseudo (-> r1); tied empty asm "+r"(ti) keeps
 *   the int copy (adds r0,r1,#0) before the signed clamp compare;
 *   int m = -13 forces movs+negs mask materialization (not movs #0xF3);
 *   pool 3 is 0x020031E4 (EWRAM table), read from ROM bytes not disasm.
 *   116 B code + 12 B pool; neighbor after is ObjInit_08016DAC (matched).
 * Evidence: docs/match_notes_wave22_C.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ObjInit_08016DAC(u8 *s);

__attribute__((section(".text.w22c_08016D2C")))
void sub_08016D2C(u8 *s)
{
    u8 *q = s + 124;
    u32 *tbl = (u32 *)0x08223CC0;
    u8 v;
    u32 *pp;
    u32 w0, w;
    u8 t;
    u16 hv;
    u32 idx;
    u8 *tab2;
    u8 b;
    int ti;
    u8 d;
    int sh;
    int m;
    u8 *r3b;

    __asm__ volatile("" : : "r"(tbl) : "r4", "r0");
    v = s[9];
    pp = tbl + v;
    *(u32 *)(s + 12) = 1;
    w0 = *pp;
    w = *(u32 *)(w0 + 4);
    *(u32 *)(s + 20) = w;
    if (q[4] == 1)
        s[13] = q[5];
    *(u32 *)(s + 108) = 0;
    t = s[10];
    t |= 2;
    t |= 1;
    s[10] = t;
    hv = *(u16 *)0x081705B0;
    idx = (hv >> 4) << 1;
    tab2 = (u8 *)0x020031E4;
    __asm__ volatile("" : : "r"(tab2) : "r4");
    b = tab2[idx] & 3;
    ti = b;
    __asm__ volatile("" : "+r"(ti));
    if (ti > 3)
        b = 3;
    r3b = s + 0x45;
    sh = b << 2;
    m = -13;
    d = *r3b;
    *r3b = (d & m) | sh;
    s[0x22] = 16;
    ObjInit_08016DAC(s);
}
