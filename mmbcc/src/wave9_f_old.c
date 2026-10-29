/* Wave 9 batch F: blocked revisits (old_agbcc).
 * Evidence: docs/match_notes_wave9_F.md, docs/wave9_F_results.tsv.
 *  - FlagToggle_080481FC @0x080481fc (100B incl 00 00 pad): W6-L4 3-byte
 *    near-miss cracked via pinned r4/r5/r6 prologue, tied-opaque pool loads,
 *    inline-asm XOR and ands-dest. Returns int (no u8 zero-extend in ROM).
 *  - TableLookup_U16 @0x08011c58 (40B): W7-F/W8-B mask/copy fusion cracked
 *    via pinned r3/r0, hardcoded-r1 b-mask asm, goto dual-bhi, pinned r2 pool.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern s16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w9f_0x080481fc")))
int FlagToggle_080481FC(u8 *p)
{
    register u8 *pp __asm__("r4") = p;
    register u32 ret __asm__("r5");
    register u16 *gg __asm__("r6");
    __asm__ volatile("movs %0,#0" : "=r"(ret));
    __asm__ volatile("" : "=r"(gg) : "0"((u16 *)0x02002F50));
    {
        u16 c0 = gg[2];
        if ((c0 & 48) != 0) {
        register u32 o2 __asm__("r2");
        register u32 rv __asm__("r0");
        register u8 t3 __asm__("r3");
        register u8 *q __asm__("r1");
        register u16 *hh __asm__("r2");
        u32 x;
        u8 qv;
        Text_SelectBlobIdx(0x66);
        __asm__ volatile("" : "=r"(o2) : "0"(0x46B4));
        q = pp + o2;
        __asm__ volatile("movs %0,#1" : "=r"(rv));
        __asm__ volatile("ldrb %0,[%1]" : "=r"(t3) : "r"(q));
        __asm__ volatile("eor %0,%1" : "+r"(rv) : "r"(t3));
        *q = (u8)rv;
        __asm__ volatile("" : "=r"(hh) : "0"((u16 *)0x02004CE0));
        rv <<= 3;
        qv = *(volatile u8 *)q;
        x = rv - qv;
        x = (x << 4) + 24;
        hh[20] = (u16)x;
        hh[21] = 32;
        }
    }
    {
        u16 c1 = gg[2];
        if ((c1 & 1) != 0) {
            ret = 1;
        } else {
            register u32 t __asm__("r0");
            __asm__ volatile("" : "=r"(t) : "0"(2));
            __asm__ volatile("and %0,%1" : "+r"(t) : "r"((u32)c1));
            if (t != 0)
                ret = 2;
        }
    }
    return ret;
}

static const u16 w9f_pad_080481fc __attribute__((section(".text.w9f_0x080481fc"))) = 0;

/* ---- TableLookup_U16 @0x08011c58 (40B) ---- */

__attribute__((section(".text.w9f_0x08011c58")))
u16 TableLookup_U16(u8 a0, u8 a1)
{
    register u32 ac __asm__("r3");
    register u32 bm __asm__("r0");
    register u16 *tbl __asm__("r2");
    u32 am = (u32)a0;
    u32 t;
    u32 idx;
    u16 res;
    __asm__ volatile("" : "+r"(am));
    ac = am;
    __asm__ volatile(
        "lsl r1,r1,#24\n\t"
        "lsr %0,r1,#24"
        : "=r"(bm) : : "r1");
    if (ac > 5)
        goto ret0;
    if (bm > 15)
        goto ret0;
    __asm__ volatile("" : "=r"(tbl) : "0"((u16 *)0x08173EEC));
    bm <<= 1;
    {
        register u32 t __asm__("r1") = ac << 5;
        u32 addr;
        idx = bm + t;
        addr = idx + (u32)tbl;
        res = *(u16 *)addr;
    }
    goto end;
ret0:
    res = 0;
end:
    return res;
}

