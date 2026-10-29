/* MMBCCDecomp — SRAM save primitives (Wave 0).
 * ROM 0x0804DB38-0x0804DCCC.
 *
 * MATCHED (byte-identical): Sram_Memcpy, Sram_WaitcntInit, Sram_Read,
 *   Sram_VerifyCompare, Sram_VerifyWorker, Sram_RetryWrapper.
 *
 * Behavior:
 * - Sram_Memcpy: plain byte copy (src, dst, len).
 * - Sram_WaitcntInit: sets SRAM waitstate (WAITCNT bits 0-1 = 3), copies
 *   Sram_Memcpy's machine code to a stack buffer, and calls the copy so
 *   the SRAM read loop executes from IWRAM.
 * - Sram_Read: WAITCNT init + byte copy (used for SRAM reads).
 * - Sram_VerifyCompare: byte compare; returns NULL if equal, else a
 *   pointer to the first mismatching byte.
 * - Sram_VerifyWorker: WAITCNT init + stack-copied Sram_VerifyCompare.
 * - Sram_RetryWrapper: Sram_Read then Sram_VerifyWorker, retrying the
 *   pair up to 3 times total while verification fails.
 *
 * Compiler notes (agbcc, -O2 -mthumb-interwork):
 * - The WAITCNT read-modify-write uses register-pinned variables and a
 *   targeted inline `ldrh` to reproduce the exact `ldrh r0,[r2]` /
 *   `ldr r1,=mask` allocation; pure C consistently yields `ldrh r1`.
 * - The `& ~1` thumb-bit clear is an inline `bic` (pure C `& ~1` folds
 *   to `and` with -2 on this agbcc).
 * - The stack-call pointer uses a register-pinned `r3` plus inline `add`
 *   to get `mov r3,sp; adds r3,#1` (pure C `| 1` gives `orrs` with a
 *   different allocation).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

#define REG_WAITCNT (*(volatile u16 *)0x04000204)

__attribute__((section(".text.sram")))
void Sram_Memcpy(u8 *src, u8 *dst, u32 len)
{
    s32 n = (s32)len - 1;

    if (len == 0)
        return;
    do {
        *dst++ = *src++;
        n--;
    } while (n != -1);
}

__attribute__((section(".text.sram")))
void Sram_WaitcntInit(u8 *dst, u8 *src, u32 len)
{
    u8 buf[0x80];
    u16 *s;
    u16 *d;
    u16 i;
    u32 addr;
    register u32 code __asm__("r3");
    {
        register u32 wc __asm__("r2") = 0x04000204;
        register u16 v __asm__("r0");
        u16 m;
        __asm__ volatile ("ldrh %0, [%1]" : "=r" (v) : "r" (wc));
        m = 0xFFFC;
        v &= m;
        v |= 3;
        *(volatile u16 *)wc = v;
    }

    addr = (u32)Sram_Memcpy;
    __asm__ volatile ("bic %0, %1" : "+r" (addr) : "r" (1));
    s = (u16 *)addr;
    d = (u16 *)buf;
    for (i = ((u32)Sram_WaitcntInit - (u32)Sram_Memcpy) / 2; i != 0; i--)
        *d++ = *s++;
    code = (u32)buf;
    __asm__ volatile ("add %0, #1" : "+r" (code));
    ((void (*)(u8 *, u8 *, u32))code)(dst, src, len);
}

__attribute__((section(".text.sram")))
void Sram_Read(u8 *src, u8 *dst, u32 len)
{
    s32 n = (s32)len;
    {
        register u32 wc __asm__("r2") = 0x04000204;
        register u16 v __asm__("r0");
        u16 m;
        __asm__ volatile ("ldrh %0, [%1]" : "=r" (v) : "r" (wc));
        m = 0xFFFC;
        v &= m;
        v |= 3;
        *(volatile u16 *)wc = v;
    }

    n--;
    if (n == -1)
        return;
    do {
        *dst++ = *src++;
        n--;
    } while (n != -1);
}

__attribute__((section(".text.sram")))
u8 *Sram_VerifyCompare(u8 *a, u8 *b, u32 len)
{
    s32 n = (s32)len - 1;
    if (len == 0)
        goto ret0;
    len = (u32)-1;
loop:
    if (*b++ == *a++)
        goto cont;
    return b - 1;
cont:
    n--;
    if (n != (s32)len)
        goto loop;
ret0:
    return 0;
}
/* 2-byte zero pad to match ROM (0x0804DC2E). */
__asm__(".short 0x0000");

__attribute__((section(".text.sram")))
u8 *Sram_VerifyWorker(u8 *dst, u8 *src, u32 len)
{
    u8 buf[0xC0];
    u16 *s;
    u16 *d;
    u16 i;
    u32 addr;
    register u32 code __asm__("r3");
    {
        register u32 wc __asm__("r2") = 0x04000204;
        register u16 v __asm__("r0");
        u16 m;
        __asm__ volatile ("ldrh %0, [%1]" : "=r" (v) : "r" (wc));
        m = 0xFFFC;
        v &= m;
        v |= 3;
        *(volatile u16 *)wc = v;
    }

    addr = (u32)Sram_VerifyCompare;
    __asm__ volatile ("bic %0, %1" : "+r" (addr) : "r" (1));
    s = (u16 *)addr;
    d = (u16 *)buf;
    for (i = ((u32)Sram_VerifyWorker - (u32)Sram_VerifyCompare) / 2; i != 0; i--)
        *d++ = *s++;
    code = (u32)buf;
    __asm__ volatile ("add %0, #1" : "+r" (code));
    return ((u8 *(*)(u8 *, u8 *, u32))code)(dst, src, len);
}

__attribute__((section(".text.sram")))
u8 *Sram_RetryWrapper(u8 *dst, u8 *src, u32 len)
{
    u8 tries;
    u8 *res;

    for (tries = 0; tries <= 2; tries++) {
        Sram_Read(dst, src, len);
        res = Sram_VerifyWorker(dst, src, len);
        if (res == 0)
            break;
    }
    return res;
}
