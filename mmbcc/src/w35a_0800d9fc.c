/* W34-B v3: ChipSlot_Tick @ 0x0800D9FC. old_agbcc.
 * Fixes: base112 r2 pin; t13978 temp (sj s28->r3, adds r0,r3,r2);
 * p26 copy asm (r2+r4); s28a var reused for rowBase.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void sub_080042B8(u8 *p);
extern void sub_0800244C(u8 *p, u32 v);
extern void Wrap_08002904(u8 *s, u8 a, u8 b);
__asm__(".set sub_080042B8, 0x080042b8");
__asm__(".set sub_0800244C, 0x0800244c");

__attribute__((section(".text.w35a_0800d9fc")))
void ChipSlot_Tick(u8 *s)
{
    register u8 *pairs __asm__("r8");
    register u8 *tbl1 __asm__("ip");
    register u8 *p48 __asm__("r6") = s + 48;
    sub_080042B8(s + 112);
    {
        u32 b = s[10] >> 4;
        register u32 one __asm__("r3") = 1;
        u32 tv;
        b &= one;
        {
            register u8 *p35 __asm__("r1") = s + 35;
            if ((*p35 & 128) == 0)
                goto else_br;
            {
                u32 t;
                __asm__ volatile("add %0, %1, #0" : "=r" (t) : "r" (one));
                t ^= b;
                tv = t;
            }
            goto join;
        else_br:
            __asm__ volatile("" : "+r" (b));
            tv = (u8)b;
        join:;
        }
        p48[24] = (u8)tv;
    }
    p48[25] = (s[10] >> 5) & 1;
    {
        u8 *t116 = s + 116;
        register u32 base112 __asm__("r2") = *(u32 *)(s + 112);
        register u32 *pe __asm__("r1") = (u32 *)((u32)*t116 * 4 + base112);
        u8 jjb = s[117];
        s32 jj = (s8)jjb;
        p48[26] = *(u8 *)(*pe + jj * 2);
    }
    {
        register u8 *t13978 __asm__("r2") = (u8 *)0x08173978;
        u8 s28a;
        register u8 *sjaddr __asm__("r0");
        s8 sj;
        tbl1 = t13978;
        s28a = s[28];
        __asm__ volatile("add %0, %1, %2" : "=r" (sjaddr) : "r" (s28a), "r" (t13978));
        sj = *(s8 *)sjaddr;
        if (sj == -1)
            return;
        {
            u32 p26 = p48[26];
            register u32 p26r4 __asm__("r4");
            u8 s30v;
            __asm__ volatile("add %0, %1, #0" : "=r" (p26r4) : "r" (p26));
            s30v = s[30];
            if (s30v == p26)
                return;
            {
                register u32 *rowBase __asm__("r1") = (u32 *)0x08173654;
                u32 r28;
                u8 s29v;
                u32 ptrA;
                __asm__ volatile("" : "+r" (rowBase));
                r28 = *(rowBase + s28a);
                s29v = s[29];
                ptrA = *(u32 *)(r28 + s29v * 4);
                s[30] = (u8)p26;
                if (*(u32 *)(p48 + 8) != ptrA)
                    *(u32 *)(p48 + 8) = ptrA;
                {
                    register u32 sh __asm__("r0") = p26r4 * 8;
                    u8 r3v = *(u8 *)((u32)sh + (u32)ptrA + 5);
                    pairs = (u8 *)0x02005030;
                    {
                        register u8 s28b __asm__("r1") = s[28];
                        u8 *tt = tbl1;
                        s32 off = (s8)*(u8 *)(s28b + (u32)tt) * 8;
                        u8 *pair = (u8 *)((u32)off + (u32)pairs);
                        s16 v0 = *(s16 *)pair;
                        s32 key = (s28b << 8) | s[29];
                        u8 *q;
                        s16 v1;
                        u32 tmp;
                        s32 sh2;
                        u8 *sp2;
                        if (v0 != key)
                            goto store_h;
                        q = pairs + 2;
                        v1 = *(s16 *)((u32)off + (u32)q);
                        if (v1 == (s16)r3v)
                            return;
                    store_h:
                        *(s16 *)pair = (s16)key;
                        tmp = tbl1[s[28]];
                        sh2 = (s8)tmp * 8;
                        sp2 = pairs + 2;
                        *(s16 *)((u32)sh2 + (u32)sp2) = (s16)r3v;
                    }
                    {
                        register u32 *rb2 __asm__("r1");
                        u8 s28c;
                        u32 *rp;
                        u32 rv;
                        u8 s29v2;
                        u32 *p32;
                        u8 *p;
                        u16 v22;
                        u8 s31v;
                        u8 warg;
                        register u8 *tbl2 __asm__("r2");
                        u8 s28d;
                        rb2 = (u32 *)0x08173760;
                        __asm__ volatile("" : "+r" (rb2));
                        s28c = s[28];
                        rp = (u32 *)(s28c * 4 + (u32)rb2);
                        rv = *rp;
                        s29v2 = s[29];
                        rv += (u32)s29v2 * 4;
                        p32 = (u32 *)(rv + *(u32 *)rv);
                        p = (u8 *)p32;
                        p += r3v * 20;
                        v22 = *(u16 *)(p48 + 22);
                        sub_0800244C(p, ((u32)v22 << 5) + (128 << 9));
                        p += 12;
                        s31v = s[31];
                        warg = s31v >> 4;
                        tbl2 = (u8 *)0x081738F2;
                        __asm__ volatile("" : "+r" (tbl2));
                        s28d = s[28];
                        Wrap_08002904(p, warg, tbl2[s28d * 2]);
                    }
                }
            }
        }
    }
}
