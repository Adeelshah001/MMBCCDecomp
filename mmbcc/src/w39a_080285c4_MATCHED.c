/* W39-A: 0x080285c4, 376 B (TSV; next 0x0802873c). Twin of 0x08048084
 * (identical instruction stream, identical pools).
 * Memset buf[8]=0. If (s[10]&1): q=s+6832; Copy4(q,buf);
 *   Blit(buf,4,4,4,0); v=(u8)F_251D8(q); CondRectFill(v,10,4,0,0);
 *   Sub_6DD8(s[5959],5,7,2,0); Sub_6DD8(s[5958],8,7,2,0);
 *   Sub_6DD8(s[5957],11,7,2,0); else Sub_6DD8(0,5/8/11,7,2,0).
 * If (s[10]&2): q=s+12772; Copy4(q,buf); Blit(buf,18,4,4,0);
 *   v=(u8)F_251D8(q); CondRectFill(v,24,4,0,0);
 *   Sub_6DD8(s[11899],19,7,2,0); Sub_6DD8(s[11898],22,7,2,0);
 *   Sub_6DD8(s[11897],25,7,2,0); else Sub_6DD8(0,19/22/25,7,2,0).
 * Intended section: .text (coordinator assigns).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void MemsetAligned_4E008(u8 *dst, int val, int n);
extern void Copy4_2518C(u8 *q, u8 *buf);
extern void Gfx_BlitRequest(u8 *buf, int a, int b, int c, int d);
extern int F_080251D8(u8 *q);
extern void CondRectFill_080070F0(u8 v, int a, int b, int c);
extern void Sub_08006DD8(u8 v, int a, int b, int c, int d);

__attribute__((section(".text.w39a_080285c4")))
void Sub_080285C4(u8 *s)
{
    u8 buf[8];
    u8 *q;
    u8 v;

    MemsetAligned_4E008(buf, 0, 8);
    if (s[10] & 1) {
        q = s + 6832;
        Copy4_2518C(q, buf);
        Gfx_BlitRequest(buf, 4, 4, 4, 0);
        v = F_080251D8(q);
        CondRectFill_080070F0(v, 10, 4, 0);
        Sub_08006DD8(s[5959], 5, 7, 2, 0);
        Sub_08006DD8(s[5958], 8, 7, 2, 0);
        Sub_08006DD8(s[5957], 11, 7, 2, 0);
    } else {
        Sub_08006DD8(0, 5, 7, 2, 0);
        Sub_08006DD8(0, 8, 7, 2, 0);
        Sub_08006DD8(0, 11, 7, 2, 0);
    }
    if (s[10] & 2) {
        q = s + 12772;
        Copy4_2518C(q, buf);
        Gfx_BlitRequest(buf, 18, 4, 4, 0);
        v = F_080251D8(q);
        CondRectFill_080070F0(v, 24, 4, 0);
        Sub_08006DD8(s[11899], 19, 7, 2, 0);
        Sub_08006DD8(s[11898], 22, 7, 2, 0);
        Sub_08006DD8(s[11897], 25, 7, 2, 0);
    } else {
        Sub_08006DD8(0, 19, 7, 2, 0);
        Sub_08006DD8(0, 22, 7, 2, 0);
        Sub_08006DD8(0, 25, 7, 2, 0);
    }
}

__asm__(".set MemsetAligned_4E008, 0x0804e008");
__asm__(".set F_080251D8, 0x080251d8");
__asm__(".set Sub_08006DD8, 0x08006dd8");

__asm__(".hword 0");
