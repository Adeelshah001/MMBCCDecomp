/* Wave 36-D v8 (inline-asm sum) (sum pinned r1, true extent 68): 0x080129f8 — tbl pinned r0 + barrier at branch entry. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u8 Worker_0804DCD0(u8 *s, u32 v);
__asm__(".set Worker_0804DCD0, 0x0804dcd0");
__attribute__((section(".text.w36d_080129f8")))
void Sub_080129F8(u8 *s)
{
    register u8 *ss __asm__("r2") = s;
    register u8 *q __asm__("r1") = ss;
    q += 124;
    if (*q != 39) {
        register u32 *tbl __asm__("r0") = (u32 *)0x08223d6c;
        __asm__ volatile("" : "+r"(tbl));
        Worker_0804DCD0(ss, tbl[*q]);
    } else {
        register u32 *tbl __asm__("r0") = (u32 *)0x08223d6c;
        register u8 b1 __asm__("r3");
        register u8 b2 __asm__("r4");
        register int sum __asm__("r1");
        __asm__ volatile("" : "+r"(tbl));
        b1 = q[2];
        b2 = *q;
        __asm__ volatile("add %0, %1, %2" : "=r"(sum) : "r"(b1), "r"(b2));
        Worker_0804DCD0(ss, tbl[sum]);
    }
}
