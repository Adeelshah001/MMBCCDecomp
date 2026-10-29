/* Phase 3 Wave 5 blocked-revisit: Task_366A8 — MATCHED 2026-10-20,
 * coordinator-verified 0 diffs over 64 bytes in built ROM.
 * Task mode handler: switch on p[2]; case 0 inits via sub_08004DFC(1);
 * case 1 tears down, polls sub_08004E0C(0) as s8, and on nonzero sets
 * p[1]=2, p[2]=p[3]=v (sign-extended), then re-inits.
 * Idioms: `s32 v = (s8)sub_08004E0C(0)` forces lsls+asrs sign-extension
 * (pure s8 gets optimized to lsrs); the wave4_k notes had the branch
 * backwards — ROM's bne skips the body, so it is `if (!v)`.
 * EntryMgr_Teardown/Setup are matched (extern, resolved by linker);
 * sub_08004DFC/sub_08004E0C are unmatched (absolute .set).
 * Evidence: docs/match_notes_wave5_blk.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
void sub_08004DFC(u32 a);
s32 sub_08004E0C(u32 a);

__attribute__((section(".text.w5b_366a8")))
void Task_366A8(u8 *p)
{
    switch (p[2]) {
    case 0:
        sub_08004DFC(1);
        p[2]++;
    case 1:
        EntryMgr_Teardown();
        {
            s32 v = (s8)sub_08004E0C(0);
            if (!v) {
                p[1] = 2;
                p[2] = v;
                p[3] = v;
            }
        }
        EntryMgr_Setup();
        break;
    default:
        break;
    }
}

__asm__(
    ".globl sub_08004DFC\n.set sub_08004DFC, 0x08004DFC\n"
    ".globl sub_08004E0C\n.set sub_08004E0C, 0x08004E0C\n"
);
