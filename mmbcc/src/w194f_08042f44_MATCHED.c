/* Wave 194 LANDING (2026-11-02 user ruling, sanctioned exception):
 * 0x08042F44 v9 pin chain, LANDED 0-diff (1260/1260 B, old_agbcc -O2, SHA a30f28cc).
 * Sanctioned trick: register-pin chain (f->r1, c->r2, z->r1); compiler-steering
 * only, invents no logic. Sanctioned FOR THIS FUNCTION ONLY per the 2026-11-02
 * ruling; invented-logic tricks remain banned.
 * Section tag renamed w176f_ -> w194f_ at landing; no .set stub dropped
 * (audit: no stub symbol has a real definition in mmbcc/src/; Sub_0804A378 etc.
 * are .set stubs only, coexisting with equal absolute definitions elsewhere).
 */
/* Wave 176 Worker F restage of w176f_08042F44_v9_oldO2.c (verbatim except section tag). */
/* Wave 169 Worker F restage of w168f_08042F44_v9_oldO2.c (verbatim except section tag). */
/* Wave 168 Worker F restage of w167f_08042F44_v9_oldO2.c (verbatim except section tag). */
/* Wave 167 Worker F restage of w166f_08042F44_v9_oldO2.c (verbatim except section tag). */
/* Wave 166-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w165f_/w165f_08042F44_v9_oldO2.c except section tag renamed to w166f_08042F44_v9_oldO2; see RESULTS.md. */
/* Wave 165-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w151a_/w151a_08042F44_v9_oldO2.c except section tag renamed to w166f_08042F44_v9_oldO2; see RESULTS.md. */
/* Wave 151-A v9 (STAGED ONLY, NOT LANDED; FLAGGED 0-diff -- pins in code, needs parent pin-sanction ruling before any landing): M2 + def1 pinned-zero r1 (R6 form + z pin). 0/0 diffs, 1260/1260 B exact, oldO2. Pins: f->r1 (both f-blocks), c->r2 (both f-blocks), z->r1 (def1). Semantics unchanged (see RESULTS.md).
/* Wave 151-A probe M2 pin-f-r1+pin-c-r2+mutate (STAGED ONLY, NOT LANDED): M1 + c pinned r2.
/* Wave 151-A probe M1 pin+mutate (STAGED ONLY, NOT LANDED): P1 + mutate-c masks in both f-blocks.
/* Wave 151-A probe P1 f-pin-r1 (STAGED ONLY, NOT LANDED): f pinned r1 in both f-blocks; else v8.
/* Wave 150-A carry (STAGED ONLY, NOT LANDED): re-verified Wave 149-A v8 best, section retargeted to w151a_; code unchanged. */
/* Wave 149-A carry base (re-verification; code unchanged from Wave 148-A staging, section retargeted to w151a_). */
/* Wave 148-A (STAGED ONLY, NOT LANDED): 0x08042F44 v8, manual method.
 * NEW BEST (was v7 51/51, 1260 B): 45/45, 1260/1260 B exact, oldO2.
 * Closing lever R1 (sel-1 else zero-order, the 6-diff cluster at
 * +738-743): compute the s[0x46aa] pointer FIRST as a named pointer
 * variable (u8 *p = s + 0x46aa), then materialize the named zero
 * (int z = 0), then store *p = v and s[0x46ab] = z. gcc then emits
 * ROM's exact order: ldr r4 (0x46aa offset), adds r1,r5,r4,
 * movs r2,#0, strb r0,[r1], instead of v7's hoisted movs r2,#0
 * before the pointer load. No neighbour disturbance: every other
 * diff group is identical to v7. The R1 trick does NOT transfer
 * to def1 (probe R6, SHA-identical to v8): def1's zero is still
 * hoisted before the flag store in r2, so def1 zero-hoist (10)
 * remains a wall, as do the f-block rotation (28), sel-0x40
 * pointer home (2), and def0 7378-arg scratch rotation (5).
 * int-f probe NOT run (absolute ban, honoured: considered and
 * rejected before building). TRUE extent 1260 B.
 * LANDING FLAGS (carried from v7, re-confirmed this wave):
 *  1. DROP the .set G_02002F50 line: .globl-defined in
 *     mmbcc/src/w83a_0802fda0_MATCHED.c lines 198-199.
 *  2. DROP-CANDIDATE: the .set Sub_0804A378 line: .globl-defined
 *     (absolute stub) in mmbcc/src/w126a_08035630_MATCHED.c
 *     line 147 (inside the __asm__ block at lines ~143-153).
 *     Confirm at link; drop if it collides (extern links to
 *     the w126a definition).
 *  3. All other stubs CLEAR (no exact-case .globl in mmbcc/src/):
 *     D_02004D14, D_02004CE0, Sub_080248AC, Sub_08043630,
 *     Sub_08007378, Sub_0800800C (only lowercase sub_0800800C
 *     elsewhere -- a different symbol to the assembler).
 * Plain C + .set stubs only (no pin, no inline asm in the body,
 * no barrier).
 */
