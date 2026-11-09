/* Wave 194 LANDING (2026-11-02 user ruling, sanctioned exception):
 * 0x08037DE0 P8, LANDED 0-diff (344/344 B, old_agbcc -O2, SHA 2c9f060d).
 * Sanctioned tricks: inline-asm ldrsb + register pins (p->r6, v->r4);
 * compiler-steering only, invents no logic. Sanctioned FOR THIS FUNCTION ONLY
 * per the 2026-11-02 ruling; invented-logic tricks remain banned.
 * Section tag renamed w176f_ -> w194f_ at landing; no .set stub dropped
 * (audit: no stub symbol has a real definition in mmbcc/src/).
 */
/* Wave 176 Worker F restage of w176f_08037DE0_p8_oldO2.c (verbatim except section tag). */
/* Wave 169 Worker F restage of w168f_08037DE0_p8_oldO2.c (verbatim except section tag). */
/* Wave 168 Worker F restage of w167f_08037DE0_p8_oldO2.c (verbatim except section tag). */
/* Wave 167 Worker F restage of w166f_08037DE0_p8_oldO2.c (verbatim except section tag). */
/* Wave 166-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w165f_/w165f_08037DE0_p8_oldO2.c except section tag renamed to w166f_08037DE0_p8_oldO2; see RESULTS.md. */
/* Wave 165-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w122b_/w122b_08037de0_p8_oldO2.c except section tag renamed to w166f_08037DE0_p8_oldO2; see RESULTS.md. */
/* Wave 122 Worker B (STAGED ONLY, DO-NOT-LAND): re-verified Wave 121 best, section renamed w121b/w121c->w122b only. */
/* W121B RE-VERIFY (confirmation only, STAGE ONLY, not landed, NOT a claim): base Wave 120 file, section name only otherwise; this header line is a comment and does not change built bytes. */
/* Wave 72-D P8: 0x08037DE0. STANDALONE 0-DIFF (see RESULTS.md) -- FLAGGED,
 * NOT A LANDING CLAIM: needs coordinator sanction for the register pins
 * (p->r6, v->r4) and the inline-asm ldrsb before any landing.
 * TRUE (tiling) extent 344 B = 340 code through bx @0x37F32 + 4 trailing
 * pool @0x37F34 (0x469C, referenced by the else-branch ldr @0x37F18);
 * next fn @0x37F38. This CORRECTS the W70/W71 "340 B, no pool" tiling:
 * the 344 B build is byte-identical to the ROM slice, proving the pool
 * word belongs to this function.
 * u8 F(u8 *s): flag = 0 (r8); Call_08004F18(0); p = s + 18077;
 * v = ldrsb *p via sanctioned-class inline asm (agbcc never emits ldrsb
 * from C; w36a precedent), v held in r4 as s32 because the asm already
 * sign-extends -- this removes the redundant lsl/asr switch extension
 * that blocked P2 (s8 v). p pinned r6, s lands in r7, flag in r8, G ptr
 * in r5: the ROM allocation. Case-2 address step uses a named pointer
 * q = s + s[18073]*12 with q[288] (exactly s[288 + s[18073]*12]); the
 * named pointer is what flips the middle adds to ROM's operand order
 * (adds r0, r7, r0) -- the direct-index form gives adds r0, r0, r7
 * (P4, 2 diffs, commutative but not byte-identical).
 * switch (v):
 * case 0: (*p)++; fallthrough.
 * case 1: idx = (u8)(Call_08024384(4096) - 50);
 *         if (Call_0800B368(TABLE_A[idx], G_B, G_C, 0) != 0) {
 *             Call_0800B3F8(0, *(u32 *)TABLE_D[s[18072]], 8);
 *             s[18077]++;
 *         }
 *         break;
 * case 2: G_PTR[20] |= 1;
 *         if (Call_0800B308() != 0) {
 *             if ((s8)G_PTR[8] == 0) {
 *                 s[18076] = v; *p = flag;
 *                 Call_08011DD0(4, TABLE_E[s[18073]]);
 *                 Call_08011DD0(6, s[18073]);
 *                 Call_08011DD0(7, 0);
 *                 if (s[18073] == 3) Call_08011D68(54, 1);
 *                 if (s[288 + s[18073] * 12] <= 98)
 *                     s[288 + s[18073] * 12]++;
 *                 s[18078] = flag; s[18083] = flag;
 *                 Call_0804A328(); flag = 1;
 *             } else {
 *                 s[18076] = flag; *p = 5;
 *             }
 *         }
 *         break;
 * default: break;
 * tail: Call_08004F80(); return flag.
 * Pool constants from raw LE bytes: TABLE_A 0x08230CFC, G_B 0x0823014C,
 * G_C 0x08230154, TABLE_D 0x08230D84, G_PTR 0x02004E40,
 * TABLE_E 0x08230450; offsets 18072 (0x4698), 18073 (0x4699),
 * 18076 (0x469C), 18077 (0x469D), 18078 (0x469E).
 * .set stubs are verification-only; coordinator strips landed-callee stubs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void Call_08004F18(u32 x);
u32 Call_08024384(u32 x);
u8 Call_0800B368(u32 a, u32 b, u32 c, u32 d);
void Call_0800B3F8(u32 a, u32 b, u32 c);
u8 Call_0800B308(void);
void Call_08011DD0(u8 a, u8 b);
void Call_08011D68(u8 a, u8 b);
void Call_0804A328(void);
void Call_08004F80(void);

extern u32 TABLE_A_08230CFC[];
extern u32 G_0823014C;
extern u32 G_08230154;
extern u32 TABLE_D_08230D84[];
extern u8 G_02004E40[];
extern u8 TABLE_E_08230450[];

__attribute__((section(".text.w194f_08037de0_p8_oldO2")))
u8 sub_08037DE0(u8 *s)
{
    u8 flag = 0;
    register u8 *p __asm__("r6");
    register s32 v __asm__("r4");
    Call_08004F18(0);
    p = s + 18077;
    __asm__ volatile("movs r4, #0\n\tldrsb %0, [%1, r4]" : "=r" (v) : "r" (p));
    switch (v) {
    case 0:
        (*p)++;
    case 1: {
        u8 idx = (u8)(Call_08024384(4096) - 50);
        if (Call_0800B368(TABLE_A_08230CFC[idx], G_0823014C, G_08230154, 0) != 0) {
            Call_0800B3F8(0, *(u32 *)TABLE_D_08230D84[s[18072]], 8);
            s[18077]++;
        }
        break;
    }
    case 2:
        G_02004E40[20] |= 1;
        if (Call_0800B308() != 0) {
            if ((s8)G_02004E40[8] == 0) {
                s[18076] = v;
                *p = flag;
                Call_08011DD0(4, TABLE_E_08230450[s[18073]]);
                Call_08011DD0(6, s[18073]);
                Call_08011DD0(7, 0);
                if (s[18073] == 3)
                    Call_08011D68(54, 1);
                {
                    u8 *q = s + s[18073] * 12;
                    if (q[288] <= 98)
                        q[288]++;
                }
                s[18078] = flag;
                s[18083] = flag;
                Call_0804A328();
                flag = 1;
            } else {
                s[18076] = flag;
                *p = 5;
            }
        }
        break;
    default:
        break;
    }
    Call_08004F80();
    return flag;
}

__asm__(
    ".globl Call_08004F18\n.set Call_08004F18, 0x08004F18\n"
    ".globl Call_08024384\n.set Call_08024384, 0x08024384\n"
    ".globl Call_0800B368\n.set Call_0800B368, 0x0800B368\n"
    ".globl Call_0800B3F8\n.set Call_0800B3F8, 0x0800B3F8\n"
    ".globl Call_0800B308\n.set Call_0800B308, 0x0800B308\n"
    ".globl Call_08011DD0\n.set Call_08011DD0, 0x08011DD0\n"
    ".globl Call_08011D68\n.set Call_08011D68, 0x08011D68\n"
    ".globl Call_0804A328\n.set Call_0804A328, 0x0804A328\n"
    ".globl Call_08004F80\n.set Call_08004F80, 0x08004F80\n"
    ".globl TABLE_A_08230CFC\n.set TABLE_A_08230CFC, 0x08230CFC\n"
    ".globl G_0823014C\n.set G_0823014C, 0x0823014C\n"
    ".globl G_08230154\n.set G_08230154, 0x08230154\n"
    ".globl TABLE_D_08230D84\n.set TABLE_D_08230D84, 0x08230D84\n"
    ".globl G_02004E40\n.set G_02004E40, 0x02004E40\n"
    ".globl TABLE_E_08230450\n.set TABLE_E_08230450, 0x08230450\n"
);
