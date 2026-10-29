/* Wave 36-E MATCHED: 0x0801cc94 (76 B, main agbcc, 0 diffs).
 * v7: split orr -- `f = 2; f |= s[10]; s[10] = f | 1;` forces ROM's
 * movs-first order (movs r0, #2; ldrb r1; orrs). Single-expression
 * `f = 2 | s[10]` loads first (W35-C v2, 4 diffs). Twin family:
 * 0x0801a9ac / 0x0801b8d0 / 0x0801cc94 all closed by this form.
 * Callee _call_via_r1 thunk + sibling via .set (sibling unmatched:
 * keep .set; thunk is in the build -- coordinator strips it). */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0804DCD0(u8 *s, u32 *ent);
extern void Worker_0801CCE0(u8 *s);
__asm__(".set Worker_0804DCD0, 0x0804dcd0");
__asm__(".set Worker_0801CCE0, 0x0801cce0");
__attribute__((section(".text.w36e_0801cc94")))
void Sub_0801CC94(u8 *s)
{
    u8 f;
    {
        register u32 *tbl __asm__("r1") = (u32 *)0x082243d8;
        register u8 idx __asm__("r2") = s[9];
        register u32 off __asm__("r0") = idx << 2;
        u32 *ent;
        __asm__ volatile("" : "+r"(tbl));
        ent = (u32 *)(off + (u32)tbl);
        *(u32 *)(s + 12) = 1;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 4);
    }
    *(u32 *)(s + 108) = 0;
    f = 2;
    f |= s[10];
    s[10] = f | 1;
    {
        register u32 *tbl2 __asm__("r1") = (u32 *)0x0822697c;
        register u8 idx2 __asm__("r2") = s[16];
        register u32 off2 __asm__("r0") = idx2 << 2;
        u32 *ent2;
        __asm__ volatile("" : "+r"(tbl2));
        ent2 = (u32 *)(off2 + (u32)tbl2);
        Worker_0804DCD0(s, *ent2);
    }
    Worker_0801CCE0(s);
}
