/* ChipState_0801C030 @0x0801C030 (216 B, main agbcc). Wave 29-B.
   Note: extern ChipInit_0801B98C uses s32/s16 params (s32-laundering idiom:
   suppresses post-asm sign-extension; runtime-correct, byte-verified) vs the
   true u16 prototype. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern void SetBit16(u8 *s, u8 bit);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u32 *ChipInit_0801B98C(u8 a, u8 b, u8 c, s32 d, s16 e, u8 *f);
extern void MaxAssign_17(u8 *s, u8 v);

__attribute__((section(".text.w29b_0801c030")))
u32 ChipState_0801C030(u8 *s)
{
    register u8 *sp __asm__("r5") = s;
    u8 vv = sp[13];
    switch (vv) {
    case 0:
        if ((u8)(sp[119] - 3) > 1)
            break;
        SetBit16(*(u8 **)(sp + 44), 3);
        ChipSlot_IncUse(sp, 1);
        sp[18] = 3;
        sp[19] = vv;
        sp[13]++;
        break;
    case 1: {
        u8 b;
        u32 c;
        s32 d;
        s16 e;

        u8 *p1;
        u32 tbl, sh;
        s16 *t1, *t2;
        if (--sp[18] != 0)
            break;
        p1 = (u8 *)0x0822688b;
        __asm__ volatile("" : "+r"(p1));
        vv = sp[19];
        b = ((u8 *)(u32)vv)[(u32)p1];
        { register u32 a35 __asm__("r0") = (u32)(sp + 35);
          __asm__ volatile("ldrb %0, [%0]" : "+r"(a35));
          c = (a35 << 28) >> 28; }
        tbl = 0x08226894;
        __asm__ volatile("" : "+r"(tbl));
        sh = (u32)vv << 3;
        t1 = (s16 *)(sh + tbl);
        __asm__ volatile("movs r6, #0\n\tldrsh %0, [%1, r6]" : "=r"(d) : "r"(t1) : "r6");
        __asm__ volatile("" : "+r"(tbl));
        tbl += 4;
        t2 = (s16 *)(sh + tbl);
        e = t2[0];
        ChipInit_0801B98C(2, b, (u8)c, d, e, *(u8 **)(sp + 44));
        sp[18] = 10;
        { register u8 *qq __asm__("r1");
          register u8 ii __asm__("r2");
          u32 nv;
          nv = sp[19] + 1;
          sp[19] = (u8)nv;
          qq = (u8 *)0x08226887;
          __asm__ volatile("" : "+r"(qq));
          ii = sp[17];
          qq = (u8 *)((u32)ii + (u32)qq);
          if ((u8)nv != *qq)
              break; }
        sp[18] = 20;
        sp[13]++;
        break;
    }
    case 2:
        if (--sp[18] != 0)
            break;
        MaxAssign_17(*(u8 **)(sp + 44), 7);
        return 1;
    default:
        break;
    }
    return 0;
}

/* Force zero-fill (not 0x46c0 nop) for section-end alignment padding */
__asm__(
    ".section .text.w29b_0801c030\n"
    ".align 2, 0\n"
    ".previous"
);
