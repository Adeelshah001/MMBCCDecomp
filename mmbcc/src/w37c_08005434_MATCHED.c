/* W37-C MATCHED: 0x08005434, 156 B, old_agbcc, pure C, 0 diffs.
 * Struct init on (s, u16 a, u16 b). Idioms: p28/p8 variables (kept
 * in r6/r5); p8 pinned r5; if-overwrite-then-store for the flag
 * values (not ternary); s += 40 in place; base+offset pool via barrier.
 * InitTriple(s+28, s+20, 0, 0); s[32] = s+560;
 * t = *(u8*)(0x02003670 + 0x11ae) & 4 (u8);
 * s[20] = t ? 30720 : 28672; s[24] = t ? 20480 : 18432;
 * *(s+560+4) = 0; *(s+560) = 0;
 * StoreTwoHalves(s+8, (s16)a, (s16)b);
 * Sub_0800410C(s+40); SetU32_200(s+40, s+28); SetField204(s+40, s+8).
 * Extern callees + addresses: InitTriple_03090 0x08003090 (MATCHED),
 * StoreTwoHalves_030BC 0x080030bc (MATCHED), Sub_0800410C 0x0800410c
 * (BLOCKED, .set), SetU32_200 0x08004158 (MATCHED), SetField204_04164
 * 0x08004164 (MATCHED).
 * Pools (LE): 0x02003670, 0x11ae.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

extern void InitTriple_03090(u8 *p, u32 a, u32 b, u32 c);
extern void StoreTwoHalves_030BC(u8 *p, s16 a, s16 b);
extern void Sub_0800410C(u8 *p);
__asm__(".set Sub_0800410C, 0x0800410c");
extern void SetU32_200(u8 *p, u32 v);
extern void SetField204_04164(u8 *p, u32 v);

__attribute__((section(".text.w37c_08005434")))
void Sub_08005434(u8 *s, u16 a, u16 b)
{
    u8 *p28;
    register u8 *p8 __asm__("r5");
    u8 *q;
    u8 t;
    u8 *gp;
    u32 v;
    p28 = s + 28;
    InitTriple_03090(p28, (u32)(s + 20), 0, 0);
    q = s + 560;
    *(u32 *)(s + 32) = (u32)q;
    gp = (u8 *)0x02003670;
    __asm__ volatile("" : "+r"(gp));
    t = gp[0x11ae] & 4;
    v = 28672;
    if (t != 0) v = 30720;
    *(u32 *)(s + 20) = v;
    v = 18432;
    if (t != 0) v = 20480;
    *(u32 *)(s + 24) = v;
    *(u32 *)(q + 4) = 0;
    *(u32 *)q = 0;
    p8 = s + 8;
    StoreTwoHalves_030BC(p8, (s16)a, (s16)b);
    s += 40;
    Sub_0800410C(s);
    SetU32_200(s, p28);
    SetField204_04164(s, p8);
}