/* Wave 147-C (STAGED ONLY, NOT LANDED): 0x08042F44 v7, manual method.
 * NEW BEST (was v6 187/187, 1260 B): 51/51, 1260/1260 B exact, oldO2.
 * Chain from v6, all hand-read from ROM vs built disassembly:
 *  P1 tail goto-form (187->80): ROM lays the sel==0x200 body first
 *    (fallthrough) and the sel==0x100 body out-of-line at +1160, with
 *    dispatch beq-to-0x100 / bne-to-epilogue; the goto-form tail
 *    (if sel==0x100 goto Ltail100; if sel!=0x200 goto LtailEnd;
 *    0x200 body; Ltail100: 0x100 body) reproduces that dispatch.
 *  P3 (80->71): case-0 0x80-block t is unsigned (ROM bhs vs built
 *    bge at +361); case-0 tail pointer-bind (u8 *d = D_02004CE0,
 *    stores via d+0x28/d+0x2a) defeats the .set fold that made pool
 *    word 0x02004D08 instead of base 0x02004CE0 (+491/+507/+512-513);
 *    named-int FC3F mask (int m = 0xfffffc3f) defeats old_agbcc's
 *    narrowing of the mask pool word to 0x0000FC3F (ROM: full
 *    0xFFFFFC3F) at both sites (+610-611, +1134-1135).
 *  P5 (71->65): first ternaries in both tail bodies written with
 *    negated condition ((*p <= 1) ? 1 : 2) to flip old_agbcc's
 *    false-first emission to ROM's true-first (movs #2, bgt).
 *  P8 (65->53): sel-1 else-branch value in a named temp
 *    (int v = (s[0x46a9] & 0xf) + 2) so gcc emits compute-before-
 *    pointer-load with the byte in r1, as ROM does (+694/+696/
 *    +732-741 fixed).
 *  P9 (53->51): named zero (int z = 0) in the sel-1 else block so
 *    the s[0x46ab] zero store reuses r2 after the pointer load
 *    (+745-750 fixed; +738-743 zero-order micro-diff remains).
 * Rejected this wave (work/ only): P2 mutate-c on both f-blocks
 *    (91, c variable disturbs neighbours); P4 chained zero stores
 *    in def1 (78, pool churn); P6 int-f init-OR (301, int lives
 *    across calls); P7 u8-f init-OR (107); P10 nested-block zero
 *    (65, z leaks into the f1 block). int-f NOT re-run (Wave 142
 *    rejection stands; P6 is a different int form, also rejected).
 * Remaining 51: f-block home rotation + mask synthesis in Lab0
 *    and def0 (28: ROM value r1/mask r2 via subs from the store
 *    constant vs built value r2/mask r1 via movs #0xe1/#0xdf --
 *    compiler-version wall, 3 init forms tried); sel-0x40 pointer
 *    home (623-624, 2); sel-1 zero-order micro-diff (738-743, 6);
 *    def0 7378-arg scratch rotation (916-924, 5); def1 zero-hoist
 *    (1010-1018 + 1024, 10). TRUE extent 1260 B.
 * LANDING FLAGS -- COORDINATOR, READ BEFORE LANDING:
 *  1. DROP the .set G_02002F50 line below: G_02002F50 is already
 *     .globl-defined in mmbcc/src/w83a_0802fda0_MATCHED.c
 *     (lines 198-199). (Wave 126 lesson; carried from v6.)
 *  2. DROP-CANDIDATE: the .set Sub_0804A378 line below:
 *     Sub_0804A378 is already .globl-defined (absolute stub) in
 *     mmbcc/src/w126a_08035630_MATCHED.c (line 147). This
 *     CORRECTS the Wave 146 "no action" note for this symbol,
 *     which missed the w126a .globl line. If the landing
 *     convention converts stubs to .globl form, keeping it WILL
 *     collide; confirm with the post-landing link test and drop
 *     if it collides (extern declaration links to w126a's def).
 *  3. All other stubs are CLEAR (no exact-case .globl in
 *     mmbcc/src/): D_02004D14, D_02004CE0, Sub_080248AC,
 *     Sub_08043630, Sub_08007378, and Sub_0800800C (only a
 *     lowercase sub_0800800C exists elsewhere -- a different
 *     symbol to the assembler -- so no action).
 * Plain C + .set stubs only (no pin, no inline asm in the body,
 * no barrier).
 */
