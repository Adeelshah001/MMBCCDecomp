/* w50c 0x0800FEE0 (276 B) v8 — v7 + asm barrier on pp after then-branch assignment in mode0/mode5 selects (pool-derivation blocker probe) + DISTINCT comment asms AFTER each merged test (between test and break/increment; suffix-interior position, per the 42878 v9/v10 breakthrough where suffix-interior asm broke tail merging). Tests: mode0-second, mode2, mode3, mode4. */
/* w49d v3 — goto ret for all returns — no entry guard (switch bounds check IS
 * the entry test; default returns), inline s[0x42], ToU8 as u16 return,
 * if/else pool select (try to defeat sub-derivation of 0x02005168).
 * v1: 296 B / 218 diffs (redundant entry guard -> double test).
 * Decode (fresh ROM dis, 2026-10-26; pools raw LE):
 *   Entry guard: if s[1] > 6 return s[0]. Loop: switch(s[1]) with
 *   shared s[1]++ after each case (break), failure (0) -> return s[0],
 *   mode 6 success -> return s[0] directly (no increment).
 *   Jump table: pool at 0x0800FEF8 holds table base 0x0800FEFC;
 *   entries (modes 0..6): 0x0800FF18, 0x0800FF68, 0x0800FF86,
 *   0x0800FF92, 0x0800FF9E, 0x0800FFAA, 0x0800FFD8.
 *   Mode 0: B2B4, then s[0x42] pool select (0x02005168 if 0 else
 *   0x0200517c), ToU8(pp[10]), B148((s[0x42]==0)?1:3, (s16)t, 1).
 *   Mode 1: B2D8, then B320(s[0x30], 0, 0, 0).
 *   Mode 2: B308. Mode 3: B2B4. Mode 4: B2F0.
 *   Mode 5: s[0x42] pool select (same two pools), NewNode(s[0x42],
 *   pp[10]); NULL -> return; else s[0x3c] = nd.
 *   Mode 6: Byte12_Gt1(s[0x3c]); 0 -> return; else s[0x3c] = 0,
 *   Ewram5160_Init_10508(0), return s[0].
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u32 CheckAndSet_B2B4(void);
extern int Tst_0800B2D8(void);
extern u32 Check_B308(void);
extern int Tst_0800B2F0(void);
extern int Sub_0800B320(u32 *a, u32 *b, u32 c, u32 d);
extern u8 *NewNode_0801CDAC(u32 a, u8 b);
extern unsigned int Byte12_Gt1_0801cdd8(u8 *s);
extern u16 ToU8(u32 v);
extern u8 sub_0800B148(u8 a, s16 b, u8 c);
extern void Ewram5160_Init_10508(u8 v);

__attribute__((section(".text.w51c_0800fee0")))
u8 Func_0800FEE0(u8 *s) {
    {
        switch (s[1]) {
        case 0:
            if ((u8)CheckAndSet_B2B4() == 0)
                goto ret;
            {
                u8 *pp;
                u16 t;
                if (s[0x42] == 0) {
                    pp = (u8 *)0x02005168;
                    __asm__ volatile("" : "+r" (pp));
                } else
                    pp = (u8 *)0x0200517c;
                t = ToU8(pp[10]);
                if ((u8)sub_0800B148((s[0x42] == 0) ? 1 : 3, (s16)t, 1) == 0)
                    goto ret;
                __asm__ volatile("@ fee0-m0");
            }
            goto inc;
        case 1:
            if ((u8)Tst_0800B2D8() == 0)
                goto ret;
            if ((u8)Sub_0800B320((u32 *)*(u32 *)(s + 0x30), 0, 0, 0) == 0)
                goto ret;
            goto inc;
        case 2:
            if ((u8)Check_B308() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m2");
            goto inc;
        case 3:
            if ((u8)CheckAndSet_B2B4() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m3");
            goto inc;
        case 4:
            if ((u8)Tst_0800B2F0() == 0)
                goto ret;
            __asm__ volatile("@ fee0-m4");
            goto inc;
        case 5: {
            register u32 b __asm__("r2") = s[0x42];
            register u8 *pp __asm__("r0");
            u8 *nd;
            if (b == 0) {
                pp = (u8 *)0x02005168;
                __asm__ volatile("" : "+r" (pp));
            } else
                pp = (u8 *)0x0200517c;
            nd = NewNode_0801CDAC(b, pp[10]);
            if (nd == 0)
                goto ret;
            *(u8 **)(s + 0x3c) = nd;
            /* fallthrough to inc */
        }
        inc:
            s[1]++;
            goto ret;
        case 6:
            if ((u8)Byte12_Gt1_0801cdd8(*(u8 **)(s + 0x3c)) == 0)
                goto ret;
            *(u8 **)(s + 0x3c) = 0;
            Ewram5160_Init_10508(0);
            goto ret;
        default:
            goto ret;
        }
    }
ret:
    return s[0];
}


