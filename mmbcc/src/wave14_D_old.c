/* Wave 14 worker D: blocked revisits, old_agbcc.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave14_D.md, docs/wave14_D_results.tsv. */

__attribute__((section(".text.w14d_08005338")))
void TblMapFF_05338(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    register unsigned char *tbl __asm__("r2");
    volatile unsigned short *out;
    __asm__ volatile("" : "=r" (tbl) : "0" (0x02003670));

    if (a == 0xFF) a = tbl[0x11B0];
    if (b == 0xFF) b = tbl[0x11B1];
    if (c == 0xFF) c = tbl[0x11B2];
    if (d == 0xFF) {
        register unsigned int off __asm__("r3");
        register unsigned char *p __asm__("r0");
        __asm__ volatile("" : "=r" (off) : "0" (0x11B3));
        p = tbl + off;
        d = *p;
    }

    out = (volatile unsigned short *)0x02003230;
    {
        register unsigned short v __asm__("r3");
        v = d;
        v |= c << 8;
        out[2] = v;
    }
    out[4] = b | (a << 8);
}

__attribute__((section(".text.w14d_08023d34")))
unsigned int Checksum_23D34(unsigned char *str, unsigned int c)
{
    register unsigned char *p __asm__("r4");
    register unsigned int sum __asm__("r3");
    register unsigned int i __asm__("r2");
    register unsigned int t __asm__("r0");

    p = str;
    __asm__ volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24" : "+r" (c));
    sum = 0;
    i = 0;

    do {
        t = p[i];
        t += sum;
        sum = (unsigned char)t;
        t = i + 1;
        i = (unsigned char)t;
    } while (i <= 13);

    t = sum + c;
    if ((unsigned char)t == 0) { } else return 1;
    return 0;
}

__attribute__((section(".text.w14d_08026574")))
unsigned char TblGetU8_26574(void *ctx, signed short idx, unsigned int sel)
{
    register unsigned short ii __asm__("r3") = (unsigned short)idx;
    unsigned char *base;
    unsigned char *entry;
    unsigned int addr;
    unsigned char *p;
    __asm__ volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24" : "+r" (sel));
    if (ii > 127)
        return 0;
    base = *(unsigned char **)((unsigned char *)ctx + 4);
    addr = (unsigned int)ii * 28 + (unsigned int)base;
    entry = (unsigned char *)addr;
    if (entry[25] == 0)
        return 0;
    if (sel <= 9) {
        p = entry + 2;
    } else {
        sel -= 10;
        if ((unsigned char)sel > 1)
            return 0;
        p = entry + 12;
    }
    return p[sel];
}

__attribute__((section(".text.w14d_08010498")))
unsigned int FlagBitClear_10498(unsigned char a)
{
    unsigned char *p = (unsigned char *)0x02005168;
    unsigned char v;
    if (a == 1)
        p += 20;
    v = p[16];
    if ((v & 2) != 0) {
        if ((v & 1) != 0) {
            register unsigned int t __asm__("r0");
            t = v & -2;
            p[16] = (unsigned char)t;
        }
        return 0;
    } else {
        return 1;
    }
}

__attribute__((section(".text.w14d_0802fc4c")))
void F_2FC4C(unsigned int *p, unsigned char x, unsigned short y)
{
    unsigned char xx = x;
    register unsigned short yy __asm__("r2") = y;
    register unsigned int *qq __asm__("r1");
    register unsigned int pp __asm__("r0");
    register unsigned short tt __asm__("r3");
    if (xx == 2)
        return;
    qq = (unsigned int *)*p;
    __asm__ volatile("" : "=r" (pp) : "0" (0x271));
    if (*(unsigned short *)((unsigned char *)qq + 8) != pp)
        return;
    tt = *(unsigned short *)((unsigned char *)qq + 10);
    __asm__ volatile("" : "+r" (tt));
    {
        register unsigned short s __asm__("r0");
        s = tt + yy;
        *(unsigned short *)((unsigned char *)qq + 10) = s;
    }
}

__attribute__((section(".text.w14d_08047510")))
void sub_08047510(unsigned char *a, unsigned int b)
{
    register unsigned char *aa __asm__("r2") = a;
    register unsigned int bb __asm__("r3") = b;
    unsigned char t = aa[4];
    signed char ss;
    if (((signed char *)aa)[4] == 0)
        return;
    aa[4] = t - 1;
    __asm__ volatile("" ::: "memory");
    ss = ((signed char *)aa)[4];
    {
        register unsigned int addr __asm__("r0");
        register unsigned int pool __asm__("r2");
        addr = ss * 2 + bb;
        __asm__ volatile("" : "=r" (pool) : "0" (0xFFFF8000));
        *(unsigned short *)addr = ss + pool;
    }
}

__attribute__((section(".text.w14d_0804d634")))
void sub_0804D634(unsigned char *a, unsigned int b)
{
    register unsigned char *aa __asm__("r2") = a;
    register unsigned int v __asm__("r3");
    register unsigned int pool __asm__("r0");
    __asm__ volatile("lsl %0, %0, #16\n\tlsr %0, %0, #16" : "+r" (b));
    v = *(unsigned int *)(aa + 52);
    __asm__ volatile("" : "=r" (pool) : "0" (0x68736D53));
    if (v != pool)
        return;
    *(unsigned short *)(aa + 30) = (unsigned short)b;
    {
        register unsigned short c __asm__("r4");
        register int t __asm__("r0");
        c = *(unsigned short *)(aa + 28);
        t = b;
        t = t * c;
        t >>= 8;
        *(unsigned short *)(aa + 32) = (unsigned short)t;
    }
}

__attribute__((section(".text.w14d_0804da34")))
void BuildU32_4DA34(unsigned int dummy, unsigned int *ctx)
{
    register unsigned char *s __asm__("r2");
    register unsigned int v __asm__("r4");
    register unsigned int mask __asm__("r0");
    register unsigned int sh __asm__("r3");

    s = (unsigned char *)ctx[16];

    __asm__ volatile("" : "=r" (mask) : "0" (0xFFFFFF00));
    v &= mask;
    v |= s[0];

    sh = (unsigned int)s[1] << 8;
    __asm__ volatile("" : "=r" (mask) : "0" (0xFFFF00FF));
    v &= mask;
    v |= sh;

    sh = (unsigned int)s[2] << 16;
    __asm__ volatile("" : "=r" (mask) : "0" (0xFF00FFFF));
    v &= mask;
    v |= sh;

    sh = (unsigned int)s[3] << 24;
    __asm__ volatile("" : "=r" (mask) : "0" (0x00FFFFFF));
    v &= mask;
    v |= sh;

    ctx[10] = v;
    s += 4;
    ctx[16] = (unsigned int)s;
}

__attribute__((section(".text.w14d_0804a884")))
void Copy4Words_4A884(unsigned int *src)
{
    unsigned char *p;
    unsigned int *dst;
    __asm__ volatile("" : "=r" (p) : "0" (0x0200BD20));
    {
        register unsigned char *q __asm__("r3") = p;
        q += 127;
        q[0] = 0;
        q -= 1;
        q[0] = 0;
        dst = (unsigned int *)(p + 140);
    }
    {
        register unsigned int *s __asm__("r0") = src;
        register unsigned int *d __asm__("r1") = dst;
        __asm__ volatile(
            "ldmia %0!, {r2, r3, r4}\n\t"
            "stmia %1!, {r2, r3, r4}\n\t"
            "ldr %0, [%0]\n\t"
            "str %0, [%1]"
            : "+r" (s), "+r" (d)
            :
            : "r2", "r3", "r4", "memory");
    }
}
