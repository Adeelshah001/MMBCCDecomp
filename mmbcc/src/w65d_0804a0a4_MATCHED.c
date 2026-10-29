/* Wave 65-D RECOMMENDED: 0x0804A0A4, MATCHED 0 diffs over 332 B
 * (old_agbcc -O2 -mthumb-interwork; main agbcc gives 4 diffs).
 * True extent 332 B: 302 code (0x4A0A4-0x4A1D1) + 2 pad (00 00 @0x4A1D2)
 * + 28 pool (0x4A1D4-0x4A1EF); next function @0x4A1F0 tiles exactly.
 * Pools re-derived from raw LE bytes:
 *   mid pool @0x4A120: 0x46A8, 0x082344EC, 0x46AA, 0x46B8, 0x081720B0
 *   end pool @0x4A1D4: 0x081720B0, 0x08234B7C, 0x46B8, 0x08234BFC,
 *                      0x46A8, 0x02004CE0, 0x46A9
 * Structure: u8 i = 0, u8 j = s[0x46A8]; loop while j < s[0x46A8]+3;
 * per iter: blit A always; if j < s[0x46AA]: bit test on s[28] flags
 * with bit b = byte at s+j+0x46B8 selects CondRectFill stack arg *T vs
 * T[2]; then blits C/D via *V1[q[0x46B8]] / *V2[q[0x46B8]] (q = s+j,
 * byte reloaded from memory after the B call). Exit writes G4[20]=20,
 * G4[21] = s[0x46A9]*16+24, then calls ShiftPairCfg_4A1F0(s).
 * 6 bl sites: A=4A0DA (6A54), B1=4A11A (62B4), B2=4A14E (62B4),
 * C=4A170 (6A54), D=4A18A (6A54), E=4A1BE (4A1F0).
 * Key codegen notes: (1) the e=2 blit arg is a literal (NOT a variable;
 * v1's e variable swapped i/e homes and cost 23 diffs); (2) the bit
 * test MUST materialize m = flags & (1<<b) before assigning q, and b
 * MUST be computed via integer arithmetic (j + (u32)s) so the temp
 * lands in r2 with (r6,r7) operand order -- pointer-arithmetic (s+j)
 * canonicalizes to (r7,r6) and costs exactly 1 diff; (3) CondRectFill's
 * y parameter is declared s8 here (its own source says u8 and casts
 * internally) to reproduce the caller's lsl#24/asr#24 sign extension.
 * Semantic re-read PASS (see RESULTS.md).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u32 *U_082344EC;
extern u32 *T_081720B0;
extern u32 *V1_08234B7C[];
extern u32 *V2_08234BFC[];
extern u16 G4_02004CE0[];

void Gfx_BlitRequest(u32 a, u16 b, u16 c, u8 d, u8 e);
void CondRectFill_080062B4(u8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);
void ShiftPairCfg_4A1F0(u8 *p);

__attribute__((section(".text.w65d_0804a0a4")))
void sub_0804A0A4(u8 *s)
{
    u8 i;
    u8 j;


    for (i = 0, j = s[0x46A8]; j < s[0x46A8] + 3; i++, j++) {
        Gfx_BlitRequest((u32)U_082344EC, 2, 2 * i + 3, 24, 2);
        if (j < s[0x46AA]) {
            u8 b = *(u8 *)(j + (u32)s + 0x46B8);
            u32 m = *(u32 *)(s + 28) & (1 << b);
            u8 *q = s + j;
            if (m != 0)
                CondRectFill_080062B4(2, (s8)(2 * i + 3), 2, 2, 110, 3, *T_081720B0);
            else
                CondRectFill_080062B4(2, (s8)(2 * i + 3), 2, 2, 110, 3, T_081720B0[2]);
            Gfx_BlitRequest((u32)*V1_08234B7C[q[0x46B8]], 4, 2 * i + 3, 8, 2);
            Gfx_BlitRequest((u32)*V2_08234BFC[q[0x46B8]], 12, 2 * i + 3, 14, 2);
        }
    }
    G4_02004CE0[20] = 20;
    G4_02004CE0[21] = (s[0x46A9] << 4) + 24;
    ShiftPairCfg_4A1F0(s);
}

__asm__(
    ".globl U_082344EC\n.set U_082344EC, 0x082344EC\n"
    ".globl T_081720B0\n.set T_081720B0, 0x081720B0\n"
    ".globl V1_08234B7C\n.set V1_08234B7C, 0x08234B7C\n"
    ".globl V2_08234BFC\n.set V2_08234BFC, 0x08234BFC\n"
    ".globl G4_02004CE0\n.set G4_02004CE0, 0x02004CE0\n"
);
