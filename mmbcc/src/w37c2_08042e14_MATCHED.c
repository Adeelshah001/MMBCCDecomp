/* W37-C2: 0x08042e14, 172 B.
 * Blit-request sequence: T=0x08232d50 (s8 table).
 * Blit(*0x08232bac, (s8)T[0]+2, (s8)T[1]+1, 7, 2);
 * if s[21]>4 Blit(*0x08232bb4, +2, +3, 7, 2);
 * if s[21]>7 Blit(*0x08232bbc, +2, +5, 7, 2);
 * else Blit(*0x08232ba4, +2, +5, 7, 2);
 * then CondTilemapRectFill(1, 7, 2*s[22]+3, 2).
 * Callees: Gfx_BlitRequest 0x08006a54 (MATCHED),
 * CondTilemapRectFill_08007378 0x08007378 (MATCHED).
 * Pools (LE): 0x08232bac, 0x08232d50, 0x08232bb4, 0x08232bbc,
 * 0x08232ba4. ldrsb via inline asm (agbcc never emits ldrsb).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Gfx_BlitRequest(u32 a, int b, int c, u8 d, u8 e);
extern void CondTilemapRectFill_08007378(u8 mode, u16 x, int y, u8 z);

__attribute__((section(".text.w37c2_08042e14")))
void Sub_08042E14(u8 *s)
{
    register s8 *t __asm__("r4");
    register int e __asm__("r6");
    int b;
    int c;
    {
        u32 p1 = *(u32 *)0x08232bac;
        t = (s8 *)0x08232d50;
        __asm__ volatile("" : "+r"(t));
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 1;
        e = 2;
        Gfx_BlitRequest(p1, b, c, 7, e);
    }
    if (s[21] > 4) {
        u32 p2 = *(u32 *)0x08232bb4;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 3;
        Gfx_BlitRequest(p2, b, c, 7, e);
    }
    if (s[21] > 7) {
        u32 p3 = *(u32 *)0x08232bbc;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 5;
        Gfx_BlitRequest(p3, b, c, 7, e);
    } else {
        u32 p4 = *(u32 *)0x08232ba4;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 5;
        Gfx_BlitRequest(p4, b, c, 7, e);
    }
    {
        register int b22 __asm__("r5");
        int y;
        __asm__ volatile("ldrb %0, [%1, #22]" : "=r"(b22) : "r"(s));
        y = ((b22 << 17) + (192 << 10)) >> 16;
        CondTilemapRectFill_08007378(1, 7, y, 2);
    }
}

