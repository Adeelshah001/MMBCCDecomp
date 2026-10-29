/* 0x0804AF20 (112 B): InitRec28_4AF20 — zero a 28-byte record at p, then fill
 * fields from table lookups / derived values:
 *   p[8]  = (u16)TblGetByte_24384(a)   p[10] = (u16)TblGetByte_24384(c)
 *   p[12] = Sub200_08024514((u8)b)     p[14] = Sub200_08024514((u8)d)
 *   p[20] = a                          p[22] = c
 * (bytes 0-7, 16-19, 24-27 stay zero).
 *
 * MATCHED 0-diff via main agbcc -O2 + .s fixups (see staging/wave24_A/
 * sed_0804af20.sed; precedent: wave-23 0x08002CB0 Makefile sed rule).
 * Key findings (docs/match_notes_wave24_A.md):
 * - Tail stores are p+20=a / p+22=c (re-decode: 82a7=strh r7,[r4,#20] with
 *   r7=a; objdump scales strh imm by 2). Wave-23's "=b" reading was wrong;
 *   with =a/=c, b is dead after call 1, so b stays in caller-saved r2 —
 *   the "b live across 4 calls" wall vanishes.
 * - Loop 0x10000 materialization is in-loop in ROM (movs r5,#128 /
 *   lsls r5,#9); gcc 2.9-arm-000512 hoists it out of any call-free loop
 *   (verified: no -fno-* flag defeats the hoist; only loops containing
 *   calls keep it in-loop). Fixed via sed.
 * - Explicit u16-increment idiom t=((u32)i<<16)+0x10000; i=t>>16 gives
 *   ROM's lsls/movs128/lsls9/adds/lsrs shape (from wave 22).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 Sub200_08024514(u8 v);

/* TblGetByte_24384 @0x08024384 is matched but BYTE()-emitted in ldscript
   (its C section is discarded), so no global symbol survives the link.
   Absolute-symbol idiom per w21a_0803affc.c. */
__asm__(
    ".set TblGetByte_24384, 0x08024384\n"
);
u8 TblGetByte_24384(u16 a);

__attribute__((section(".text.w24a_0804AF20")))
void InitRec28_4AF20(u8 *p, u16 a, u16 b, u16 c, u16 d)
{
    u8 *q = p;
    u16 i;
    u32 t;
    for (i = 0; i < 28; i = (t = ((u32)i << 16) + 0x10000) >> 16) {
        *q++ = 0;
    }
    *(u16 *)(p + 12) = Sub200_08024514((u8)b);
    *(u16 *)(p + 14) = Sub200_08024514((u8)d);
    *(u16 *)(p + 8) = TblGetByte_24384(a);
    *(u16 *)(p + 10) = TblGetByte_24384(c);
    *(u16 *)(p + 20) = a;
    *(u16 *)(p + 22) = c;
}
