/* W57-A: 0x08025a64 MATCHED (standalone 0-diff, old+main, see RESULTS.md).
 * Mechanisms vs W56 v17 base: block-scoped r6 temp pin (tbh) at the load
 * so the ldrb targets tb's home r6 (not the arg reg r0); block-scoped
 * r0/r1/r2 pin-args at the three 3-arg calls so arg moves emit in
 * r0,r1,r2 order (built had the r2 move first). Trailing .balign 4, 0
 * gives the ROM 00 00 pad. old_agbcc -O2 -mthumb-interwork (main identical).
 * W55-D: 0x08025a64, 252 B. Hi-reg multi-path, returns int.
 * tb = s[idx*4+20]; (26710(tb)&4)? return 8;
 * (u16)26700(tb)==1 ? [ (u8)25730(s,0)? return (u16)25ca0(s,0,idx);
 *   (u16)25754(s)>(u16)258a4(s,tb)? return 1;
 *   25638(s,0,idx); 256dc(s+idx*4+20,0); return 0 ]
 * : [ v=(u8)2567c(s); v==0? return 6;
 *   v<=9 ? [ (u16)2583c(s,0,(s16)266f0(tb))==0 ?
 *     25638(s,v,idx); 256dc(s+idx*4+20,v); return 0 : return 2 ]
 *   : [ (u16)257f8(s)>=(u16)266f0(tb) ?
 *     25638(s,v,idx); 256dc(s+idx*4+20,v); return 0 : return 3 ] ].
 * No pools (all immediates); bx r1 epilogue (r0 = return value).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern int Sub_08026710(u8 a);
__asm__(".set Sub_08026710, 0x08026710");
extern int Sub_08026700(u8 a);
__asm__(".set Sub_08026700, 0x08026700");
extern int Sub_08025730(u8 *s, int b);
__asm__(".set Sub_08025730, 0x08025730");
extern int Sub_08025CA0(u8 *s, int b, u8 idx);
__asm__(".set Sub_08025CA0, 0x08025ca0");
extern int Sub_08025754(u8 *s);
__asm__(".set Sub_08025754, 0x08025754");
extern int Sub_080258A4(u8 *s, u8 tb);
__asm__(".set Sub_080258A4, 0x080258a4");
extern void Sub_08025638(u8 *s, int b, u8 idx);
__asm__(".set Sub_08025638, 0x08025638");
extern void Sub_080256DC(u8 *s, int b);
__asm__(".set Sub_080256DC, 0x080256dc");
extern int Sub_0802567C(u8 *s);
__asm__(".set Sub_0802567C, 0x0802567c");
extern int Sub_080266F0(u8 a);
__asm__(".set Sub_080266F0, 0x080266f0");
extern int Sub_0802583C(u8 *s, int b, s16 c);
__asm__(".set Sub_0802583C, 0x0802583c");
extern int Sub_080257F8(u8 *s);
__asm__(".set Sub_080257F8, 0x080257f8");

__attribute__((section(".text.w57a_08025a64")))
int Sub_08025A64(u8 *s, u8 idx)
{
    register u8 idx8 __asm__("r8") = idx;
    register int off __asm__("r7") = idx8 * 4;
    int tb;
    register int tb9 __asm__("r9");
    {
        register int tbh __asm__("r6") = s[off + 20];
        tb = tbh;
        tb9 = tbh;
    }
    if ((Sub_08026710(tb) & 4) != 0)
        return 8;
    if ((u16)Sub_08026700(tb) == 1) {
        if ((u8)Sub_08025730(s, 0) != 0) {
            register u8 *p0 __asm__("r0") = s;
            register int p1 __asm__("r1") = 0;
            register u8 p2 __asm__("r2") = idx8;
            return (u16)Sub_08025CA0(p0, p1, p2);
        }
        if ((u16)Sub_08025754(s) > (u16)Sub_080258A4(s, tb))
            return 1;
        {
            register u8 *p0 __asm__("r0") = s;
            register int p1 __asm__("r1") = 0;
            register u8 p2 __asm__("r2") = idx8;
            Sub_08025638(p0, p1, p2);
        }
        Sub_080256DC((off + 20) + s, 0);
        return 0;
    } else {
        u8 v = (u8)Sub_0802567C(s);
        if (v == 0)
            return 6;
        if (v <= 9) {
            if ((u16)Sub_0802583C(s, 0, (s16)Sub_080266F0(tb)) == 0) {
                {
                    register u8 *p0 __asm__("r0") = s;
                    register int p1 __asm__("r1") = v;
                    register u8 p2 __asm__("r2") = idx8;
                    Sub_08025638(p0, p1, p2);
                }
                Sub_080256DC((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 2;
        } else {
            if ((u16)Sub_080257F8(s) >= (u16)Sub_080266F0(tb9)) {
                {
                    register u8 *p0 __asm__("r0") = s;
                    register int p1 __asm__("r1") = v;
                    register u8 p2 __asm__("r2") = idx8;
                    Sub_08025638(p0, p1, p2);
                }
                Sub_080256DC((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 3;
        }
    }
}

__asm__(".balign 4, 0");
