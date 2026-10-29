/* Wave 45-C v10: 0x0800bd20, 448 B. v9 + last two fixes (v9: 448 B,
 * main 6 diffs, old 2 diffs).
 * - Flag AND dest: main picks byte's reg (r1) as AND dest, old picks
 *   mask's reg (r0, as in ROM). Swap test operands to (m4 & *fp) /
 *   (m4b & *fb2) so the mask (r0) is the first operand -> dest r0.
 * - Header third address reg: direct store reuses hdr's reg (r2)
 *   for the address; ROM uses r1. Restore the a3 temp (pinned r1)
 *   but make o1's +8 update opaque via asm (plain o1 += 8 let gcc
 *   fold the +8 into a3's computation, costing an insn in v8).
 *   asm is 2-operand `add %0, #8` (Thumb imm3 cannot hold 8; ROM's
 *   adds r3,#8 is the imm8 form 0x3308). */
/* Wave 45-C v9: 0x0800bd20, 448 B. v8 + corrections.
 * v8 REGRESSED (440 B): pinning u16 Yt/Xt made gcc defer/drop
 * truncations (y0 trunc vanished, branches gained truncs, Yt-=8 lost
 * its wrap -- a semantic bug, not just bytes). LESSON: do NOT pin
 * u16 locals whose value must be truncated at assignment; gcc 2.95
 * defers the conversion to uses (or drops it) when the dest is a
 * pinned register. v6's plain Yt/Xt were correct. v9 reverts Yt/Xt
 * to plain and fixes the remaining v6 diffs with conflict-free
 * single-use temps only:
 * - flag tests: single-use m4/m4b pinned r0 + barrier, assigned in a
 *   separate statement before the test (statement order gives
 *   movs-before-ldrb; the barrier blocks constant propagation that
 *   would restore literal order; single-use + dead-after-test gives
 *   AND dest r0). Ranges are sequential (off->m4->tv->q->m4b), so
 *   no v7-style pin conflict.
 * - flagG join: join-asm (kept from v8, it worked).
 * - off barrier, dst pin, hdr barrier, a2 pin, X2 asm: kept (worked).
 * - header third: direct store after o1 += 8 (v8's a3 temp folded
 *   the +8 into a fresh reg, costing an insn vs ROM's in-place
 *   adds r3,#8; adds r1,r2,r3).
 * v6 already exact: prologue, head, geometry y0, sum2, Xt-=8, late,
 * store-check, alloc, recheck, table, Memset loop, post, span setup,
 * span pre-check, epilogue, all pools. */
/* Wave 45-C v8: 0x0800bd20, 448 B. v6 + fixes for v6's remaining diffs
 * (v6: 448 B, 134/133 diffs, mostly a 2 B join-shortfall cascade).
 * v7 is DISCARDED: it pinned m to r0 across flagG->flagH, conflicting
 * with q (also r0, live in between) -- gcc cannot honor two live vars
 * in one register, so it emitted wrong code (flagH's AND used a stale
 * r0, no mask reload) and remapped plain vars. LESSON: never pin two
 * variables to the same register with overlapping live ranges; use
 * single-use temps (dead after their test) instead of a shared mask.
 * v8 changes, all conflict-free (sequential live ranges only):
 * - Yt pinned r3, Xt pinned r2 (v6's natural regs, locked so the
 *   added pins cannot remap plain vars as v7 did).
 * - flagG offset: off pinned r0 + barrier (v7 proved the barrier
 *   works; off's range is brief and ends before tv/q are born).
 * - flag tests: literal-first operand order (4 & *fp) / (4 & *fb2)
 *   to get movs-before-ldrb order with dest r0 (v6's byte-first
 *   order gave ldrb-before-movs).
 * - flagG join: explicit join-asm (lsl tv; lsr tv; adds Yt,tv) with
 *   Yt as output -- no tu temp (v7's tu was coalesced away).
 * - Store pair: dst pinned r0 (was r3).
 * - Header: hdr barriered (kills the orr synthesis) + pinned a2/a3
 *   -> r1 so the values load into r0 as in ROM.
 * - Span body X2-store: asm mov r0,r8; strh r0,[r4].
 * v6 already exact: prologue, head, geometry y0, sum2, Xt-=8, late,
 * store-check, alloc, recheck, table, Memset loop, post, span setup,
 * span pre-check, epilogue, all pools. */
