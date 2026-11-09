/* LANDING NOTE (Wave 130 coordinator): staged w130a_080396b4_v4 (clean 0/0, 580/580 B, old -O2) landed as w130a_080396b4_MATCHED. Section renamed to .text.w130a_080396b4. Per the Wave 126 landing lesson, the .set stubs for Call_08011DD0, Call_08024384, Call_080112FC, Call_080114B8 and Call_080114E8 are OMITTED here: those symbols are already defined by landed files w78d_08037f38_MATCHED (11DD0/24384/112FC/114B8/114E8), w72a_080493ec_MATCHED (24384) and w83a_08039cfc_MATCHED (24384); redefining them would fail the link with multiple definition. The top prototypes serve as extern declarations and link to those definitions at the same absolute addresses (zero byte change, proven by the post-landing region diff). Kept stubs: Call_080496E8, Call_0804990C, Call_08011BD4 (no other landed definition). */
/* Wave 130-A v4 (P3: P2 shared function-scope u16 r + pointer-form final store; 0/0 MATCH, 580/580 B exact, old -O2; STAGED ONLY, NOT LANDED). */
/* Wave 129-A v3 (P2: held-f case2/4 tails + s16 114E8 return; 289/293, tail mechanism fixed; STAGED ONLY, NOT LANDED). Wave 128-A v2 (P1: temp-z case4 tail; 289/293, WORSE on count but fixes case1 cross-jump + case4 tail homes; STAGED ONLY, NOT LANDED). Wave 127-A v1 (Wave 125-C v1 re-staged unchanged; no new mechanism, see RESULTS.md) (STAGED ONLY, NOT LANDED). 0x080396B4, hand-decoded from
 * ROM disassembly (staging/w125c_/work/dis_080396b4.txt). TRUE extent 580 B
 * (next func 0x080398F8); func_stats size_bytes 572 B (see RESULTS.md).
 * DATA-VS-CODE FINDING: this region is CODE, not data -- a 5-case jump-table
 * state machine on (s8)s[0x469D] (cases 0..4, default returns). The low
 * func_stats insn count (26) is an artifact; the disassembly shows the full
 * dispatcher plus shared tails: case 0 falls into case 1's head, case 1's
 * tail falls into case 2's test, case 3's tail falls into case 4's test.
 * A plain-C v1 duplicates the shared tails (the compiler does not merge
 * them the way ROM does), so exact size/layout match is not expected.
 * Status: BLOCKED-proposal (v1, not yet verified at write time).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

void Call_08011DD0(int a, u8 b);
u8 Call_080496E8(u8 a, u8 b);
void Call_0804990C(void);
u8 Call_08024384(int a);
u16 Call_080112FC(u8 a, int b);
u8 Call_080114B8(u16 a);
s16 Call_080114E8(int a);
void Call_08011BD4(void);

__attribute__((section(".text.w130a_080396b4")))
int sub_080396B4(u8 *s)
{
    u16 keys = *(u16 *)0x02002F50;
    s8 st = (s8)s[0x469D];
    u16 r;

    switch (st) {
    case 0: {
        u8 diff = (u8)(s[0x469B] - s[0x4698] - 1);
        u8 idx;
        u8 *p;
        Call_08011DD0(1, diff);
        Call_08011DD0(2, s[0x469A]);
        Call_08011DD0(3, 0);
        diff = (u8)(s[0x469B] - s[0x4698] - 1);
        idx = Call_080496E8(diff, s[0x469A]);
        p = s + idx * 12 + 48;
        if (*p <= 98)
            (*p)++;
        s[0x469E] = 0;
        if (s[21] == 1) {
            Call_0804990C();
            *(u32 *)(s + 24) |= 4;
            *(u32 *)(s + 28) &= ~4;
        }
        s[0x469D]++;
        /* fallthrough into case 1 */
    }
    case 1: {
        r = Call_080112FC((u8)(Call_08024384(0x1000) - 50), 4);
        if (r == 0) {
            s[0x469D] += 2;
            break;
        }
        if (Call_080114B8(r) != 0)
            break;
        s[0x469D]++;
        s[0x469F] = 0;
        /* fallthrough into case 2 */
    }
    case 2: {
        u8 f;
        if ((keys & 8) != 0)
            s[0x469F]++;
        else
            s[0x469F] = 0;
        f = s[0x469F];
        if (f > 30) {
            Call_08011BD4();
            s[0x469D]++;
        } else if (Call_080114E8(f) == 1) {
            s[0x469D]++;
        }
        break;
    }
    case 3: {
        r = Call_080112FC((u8)(Call_08024384(0x1000) - 50), 3);
        if (r == 0) {
            s[0x469C] = 4;
            s[0x469D] = 0;
            break;
        }
        if (Call_080114B8(r) != 0)
            break;
        s[0x469D]++;
        s[0x469F] = 0;
        /* fallthrough into case 4 */
    }
    case 4: {
        u8 f;
        if ((keys & 8) != 0)
            s[0x469F]++;
        else
            s[0x469F] = 0;
        f = s[0x469F];
        if (f > 30) {
            Call_08011BD4();
        } else if (Call_080114E8(f) != 1) {
            break;
        }
    }
        {
            u8 *p = s + 0x469C;
            u8 z = 0;
            *p = 5;
            s[0x469D] = z;
        }
        break;
    default:
        break;
    }
    return 0;
}

/* Absolute callee symbols -- MUST follow all code (GAS 2.42 .set rule). */
__asm__(
    ".globl Call_080496E8\n.set Call_080496E8, 0x080496E8\n"
    ".globl Call_0804990C\n.set Call_0804990C, 0x0804990C\n"
    ".globl Call_08011BD4\n.set Call_08011BD4, 0x08011BD4\n"
);
