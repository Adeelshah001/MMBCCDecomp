/* Wave 25-B: 0x08026740 Task_Clock_08026740 — MATCHED (0 diffs, 116 B).
 * Clock task: increments S[16] (seconds), rolls over to S[17] (minutes),
 * S[18]/S[19] (hours BCD-ish), then dispatches via tbl[S[0]].
 *
 * Idioms used:
 * - Branch inversion via if/else swap (w24d): `if (S[17] <= 58)` gives bhi.
 * - register u32 hrs __asm__("r2") pins the ldrh to r2 (ROM: ldrh r2,[r4,#18]).
 * - Pinned tbl->r0, idx->r2, idx4->r1, fnaddr->r1 with a "memory" barrier
 *   reproduces ROM's dispatch: ldr r0,=tbl; ldrb r2,[r4,#0]; lsls r1,r2,#2;
 *   adds r1,r1,r0; ldr r1,[r1,#0]; adds r0,r4,#0; bl _call_via_r1.
 * - Control-flow correction: S[18]=0 is INSIDE `if (S[19] != 99)` (ROM's
 *   beq skips it); the w24d C had it outside (wrong).
 * - True extent 116 B (112 code + 4 pool at 0x80267B0); next fn at 0x80267B4.
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void F_EF8(void);
extern void Task_ActivateSlot(u32 slot);
__attribute__((section(".text.w25b_08026740")))
void Task_Clock_08026740(void)
{
    u8 *S;
    u16 max;
    F_EF8();
    S = (u8 *)0x020070F0;
    max = 0x633B;
    for (;;) {
        if (S[0] != 11) {
            S[16]++;
            if ((u8)S[16] > 59) {
                S[16] = 0;
                if (S[17] <= 58) {
                    S[17]++;
                } else {
                    register u32 hrs __asm__("r2") = *(u16 *)(S + 18);
                    if (hrs != max) {
                        S[17] = 0;
                        if (S[18] <= 58) {
                            S[18]++;
                        } else {
                            if (S[19] != 99) {
                                S[19]++;
                                S[18] = 0;
                            }
                        }
                    }
                }
            }
        }
        {
            register u32 *tbl __asm__("r0") = (u32 *)0x0822D8EC;
            register u32 idx __asm__("r2") = S[0];
            register u32 idx4 __asm__("r1") = idx << 2;
            register u32 *fnaddr __asm__("r1");
            __asm__ volatile("" ::: "memory");
            fnaddr = (u32 *)(idx4 + (u32)tbl);
            ((void (*)(u8 *))*fnaddr)(S);
        }
        Task_ActivateSlot(1);
    }
}
