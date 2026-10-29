/* W37-C MATCHED: 0x0804713c, 156 B, old_agbcc, pure C, 0 diffs.
 * Jump-table dispatch on s[0], returns u8. Idioms: result pinned r0
 * (tail reads call result directly, no lsrs); tail label inside switch
 * (between case 3 and case 4); case 4 falls through to case 5 (both
 * return 0; case 4 increments first if B2F0() != 0).
 * ret = 1; switch (s[0]):
 *  case 0: r = B148(1, 133, 1); goto tail;
 *  case 1: if (B2D8() == 0) goto ret; r = B320(a, b, c, d); goto tail;
 *  case 2: r = B308(); goto tail;
 *  case 3: r = B2B4(); goto tail;
 *  case 4: if (B2F0() == 0) { ret = 0; goto ret; } s[0]++; goto ret;
 *  case 5: ret = 0; goto ret;
 *  default: goto ret;
 * tail: if (r != 0) s[0]++;
 * ret: return ret.
 * Extern callees + addresses: Sub_0800B148 0x0800b148, Tst_0800B2D8
 * 0x0800b2d8, Sub_0800B320 0x0800b320, Check_B308 0x0800b308,
 * CheckAndSet_B2B4 0x0800b2b4, Tst_0800B2F0 0x0800b2f0 (all MATCHED).
 * Jump table at 0x08047164: 717c, 7188, 71a0, 71a6, 71b8, 71c8.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern u8 Sub_0800B148(int a, int b, int c);
__asm__(".set Sub_0800B148, 0x0800b148");
extern u8 Tst_0800B2D8(void);
extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);
extern u8 Check_B308(void);
extern u8 CheckAndSet_B2B4(void);
extern u8 Tst_0800B2F0(void);

__attribute__((section(".text.w37c_0804713c")))
u8 Sub_0804713C(u8 *s, u32 a, u32 b, u32 c, u32 d)
{
    u8 ret = 1;
    register u8 r __asm__("r0");
    switch (s[0]) {
    case 0: r = Sub_0800B148(1, 133, 1); goto tail;
    case 1:
        if (Tst_0800B2D8() == 0)
            goto ret;
        r = Sub_0800B320(a, b, c, d);
        goto tail;
    case 2: r = Check_B308(); goto tail;
    case 3: r = CheckAndSet_B2B4(); goto tail;
tail:
    if (r != 0)
        s[0]++;
    goto ret;
    case 4:
        if (Tst_0800B2F0() != 0)
            s[0]++;
        /* fall through */
    case 5:
        ret = 0;
        goto ret;
    default:
        goto ret;
    }
ret:
    return ret;
}