/* Wave 45-C v6: 0x0800bd20, 448 B. v5 + ROM-disassembly-grounded fixes
 * (ROM dis dumped 2026-10-26, compared insn by insn):
 * - flagG: offset pinned r0 (ldr r0,pool; adds r1,r2,r0), literal &4
 *   (movs r0,#4; ldrb r1,[r1]; ands r0,r1); join via s32 tv + u16 tu
 *   both pinned r0 so the trunc is lsl r0; lsr r0; adds r3,r0 (ROM
 *   does NOT fold the join trunc into r3).
 * - x0: G[6]>>8 into t6 first, then q=G+140 (barriered so gcc cannot
 *   fold q[1] into G[141]) and q[1] -> ldr [r0,#4] as in ROM.
 * - flagH: literal &4 (mask r0, load r1); base+offset pools kept
 *   separate via the pinned fb/fb2 pair (no 0x0200481e fold).
 * - A<0 sl=0: literal asm movs r3,#0; mov sl,r3 (a pinned C temp was
 *   coalesced away by gcc in v5).
 * - Store pair: asm mov r1,r9; strh; mov r2,r8; strh (C temps were
 *   coalesced to r3/r4 in v5).
 * - Header: pinned o1->r3 (372 = 186<<1), o2->r0 (376 = 188<<1),
 *   third via o1+=8 (adds r3,#8) as in ROM; hdr pinned r2.
 * - step16 is s32 (ROM: asrs r5; cmp r5,#0, no re-extension).
 * - Span setup: asm mov r2,sl; lsl r3,r2,#16 (slv/fx0 pins were
 *   coalesced away in v5).
 * - Span pre-check: cur via opaque asm asr (blocks gcc merging the
 *   guard into the loop test, which is what v5's if+do-while
 *   suffered); guard `if (cur >= end) return;` + do-while; end in r2.
 * - Span body: Y-store via asm mov r3,r9; strh r3,[r4]; fx+= via asm
 *   movs r3,#128; lsl r3,#9; add r1,r1,r3 (per-iteration, r3). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void *Ewram_BumpAlloc(u32 n);
extern void Memset16(u16 val, void *dst, u32 n);

__attribute__((section(".text.w45c_0800bd20")))
void Sub_0800BD20(u8 *s0)
{
    u8 *s = s0;
    u16 Yt;
    u16 Xt;
    {
        register s32 b4 __asm__("r1");
        register s32 h0 __asm__("r0");
        __asm__ volatile("movs r1, #4\n\tldrsb %0, [%1, r1]" : "=r"(b4) : "r"(s));
        if (b4 == -1) {
            __asm__ volatile("movs r2, #20\n\tldrsh %0, [%1, r2]" : "=r"(h0) : "r"(s) : "r2");
            if (h0 == b4)
                return;
        }
    }
    {
        register s32 *G __asm__("r2");
        register u16 h16 __asm__("r4");
        register u16 h18 __asm__("r2");
        register u8 *fp __asm__("r1");
        register u8 *fb2 __asm__("r1");
        register s32 off __asm__("r0");
        register s32 m4 __asm__("r0");
        register s32 tv __asm__("r0");
        register s32 *q __asm__("r0");
        register s32 m4b __asm__("r0");
        s32 sum;
        s32 sum2;
        G = (s32 *)0x020038ac;
        sum = (G[5] >> 8) + (((s32 *)(G + 140))[0] >> 8);
        h16 = ((u16 *)G)[8];
        Yt = (u16)(sum - h16);
        off = 0xf72;
        __asm__ volatile("" : "+r"(off));
        fp = (u8 *)G + off;
        m4 = 4;
        __asm__ volatile("" : "+r"(m4));
        if ((m4 & *fp) != 0)
            tv = Yt + 8;
        else
            tv = Yt + 16;
        __asm__ volatile("lsl %1, %1, #16\n\tlsr %1, %1, #16\n\tadd %0, %1, #0"
                         : "=r"(Yt) : "r"(tv));
        {
            s32 t6 = G[6] >> 8;
            q = G + 140;
            __asm__ volatile("" : "+r"(q));
            sum2 = t6 + (q[1] >> 8);
        }
        h18 = ((u16 *)G)[9];
        Xt = (u16)(sum2 - h18);
        {
            register u8 *fb __asm__("r1");
            fb = (u8 *)0x02003670;
            __asm__ volatile("" : "+r"(fb));
            fb2 = fb + 0x11ae;
        }
        m4b = 4;
        __asm__ volatile("" : "+r"(m4b));
        if ((m4b & *fb2) == 0)
            Yt -= 8;
        Xt -= 8;
    }
    {
        register u16 Y __asm__("r9");
        register u16 X2 __asm__("r8");
        register u16 sl __asm__("sl");
        register u16 step __asm__("r6");
        s16 A;
        s32 x2v;
        {
            register s32 diff __asm__("r1");
            register u16 slt __asm__("r2");
            diff = 60 - Xt;
            __asm__ volatile("lsl %0, %0, #16" : "+r"(diff));
            step = 32;
            Y = Yt;
            x2v = 224;
            __asm__ volatile("lsr %0, %1, #16" : "=r"(slt) : "r"(diff));
            sl = slt;
            A = (s16)(diff >> 16);
        }
        x2v = x2v - A;
        __asm__ volatile("lsl %0, %0, #16\n\tlsr %0, %0, #16" : "+r"(x2v));
        X2 = (u16)x2v;
        if (A < 0) {
            s32 t;
            t = A;
            t += 32;
            __asm__ volatile("lsl %1, %1, #16\n\tlsr %0, %1, #16" : "=r"(step), "=r"(t) : "1"(t));
            __asm__ volatile("movs r3, #0\n\tmov %0, r3" : "=r"(sl) : : "r3");
        }
        {
            register s32 h1 __asm__("r0");
            register u16 *dst __asm__("r0");
            __asm__ volatile("movs r4, #20\n\tldrsh %0, [%1, r4]" : "=r"(h1) : "r"(s) : "r4");
            if (h1 == -1) {
                dst = (u16 *)0x020031f4;
                __asm__ volatile("mov r1, %1\n\tstrh r1, [%0]\n\tmov r2, %2\n\tstrh r2, [%0, #2]"
                                 : : "r"(dst), "r"(Y), "r"(X2) : "r1", "r2", "memory");
                return;
            }
        }
        {
            register u8 *buf __asm__("r4");
            register u32 *hdr __asm__("r2");
            register s32 o1 __asm__("r3");
            register s32 o2 __asm__("r0");
            register u32 *a2 __asm__("r1");
            register u32 *a3 __asm__("r1");
            buf = Ewram_BumpAlloc(640);
            if (buf == 0)
                return;
            hdr = (u32 *)0x03000400;
            __asm__ volatile("" : "+r"(hdr));
            o1 = 372;
            *(u32 *)((u8 *)hdr + o1) = (u32)buf;
            o2 = 376;
            a2 = (u32 *)((u8 *)hdr + o2);
            *a2 = 0x04000018;
            __asm__ volatile("add %0, #8" : "+r"(o1));
            a3 = (u32 *)((u8 *)hdr + o1);
            *a3 = 0xa2600002;
            {
                register s32 h2 __asm__("r0");
                __asm__ volatile("movs r1, #20\n\tldrsh %0, [%1, r1]" : "=r"(h2) : "r"(s) : "r1");
                if (h2 != -1) {
                    register u32 *ft __asm__("r2");
                    s8 idx;
                    void (*fn)(u8 *, void *, u32);
                    ft = (u32 *)0x081731c0;
                    __asm__ volatile("" : "+r"(ft));
                    idx = ((s8 *)0x0817313c)[h2];
                    fn = (void (*)(u8 *, void *, u32))ft[idx];
                    fn(s, buf, 160);
                    __asm__ volatile("lsl %0, %0, #16" : "+r"(step));
                } else {
                    int cnt;
                    s32 t;
                    register s32 ctmp __asm__("r1");
                    cnt = 0;
                    __asm__ volatile("lsl %0, %0, #16" : "+r"(step));
                    do {
                        Memset16(0, buf, 320);
                        __asm__ volatile(
                            "lsl %0, %1, #16\n\t"
                            "movs %2, #128\n\t"
                            "lsl %2, %2, #9\n\t"
                            "add %0, %0, %2\n\t"
                            "lsr %1, %0, #16"
                            : "=&r"(t), "+r"(cnt), "=&r"(ctmp));
                    } while ((s16)(t >> 16) <= 159);
                }
            }
            {
                register s32 step16 __asm__("r5");
                register s32 slv __asm__("r2");
                register s32 fx0 __asm__("r3");
                s16 start;
                s32 end;
                s32 cur;
                __asm__ volatile("asr %0, %1, #16" : "=r"(step16) : "r"(step));
                if (step16 <= 0)
                    return;
                __asm__ volatile("mov %0, %2\n\tlsl %1, %0, #16"
                                 : "=r"(slv), "=r"(fx0) : "r"(sl));
                start = (s16)(fx0 >> 16);
                if (start > 159)
                    return;
                {
                    register s32 b4 __asm__("r1");
                    __asm__ volatile("movs r1, #4\n\tldrsb %0, [%1, r1]" : "=r"(b4) : "r"(s));
                    if (b4 == -1)
                        return;
                }
                buf = buf + start * 4;
                {
                    register s32 fx __asm__("r1");
                    fx = fx0;
                    __asm__ volatile("asr %0, %1, #16" : "=r"(cur) : "r"(fx));
                    end = start + step16;
                    if (cur >= end)
                        return;
                    do {
                        __asm__ volatile("mov r3, %1\n\tstrh r3, [%0]"
                                         : : "r"(buf), "r"(Y) : "r3", "memory");
                        buf += 2;
                        __asm__ volatile("mov r0, %1\n\tstrh r0, [%0]"
                                         : : "r"(buf), "r"(X2) : "r0", "memory");
                        buf += 2;
                        __asm__ volatile("movs r3, #128\n\tlsl r3, r3, #9\n\tadd %0, %0, r3"
                                         : "+r"(fx) : : "r3");
                    } while ((s16)(fx >> 16) < end);
                }
            }
        }
    }
}

__asm__(".set Memset16, 0x080006dc");
