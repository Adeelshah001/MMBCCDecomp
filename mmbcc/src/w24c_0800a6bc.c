/* Wave 24 Worker C @0x0800a6bc (152 B incl pools). MATCHED with old_agbcc.
 * EWRAM 0x02004830 state reset: if p[1]==0, init (Ewram4E40_Init_0B4E4,
 * Clr_0800B4C8, p[19] &= -3); if p[1] not 0/1, return 1. Then a
 * saturating-decrement on *(u8*)(0x02004830+0x264): if (p[19]&1) and
 * (s8)b > 1, r = (u8)((s8)b - max((s8)b>>2, 1)); if r>0 store it,
 * else zero p[0..3] and *(u8*)(0x02004830+0x265), then store r.
 * Idioms: widened-temp &= -3 (movs+negs); pinned sh->r1 shift/copy;
 * honest s8 intermediates (sb2, ds) to force sign-extends the compiler
 * would otherwise fold through the final (u8); asm-barrier on `base`
 * defeats constant folding so *(base+0x265) emits two pool loads.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern void Ewram4E40_Init_0B4E4(void);
extern void Clr_0800B4C8(void);

__attribute__((section(".text.w24c_0800a6bc")))
u32 Ewram4830_StateReset_0800A6BC(u8 *p)
{
    u8 *r5 = (u8 *)0x02004830;
    u8 v = p[1];
    u8 b, r;
    u32 t;
    register s32 sh __asm__("r1");
    s32 shc;
    s8 q;
    u8 d;
    s8 sb2, ds;
    u32 base;

    if (v == 0) {
        p[1] = 1;
        Ewram4E40_Init_0B4E4();
        Clr_0800B4C8();
        t = p[19];
        t &= -3;
        p[19] = (u8)t;
    } else if (v != 1) {
        return 1;
    }

    b = *(r5 + 0x264);
    if (p[19] & 1) {
        sh = (s32)b << 24;
        shc = sh;
        if ((s8)(shc >> 24) > 1) {
            q = shc >> 26;
            d = q ? (u8)q : 1;
            sb2 = (s8)(sh >> 24);
            ds = (s8)d;
            r = (u8)(sb2 - ds);
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }

    if ((r << 24) > 0)
        goto store;
    r = 0;
    p[0] = 0;
    p[3] = 0;
    p[2] = 0;
    p[1] = 0;
    base = 0x02004830;
    __asm__ volatile("" : "+r" (base));
    *(u8 *)(base + 0x265) = 0;
store:
    *(r5 + 0x264) = r;
    return 1;
}
