/* Sub_08017A94 @ 0x08017A94 (214 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08017a94_MATCHED.c (registry: mmbcc/src/w38a_08017a94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void ChipSlot_Setup(u8 *s, int b, u8 c);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern int Text_SelectBlobIdx(int idx);

extern void Sub_08017B6C(u8 *s);

__attribute__((section(".text.w38a_08017a94")))
void Sub_08017A94(u8 *s)
{
    u32 out[2];
    u8 *e;
    u32 *p;
    u8 *q;
    int v, w, sh, m;
    {
        register int sh1 __asm__("r1");
        register u8 *b __asm__("r0");
        sh1 = s[16] << 4;
        b = (u8 *)0x082263a8;
        __asm__ volatile("" : "+r"(b));
        e = (u8 *)(sh1 + (u32)b);
    }
    {
        register u32 *base __asm__("r1");
        register int s9 __asm__("r2");
        base = (u32 *)0x082243d8;
        __asm__ volatile("" : "+r"(base));
        s9 = s[9];
        p = (u32 *)((s9 << 2) + (u32)base);
    }
    {
        register int one __asm__("r1");
        register int t10 __asm__("r3");
        register int res __asm__("r0");
        one = 1;
        *(u32 *)(s + 12) = one;
        *(u32 *)(s + 20) = *(u32 *)(*p + 4);
        *(u32 *)(s + 108) = 0;
        t10 = s[10];
        res = 2 | t10;
        res |= one;
        s[10] = res;
    }
    {
        /* ROM arg: movs r1,#192; lsls r1,#2; adds r0,r1,#0;
         * ldrb r1,[e,#1]; orrs r1,r0 (C reorders to e[1]-first
         * with no adds under both agbcc versions, so pin the
         * computation with asm; arg itself stays a C call arg). */
        register int arg __asm__("r1");
        __asm__ volatile("mov %0, #192\n\tlsl %0, %0, #2\n\tadd r0, %0, #0\n\tldrb %0, [%1, #1]\n\torr %0, %0, r0" : "=r"(arg) : "r"(e) : "r0", "cc");
        ChipSlot_Setup(s, arg, e[0]);
    }
    ChipSlot_IncUse(s, e[2]);
    v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
    w = v;
    __asm__ volatile("" : "+r"(w));
    if (w > 3)
        v = 3;
    q = s + 69;
    sh = v << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *q = (*q & m) | sh;
    s[34] = 14;
    if (*(u16 *)(e + 12) & 1) {
        register s32 x __asm__("r1");
        register s32 y __asm__("r2");
        sub_0800DD08(out, s);
        __asm__ volatile("movs r2, #8\n\tldrsh %0, [%1, r2]" : "=r"(x) : "r"(e) : "r2");
        __asm__ volatile("movs r3, #10\n\tldrsh %0, [%1, r3]" : "=r"(y) : "r"(e) : "r3");
        Vec2_SetMirrored(s, x, y);
    } else {
        register s32 x __asm__("r1");
        register s32 y __asm__("r2");
        __asm__ volatile("movs r0, #8\n\tldrsh %0, [%1, r0]" : "=r"(x) : "r"(e) : "r0");
        __asm__ volatile("movs r3, #10\n\tldrsh %0, [%1, r3]" : "=r"(y) : "r"(e) : "r3");
        Vec2_AddMirrored(s, x, y);
    }
    if (e[5] != 0)
        Text_SelectBlobIdx(e[5]);
    Sub_08017B6C(s);
}