/* Wave 146-C (STAGED ONLY, NOT LANDED): 0x08042F44 v6, manual method.
 * NEW BEST (was v5 409/413, 1264 B): 187/187, 1260/1260 B exact, oldO2.
 * Lever (hand-read from raw-byte comparison): the +4 shift was a
 * .set fold, not a code difference -- old_agbcc folded the case-1
 * tail's D_02004D14+0x28 into its own pool word 0x02004D3c (built
 * +864), because the .set stub makes D's address an assembly-time
 * constant, while ROM loads the base 0x02004D14 once and uses
 * strh offsets 0x28/0x2a. Defeat: bind the base to a pointer
 * variable first (u8 *d = D_02004D14; stores via d+0x28/d+0x2a),
 * so the pool holds only the base and the fold cannot happen.
 * This realigns def0 (0x48 store back to ROM offset 880) and the
 * whole def1/tail, and also clears the early branch-offset diffs
 * at 186/200/212/218/220 (they were +4-shift consequences).
 * Remaining 187: f-block register rotation in def0/def1 (ROM
 * value r1/mask r2/ptr r3 vs built rotated homes) + sparse
 * pre-def0 sites + tail. The f3 mutate-c subs form was re-tested
 * on this new base (work probe g2): 190/190, worse -- its c
 * variable disturbs 204/206 and the 0800C/7378 arg code; g1 stays
 * count-best. int-f NOT re-run per brief. TRUE extent 1260 B.
 * Plain C + .set stubs only (no pin, no inline asm in the body,
 * no barrier).
 */
