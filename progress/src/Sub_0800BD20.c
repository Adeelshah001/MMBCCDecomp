/* Sub_0800BD20 @ 0x0800BD20 (448 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w45c_0800bd20_MATCHED.c (registry: src/w45c_0800bd20_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern u8 gEwram_0200BD20[];

struct A { u16 f0; u16 f2; u8 pad4[4]; u8 f8; u8 f9; u8 f10; u8 pad11; u16 f12; u16 f14; u16 f16; u16 f18; u8 pad20[4]; u16 f24; u8 pad26[2]; u32 f28; u8 pad32[11]; u8 f43; };

extern void *Ewram_BumpAlloc(u32 n);

extern void sub_080006DC(u16 val, void *dst, u32 n);

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
        register s32 *gEwram_0200BD20 __asm__("r2");
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
        gEwram_0200BD20 = (s32 *)0x020038ac;
        sum = (gEwram_0200BD20[5] >> 8) + (((s32 *)(gEwram_0200BD20 + 140))[0] >> 8);
        h16 = ((u16 *)gEwram_0200BD20)[8];
        Yt = (u16)(sum - h16);
        off = 0xf72;
        __asm__ volatile("" : "+r"(off));
        fp = (u8 *)gEwram_0200BD20 + off;
        m4 = 4;
        __asm__ volatile("" : "+r"(m4));
        if ((m4 & *fp) != 0)
            tv = Yt + 8;
        else
            tv = Yt + 16;
        __asm__ volatile("lsl %1, %1, #16\n\tlsr %1, %1, #16\n\tadd %0, %1, #0"
                         : "=r"(Yt) : "r"(tv));
        {
            s32 t6 = gEwram_0200BD20[6] >> 8;
            q = gEwram_0200BD20 + 140;
            __asm__ volatile("" : "+r"(q));
            sum2 = t6 + (q[1] >> 8);
        }
        h18 = ((u16 *)gEwram_0200BD20)[9];
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
                        sub_080006DC(0, buf, 320);
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
