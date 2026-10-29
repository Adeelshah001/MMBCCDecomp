/* 0x0801C428: ChipFxTick_0801C428 (280 B incl 2 pad). v2a:
   call-1 rewrite: idxv->r1, sh->r0, base->r1 via pins; a1 unpinned (falls to r3);
   b1 via explicit ldrsh asm; zero-fill pad. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;

void SetBit16(u8 *s, u8 bit);
void MaxAssign_17(u8 *s, u8 v);
u32 *ChipInit_0801B98C(u8 a, u8 b, u8 c, s32 d, s32 e, u8 *f); /* s32-laundered: 5th arg is 4B stack slot either way */

#define NIBBLE(q, n) { n = ((u32)*(q) << 28) >> 28; __asm__ volatile("" : "+r"(n)); }

__attribute__((section(".text.w30d_0801c428")))
int ChipFxTick_0801C428(u8 *p) {
    u8 state = p[13];
    switch (state) {
    case 0:
        SetBit16(*(u8 **)(p + 44), 3);
        p[18] = 5;
        p[19] = state;
        p[13]++;
        break;
    case 1: {
        u8 *q;
        s16 *t1;
        s16 *t2;
        u8 n1, n2, n3;
        s32 a1;
        s32 b1; s16 a2, b2, a3, b3;
        if ((s8)--p[18] != 0)
            return 0;
        q = p + 35;
        NIBBLE(q, n1);
        t1 = (s16 *)0x082268C8;
        { register unsigned idxv __asm__("r1") = p[19];
          register u32 sh __asm__("r0") = idxv * 8;
          register s16 *b __asm__("r1") = (s16 *)(sh + (u32)t1);
          register s32 a1r __asm__("r3");
          __asm__ volatile("movs r5, #0\n\tldrsh %0, [%1, r5]"
                           : "=r"(a1r) : "r"(b) : "r5");
          a1 = a1r;
          t2 = t1 + 2;
          sh += (u32)t2;
          __asm__ volatile("movs r1, #0\n\tldrsh %0, [%1, r1]"
                           : "+r"(sh) : : "r1");
          b1 = sh; }
        ChipInit_0801B98C(2, 1, n1, a1, b1, *(u8 **)(p + 44));
        { int idx = p[19];
          p[19] = ++idx;
          NIBBLE(q, n2);
          a2 = t1[idx * 4];
          b2 = t2[idx * 4];
          ChipInit_0801B98C(2, 0, n2, a2, b2, *(u8 **)(p + 44)); }
        { int idx = p[19];
          p[19] = ++idx;
          NIBBLE(q, n3);
          a3 = t1[idx * 4];
          b3 = t2[idx * 4];
          ChipInit_0801B98C(2, 0, n3, a3, b3, *(u8 **)(p + 44)); }
        { register int idx __asm__("r1") = p[19];
          u32 base = 0x082268C4;
          u8 v;
          p[19] = ++idx;
          p[18] = 12;
          __asm__ volatile("" : "+r"(base));
          v = ((u8 *)base)[p[17]];
          if ((u8)idx < v)
              return 0;
          p[18] = 20; }
        p[13]++;
        break;
    }
    case 2:
        if ((s8)--p[18] != 0)
            return 0;
        MaxAssign_17(*(u8 **)(p + 44), 7);
        return 1;
    default:
        return 0;
    }
    return 0;
}

/* Force zero-fill (not 0x46c0 nop) for section-end alignment padding */
__asm__(".section .text.w30d_0801c428\n.align 2, 0\n.previous");