/* Wave 142-C (STAGED ONLY, NOT LANDED): 0x08042F44 v1, manual method.
 * Hand-read from the disassembly (rdis_42F44.txt, 515 insns, no switch
 * jump-table; dispatch trees + shared tails).
 * int Sub_08042F44(u8 *s): returns r8 (0 normally, 5 on the sel==2 /
 * s[0x46aa]==0 path, 2 on the sel==1 / s[0x46aa]==1 / hi-nibble==0 path).
 * Selector sel (last wins): (G0&0x200&&G3&0x200)->0x200 [neg/asr/and
 * idiom], (G0&0x100&&G3&0x100)->0x100, (G0&0x40&&G2&0x40)->0x40,
 * (G0&0x80&&G2&0x80)->0x80, (G0&1&&G2&1)->1, (G0&2&&G2&2)->2.
 * Main switch on aa = s[0x46aa] (kept in r4; s+0x46aa pointer in r6):
 *  case 1: s[0x46ab]==0 -> struct-0x18/0x58 block + s[0x46ab]++,
 *    then sel-switch; s[0x46ab]==1 -> sel-switch directly; else -> tail.
 *    sel-switch: 2 -> 4A378(0x67), s[0x46aa]=0, s[0x46ab]=0, FLAG&=~2,
 *      43630; 1 -> 4A378(0x67), hi==0 ? (FLAG&=~2, ret=2)
 *      : (s[0x46aa]=(s[0x46a9]&0xf)+2, s[0x46ab]=0, FLAG&=~2), 43630;
 *      0x40 -> hi!=0 ? (4A378(0x66), s[0x46a9]-=0x10) : nothing;
 *      0x80 -> hi==0 ? (4A378(0x66), s[0x46a9]+=0x10) : nothing;
 *      default -> nothing. Then 0x02004D14 struct sets (0x18,
 *      ((s[0x46a9]>>4)<<4)+0x58) -> tail.
 *  case 0: sel-switch: 2 -> 4A378(0x68), 248AC(s[0x16]), ret=5, 43630;
 *    1 -> 4A378(0x67), s[0x46aa]=sel, s[0x46ab]=aa, s[0x46a9]&=0xf, 43630;
 *    0x40 -> (s[0x46a9]&0xf)!=0 ? (4A378(0x66), s[0x46a9]--,
 *      248AC(s[0x46a9]&0xf), s[0x46b0]=3, s[0x46b1]=1, s[0x46a8]&=0xe0,
 *      43630) : nothing;
 *    0x80 -> t=(s[0x15]>7)?2:(s[0x15]>4)?1:0;
 *      (s[0x46a9]&0xf)<t ? (4A378(0x66), s[0x46a9]++,
 *      248AC(s[0x46a9]&0xf), s[0x46b0]=3, s[0x46b1]=1, s[0x46a8]&=0xe0,
 *      43630) : nothing;
 *    default -> nothing. Then 0x02004CE0 struct sets (0x10,
 *    ((s[0x46a9]&0xf)<<4)+0x18) -> tail.
 *  default (aa>=2): s[0x46ab]==0 -> struct-0x48/0x7c block +
 *    0800C(3) + 7378(0,7,2*s[0x16]+3,2) + s[0x16]=s[0x46a9]&0xf + 43630
 *    + s[0x46ab]++, then shared 3306; s[0x46ab]==1 -> 3306 directly;
 *    else -> tail. 3306: if (sel&1) { 7378(1,7,2*s[0x16]+3,2),
 *    4A378(0x67), FLAG&=~2, s[0x46aa]=0, s[0x46ab]=0, 43630 } -> tail.
 * Tail: if (sel==0x100) { (s[0x46a8]&0x1f)>0x16 ? return :
 *   (4A378(0x66), s[0x46b0]=(s8)s[0x46b0]>1?2:1, s[0x46a8]++,
 *   (s[0x46a8]&0x1f)==0x17 ? (s[0x46b1]=(s8)s[0x46b1]>1?3:0) : nothing,
 *   43630) } else if (sel==0x200) { (s[0x46a8]&0x1f)==0 ? return :
 *   (4A378(0x66), s[0x46b1]=(s8)s[0x46b1]>1?2:1, s[0x46a8]--,
 *   (s[0x46a8]&0x1f)==0 ? (s[0x46b0]=(s8)s[0x46b0]>1?3:0) : nothing,
 *   43630) } return ret.
 * TRUE extent 1260 B (next fn 0x08043430).
 * Plain C + .set stubs only (no pin, no inline asm in the body, no barrier).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

extern u16 G_02002F50[];
extern u8 D_02004D14[];
extern u8 D_02004CE0[];
extern void Sub_0804A378(int a);
extern void Sub_080248AC(int a);
extern void Sub_08043630(u8 *s);
extern void Sub_0800800C(u8 *a, int b);
extern void Sub_08007378(int a, int b, int c, int d);

__asm__(".set G_02002F50, 0x02002F50");
__asm__(".set D_02004D14, 0x02004D14");
__asm__(".set D_02004CE0, 0x02004CE0");
__asm__(".set Sub_0804A378, 0x0804A378");
__asm__(".set Sub_080248AC, 0x080248AC");
__asm__(".set Sub_08043630, 0x08043630");
__asm__(".set Sub_0800800C, 0x0800800C");
__asm__(".set Sub_08007378, 0x08007378");

__attribute__((section(".text.w194f_08042f44_v9_oldO2"))) 
int Sub_08042F44(u8 *s)
{
    int ret = 0;
    int sel = 0;
    int aa;

    if (G_02002F50[0] & 0x200)
        sel = (G_02002F50[3] & 0x200) ? 0x200 : 0;
    if (G_02002F50[0] & 0x100 && G_02002F50[3] & 0x100)
        sel = 0x100;
    if (G_02002F50[0] & 0x40 && G_02002F50[2] & 0x40)
        sel = 0x40;
    if (G_02002F50[0] & 0x80 && G_02002F50[2] & 0x80)
        sel = 0x80;
    if (G_02002F50[0] & 1 && G_02002F50[2] & 1)
        sel = 1;
    if (G_02002F50[0] & 2 && G_02002F50[2] & 2)
        sel = 2;

    aa = s[0x46aa];
    if (aa == 1)
        goto Lcase1;
    if (aa > 1)
        goto Ldef;
    if (aa == 0)
        goto Lcase0;
    goto Ltail;
Ldef:
    if (aa > 4)
        goto Ltail;
    if (s[0x46ab] == 0)
        goto Ldef0;
    if (s[0x46ab] == 1)
        goto Ldef1;
    goto Ltail;
Lcase0:

        switch (sel) {
        case 0x40:
            if ((s[0x46a9] & 0xf) != 0) {
                Sub_0804A378(0x66);
                s[0x46a9]--;
                Sub_080248AC(s[0x46a9] & 0xf);
                s[0x46b0] = 3;
                s[0x46b1] = 1;
                s[0x46a8] &= 0xe0;
                Sub_08043630(s);
            }
            break;
        case 0x80: {
            unsigned int t = 0;
            if (s[0x15] > 7)
                t = 2;
            else if (s[0x15] > 4)
                t = 1;
            if ((s[0x46a9] & 0xf) < t) {
                Sub_0804A378(0x66);
                s[0x46a9]++;
                Sub_080248AC(s[0x46a9] & 0xf);
                s[0x46b0] = 3;
                s[0x46b1] = 1;
                s[0x46a8] &= 0xe0;
                Sub_08043630(s);
            }
            break;
        }
        case 1:
            Sub_0804A378(0x67);
            s[0x46aa] = sel;
            s[0x46ab] = aa;
            s[0x46a9] &= 0xf;
            Sub_08043630(s);
            break;
        case 2:
            Sub_0804A378(0x68);
            Sub_080248AC(s[0x16]);
            ret = 5;
            Sub_08043630(s);
            break;
        default:
            break;
        }
        { u8 *d = D_02004CE0; *(u16 *)(d + 0x28) = 0x10; *(u16 *)(d + 0x2a) = ((s[0x46a9] & 0xf) << 4) + 0x18; }
        goto Ltail;
Lcase1:
    if (s[0x46ab] == 0)
        goto Lab0;
    if (s[0x46ab] == 1)
        goto Lsel1;
    goto Ltail;
Lab0: {
            register u8 f __asm__("r1") = D_02004D14[0x2c] | 1;
            register int c __asm__("r2") = 0x18;
            *(u16 *)(D_02004D14 + 0x28) = c;
            c = 0x58;
            *(u16 *)(D_02004D14 + 0x2a) = c;
            f &= (c -= 0x77);
            f &= (c -= 2);
            D_02004D14[0x2c] = f;
            { int m = 0xfffffc3f; *(u16 *)(D_02004D14 + 0x2c) &= m; }
            Sub_0800800C(D_02004D14, 0);
            s[0x46ab]++;
    }
Lsel1:

            switch (sel) {
            case 0x40:
                if ((s[0x46a9] >> 4) != 0) {
                    Sub_0804A378(0x66);
                    s[0x46a9] -= 0x10;
                }
                break;
            case 0x80:
                if ((s[0x46a9] >> 4) == 0) {
                    Sub_0804A378(0x66);
                    s[0x46a9] += 0x10;
                }
                break;
            case 1:
                Sub_0804A378(0x67);
                if ((s[0x46a9] >> 4) == 0) {
                    { int f1 = D_02004D14[0x2c]; f1 &= ~1; D_02004D14[0x2c] = (u8)f1; }
                    ret = 2;
                } else {
                    int v = (s[0x46a9] & 0xf) + 2;
                    u8 *p = s + 0x46aa;
                    int z = 0;
                    *p = v;
                    s[0x46ab] = z;
                    { int f1 = D_02004D14[0x2c]; f1 &= ~1; D_02004D14[0x2c] = (u8)f1; }
                }
                Sub_08043630(s);
                break;
            case 2:
                Sub_0804A378(0x67);
                s[0x46aa] = 0;
                s[0x46ab] = 0;
                { int f1 = D_02004D14[0x2c]; f1 &= ~1; D_02004D14[0x2c] = (u8)f1; }
                Sub_08043630(s);
                break;
            default:
                break;
            }
            { u8 *d = D_02004D14; *(u16 *)(d + 0x28) = 0x18; *(u16 *)(d + 0x2a) = ((s[0x46a9] >> 4) << 4) + 0x58; }
            goto Ltail;
Ldef0: {
            register u8 f __asm__("r1") = D_02004D14[0x2c] | 1;
            register int c __asm__("r2") = 0x48;
            *(u16 *)(D_02004D14 + 0x28) = c;
            c = 0x7c;
            *(u16 *)(D_02004D14 + 0x2a) = c;
            f &= (c -= 0x9b);
            f &= (c -= 2);
            D_02004D14[0x2c] = f;
            { int m = 0xfffffc3f; *(u16 *)(D_02004D14 + 0x2c) = (*(u16 *)(D_02004D14 + 0x2c) & m) | 0xc0; }
            Sub_0800800C(D_02004D14, 3);
            Sub_08007378(0, 7, ((s[0x16] << 17) + 0x30000) >> 16, 2);
            s[0x16] = s[0x46a9] & 0xf;
            Sub_08043630(s);
            s[0x46ab]++;
    }
    /* fall through to Ldef1 */
