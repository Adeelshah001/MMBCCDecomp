/* Wave 194 LANDING (2026-11-02 user ruling, sanctioned exception):
 * 0x080158DC bppinr0 pin, LANDED 0-diff (364/364 B, old_agbcc -O2 AND -Os
 * with identical SHA 0b80c682; the -O2 build is landed, matching Makefile CFLAGS).
 * Sanctioned trick: register pin (bp->r0); compiler-steering only, invents no
 * logic. Sanctioned FOR THIS FUNCTION ONLY per the 2026-11-02 ruling;
 * invented-logic tricks remain banned.
 * Section tag renamed w176f_ -> w194f_ at landing; no .set stub dropped
 * (audit: no stub symbol has a real definition in mmbcc/src/).
 */
/* Wave 176 Worker F restage of w176f_080158DC_bppinr0_oldO2.c (verbatim except section tag). */
/* Wave 169 Worker F restage of w168f_080158DC_bppinr0_oldO2.c (verbatim except section tag). */
/* Wave 168 Worker F restage of w167f_080158DC_bppinr0_oldO2.c (verbatim except section tag). */
/* Wave 167 Worker F restage of w166f_080158DC_bppinr0_oldO2.c (verbatim except section tag). */
/* Wave 166-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w165f_/w165f_080158DC_bppinr0_oldO2.c except section tag renamed to w166f_080158DC_bppinr0_oldO2; see RESULTS.md. */
/* Wave 165-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w122b_/w122b_080158dc_bppinr0_oldO2.c except section tag renamed to w166f_080158DC_bppinr0_oldO2; see RESULTS.md. */
/* Wave 122 Worker B (STAGED ONLY, DO-NOT-LAND): re-verified Wave 121 best, section renamed w121b/w121c->w122b only. */
/* W121B RE-VERIFY (confirmation only, STAGE ONLY, not landed, NOT a claim):
 * base: Wave 120 base file of the same form/compiler (this header block is a
 *   comment and does not change built bytes).
 * compiler+flags verified this wave: old_agbcc -O2 -mthumb-interwork
 *   ONLY. The -Os byte-identity is WORKER-REPORTED (Wave 112
 *   coordinator note: no staged -Os file exists); it was NOT
 *   re-verified in Wave 121 and must not be presented as verified.
 * built size: 364 B, TRUE extent: 364 B (next fn 0x08015A48 - 0x080158DC).
 * over/full diffs: 0 / 0 under -O2 (verified this wave).
 * built SHA-256 = ROM-slice SHA-256 =
 *   0b80c682177820f87d2541f7cca7c464517e2be10a4fef75572f2e7c14f4a107.
 * diff offsets: none.
 * semantic re-read: single change from v5 is register u8 *bp __asm__("r0") =
 *   &buf[0]; prologue add r0,sp,#4; movs r1,#48; strb r1,[r0,#0] (bp pinned r0);
 *   rest of function byte-identical to ROM under -O2 (verified).
 * FLAG STATUS: FLAGGED — pin-landability ruling still needed. Evidence ONLY,
 *   NOT landable, NOT presented as a clean claim. Clean floor stays 3.
 */
/* Wave 73-A carried best (Wave 72-A v5, unchanged code; Wave 73 v6/v7/v8 tried, none beat it): 0x080158DC, fresh. TRUE extent 364 B: code 360 B
 * through bx at 0x15A42 (epilogue), plus 2 pad + pool word at
 * 0x15A44 (0xFFFFC400); next function 0x08015A48. void F(u8 *s).
 * Prologue stores 48 at sp+4 (u8 buf[4] at sp+4; sp+0 is the
 * outgoing 5th-arg slot for the case-3 1AB94 call) and sets
 * q = s + 124 (two-step adds, since 124 > imm3 with Rd != Rn).
 * Switch on s[14] (8 cases); shared advance is s[14]++ then the
 * D9FC epilogue. Case 3: 174A4([s+44], 3), then 1AB94(buf[s[17]],
 * s[35] & 0xF, (s16)(tab[s[124]].a + 0x2200),
 * (s16)(tab[s[124]].b - 0xF00), [s+44] word). .set stubs are
 * verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

u32 Call_0800DD2C(u8 *s, u32 a, u32 b);
u16 Call_08011F50(u8 *s);
void Call_0800D9EC(u8 *s, u32 a);
void Call_0800D9FC(u8 *s);
u32 Call_080174A4(u32 a, u32 b);
u32 Call_08017474(u32 a);
u32 Call_08017464(u32 a);
u32 Call_08011F68(u8 *s, u32 a);
void Call_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w194f_080158dc_bppinr0_oldO2")))
void sub_080158DC(u8 *s)
{
    u8 buf[4];
    u8 *q;
    register u8 *bp __asm__("r0") = &buf[0];
    *bp = 48;
    q = s + 124;
    switch (s[14]) {
    case 0:
        Call_0800DD2C(s, 0xFFFFC400, 0);
        Call_0800D9EC(s, 2);
        s[14]++;
        break;
    case 1:
        if (Call_08011F50(s)) {
            Call_0800DD2C(s, 0x1400, 0);
            Call_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Call_08011F50(s)) {
            Call_0800D9EC(s, 15);
            s[14]++;
        }
        break;
    case 3:
        if (Call_08011F50(s)) {
            u8 bb;
            u32 nb;
            u8 *tbl;
            u16 *ent;
            u16 a;
            u16 b;
            Call_080174A4(*(u32 *)(s + 44), 3);
            bb = buf[s[17]];
            nb = ((u32)s[35] << 28) >> 28;
            tbl = TABLE_08223ED8;
            ent = (u16 *)(tbl + *q * 4);
            a = ent[0];
            b = ent[1];
            Call_0801AB94(bb, nb, (s16)(a + 0x2200), (s16)(b - 0xF00),
                          *(u32 *)(s + 44));
            Call_0800D9EC(s, 16);
            s[14]++;
        }
        break;
    case 4:
        if (Call_08011F50(s))
            s[14]++;
        break;
    case 5:
        if ((u8)Call_08017474(*(u32 *)(s + 44)) > 6) {
            Call_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 6:
        if (Call_08011F50(s)) {
            Call_0800DD2C(s, 0xFFFFC400, 0);
            Call_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 7:
        if (Call_08011F50(s)) {
            Call_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Call_0800DD2C(s, 0xFFFFC400, 0);
            Call_0800D9EC(s, 0);
            q[4] = 0;
            Call_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    Call_0800D9FC(s);
}

__asm__(
    ".globl Call_0800DD2C\n.set Call_0800DD2C, 0x0800DD2C\n"
    ".globl Call_08011F50\n.set Call_08011F50, 0x08011F50\n"
    ".globl Call_0800D9EC\n.set Call_0800D9EC, 0x0800D9EC\n"
    ".globl Call_0800D9FC\n.set Call_0800D9FC, 0x0800D9FC\n"
    ".globl Call_080174A4\n.set Call_080174A4, 0x080174A4\n"
    ".globl Call_08017474\n.set Call_08017474, 0x08017474\n"
    ".globl Call_08017464\n.set Call_08017464, 0x08017464\n"
    ".globl Call_08011F68\n.set Call_08011F68, 0x08011F68\n"
    ".globl Call_0801AB94\n.set Call_0801AB94, 0x0801AB94\n"
    ".globl TABLE_08223ED8\n.set TABLE_08223ED8, 0x08223ED8\n"
);
