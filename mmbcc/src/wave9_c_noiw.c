/* MMBCCDecomp — Wave 9 batch C (no-interwork TU).
 *
 * No-interwork functions from the 0x0804DD08-0x0804DFA8 division/libc block:
 * agbcc emits `pop {pc}` / `pop {r4,r5,pc}` epilogues only WITHOUT
 * -mthumb-interwork. Evidence: docs/match_notes_wave9_C.md.
 *
 * MATCHED (byte-identical, worker C, 2026-10-21):
 * - Memcpy_4DFA8 @0x0804DFA8 (94 B): optimized memcpy — 16-byte unrolled
 *   word loop (ldmia/stmia) for aligned len>15, 4-byte tail, byte tail.
 *   Register pinning: sw pinned to r3 (coalesces with s); dw from dst.
 * - DivZeroStub_4DD90 @0x0804DD90 (10 B + 2 B pad): divide-by-zero exit
 *   stub; calls sub_0804DD9C, returns 0. Twin of DivZeroStub@0x0804DE64
 *   (wave3_d_noiw.c), DivZeroStub_4DEDE (ldscript BYTE), Wrap_0804DF9E.
 */

typedef unsigned int u32;
typedef unsigned char u8;

extern void sub_0804DD9C(void);

/* 0x0804DFA8: optimized memcpy (94 B).
 * Word path (len > 15, both 4-aligned): 4x ldmia/stmia unrolled loop,
 * then single-word tail. Byte tail uses the len-1 vs -1 idiom. */
__attribute__((section(".text.w9c_memcpy_4dfa8")))
void *Memcpy_4DFA8(void *dst, const void *src, u32 len)
{
    const u8 *s;
    u8 *d;

    d = (u8 *)dst;
    s = (const u8 *)src;

    if (len > 15 && ((((u32)s) | ((u32)d)) & 3) == 0) {
        u32 *dw = (u32 *)dst;
        register const u32 *sw __asm__("r3") = (const u32 *)s;
        do {
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            len -= 16;
        } while (len > 15);
        while (len > 3) {
            *dw++ = *sw++;
            len -= 4;
        }
        d = (u8 *)dw;
        s = (const u8 *)sw;
    }
    {
        u32 n = len - 1;
        if (n != (u32)-1) {
            do {
                *d++ = *s++;
            } while (--n != (u32)-1);
        }
    }
    return dst;
}

/* 0x0804DD90: divide-by-zero exit stub (10 B).
 * Calls the 1-insn trap at 0x0804DD9C, returns 0. */
__attribute__((section(".text.w9c_divzero_4dd90")))
u32 DivZeroStub_4DD90(void)
{
    sub_0804DD9C();
    return 0;
}

/* 2-byte zero pad: ROM has 0000 after the 10 code bytes at 0x0804DD9A. */
__attribute__((section(".text.w9c_divzero_4dd90")))
static const u8 sPad_DivZeroStub_4DD90[2] = { 0, 0 };