Ldef1:

            if (sel & 1) {
                Sub_08007378(1, 7, ((s[0x16] << 17) + 0x30000) >> 16, 2);
                Sub_0804A378(0x67);
                { int f1 = D_02004D14[0x2c]; f1 &= ~1; D_02004D14[0x2c] = (u8)f1; }
                { u8 *p = s + 0x46aa; register int z __asm__("r1") = 0; *p = z; s[0x46ab] = z; }
                Sub_08043630(s);
            }
            goto Ltail;
Ltail:
    if (sel == 0x100)
        goto Ltail100;
    if (sel != 0x200)
        goto LtailEnd;
    {
        s8 *p;
        if ((s[0x46a8] & 0x1f) == 0)
            goto LtailEnd;
        Sub_0804A378(0x66);
        p = (s8 *)(s + 0x46b1);
        s[0x46b1] = (*p <= 1) ? 1 : 2;
        s[0x46a8]--;
        if ((s[0x46a8] & 0x1f) == 0) {
            p = (s8 *)(s + 0x46b0);
            s[0x46b0] = (*p > 1) ? 3 : 0;
        }
        Sub_08043630(s);
        goto LtailEnd;
    }
Ltail100:
    {
        s8 *p;
        if ((s[0x46a8] & 0x1f) > 0x16)
            goto LtailEnd;
        Sub_0804A378(0x66);
        p = (s8 *)(s + 0x46b0);
        s[0x46b0] = (*p <= 1) ? 1 : 2;
        s[0x46a8]++;
        if ((s[0x46a8] & 0x1f) == 0x17) {
            p = (s8 *)(s + 0x46b1);
            s[0x46b1] = (*p > 1) ? 3 : 0;
        }
        Sub_08043630(s);
    }
LtailEnd:
    return ret;
}
