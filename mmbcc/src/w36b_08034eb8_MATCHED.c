/* Wave 36 Worker B2 — 0x08034eb8, 116 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x08034f2c (func_list v2). No literal pool.
 * Variant count: 4 (v4 + patch). Callees Sub_080245C4, Sub_080400A8, Sub_0804DDA0 via .set.
 * Key idioms: base pinned to r8; res = count (not fresh 0) so gcc emits mov r9,r6;
 * byte reloaded after the call (no b variable across the call); elem = i*12 + base
 * (gcc strength-reduces *12 as (i<<1+i)<<2); trailing 00 00 pad to next function.
 * Patch: prologue base pin before target truncation (reorder); element adds
 * operand order index + base (same length, reorder only). */
/* v4: separate assignments, base before target */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 Sub_080245C4(u8 b);
extern u32 Sub_080400A8(void);
extern u32 Sub_0804DDA0(u32 a, u32 b);
__asm__(".set Sub_080245C4, 0x080245c4");
__asm__(".set Sub_080400A8, 0x080400a8");
__asm__(".set Sub_0804DDA0, 0x0804dda0");
__attribute__((section(".text.w36b_08034eb8")))
u8 Sub_08034EB8(u8 *base, u8 arg1)
{
    register u8 *b8 __asm__("r8");
    u8 buf[12];
    u8 target;
    u8 count;
    u8 res;
    u8 i;
    b8 = base;
    target = arg1;
    count = 0;
    res = count;
    for (i = 1; i <= 11; i++) {
        u8 *elem = i * 12 + b8;
        if ((u8)Sub_080245C4(*elem) == target && *elem != 0) {
            buf[count] = *elem;
            count++;
        }
    }
    if (count != 0) {
        u16 rnd = Sub_080400A8();
        u32 idx = Sub_0804DDA0(rnd, count);
        res = buf[idx];
    }
    return res;
}
__asm__(".byte 0, 0");
