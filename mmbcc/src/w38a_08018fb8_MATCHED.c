/* W38-A: 0x08018fb8, 216 B. Move-task step (1823c family variant,
 * int return). AddMirrored(s,s[88],s[92]); s[88]+=s[96];
 * s[92]+=s[100]; CopyMirrored(sp+4,s) [out dead]; mode = s[13]:
 * case 0: if (u8)(s[119]-3)>1 return 0; IncUse(s,tbl[s[17]]);
 * s[18]=45; s[13]++; return 0; case 1: if (--s[18]!=0) return 0;
 * SetBit16(s[44],3); ChipInit(tbl2[s[17]],nibble,15360,-1280,
 * s[44]); s[10]=253&s[10]&254; s[13]++; return 0; case 2:
 * if (u8)GetField(s[44])<=5 return 0; MaxAssign_17(s[44],7);
 * return 1; else return 0.
 * Callees: AddMirrored 0x0800dd4c, CopyMirrored 0x0800dd08
 * (BLOCKED, .set), IncUse 0x0800d9ec, SetBit16 0x080174a4,
 * ChipInit 0x080178a8, GetField17_U8 0x08017474, MaxAssign_17
 * 0x08017478 (all MATCHED except CopyMirrored).
 * NOTE: ChipInit staged as (int,int,int,int,u8*) returning u32*
 * (real callee is (u8,u8,u16,u16,u8*)) — ROM caller passes the
 * full 32-bit d (0xFFFFFB00) with no truncation, so the caller's
 * prototype must be 32-bit; flag for coordinator at landing.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBit16(u8 *s, int bit);
extern u32 *ChipInit_080178A8(int a, int b, int c, int d, u8 *e);
extern u8 GetField17_U8(u8 *p);
extern void MaxAssign_17(u8 *s, int v);

__attribute__((section(".text.w38a_08018fb8")))
int Sub_08018FB8(u8 *s)
{
    u32 out[2];
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    return 0;
gt1:
    if (mode == 2)
        goto c2;
    return 0;
c0:
    if ((u8)(s[119] - 3) > 1)
        return 0;
    {
        register u8 *base __asm__("r0");
        base = (u8 *)0x082265bc;
        __asm__ volatile("" : "+r"(base));
        ChipSlot_IncUse(s, *(base + s[17]));
    }
    s[18] = 45;
    goto tail_inc;
c1:
    if (--s[18] != 0)
        return 0;
    SetBit16(*(u8 **)(s + 44), 3);
    {
        register u8 *base __asm__("r0");
        base = (u8 *)0x082265be;
        __asm__ volatile("" : "+r"(base));
        ChipInit_080178A8(*(base + s[17]), ((u32)s[35] << 28) >> 28, 15360, -1280, *(u8 **)(s + 44));
    }
    {
        /* ROM keeps two separate ANDs (&253 then &254); plain
         * C folds to a single &252, so pin the intermediate
         * with a barrier. */
        int t = 253 & s[10];
        int m = 254;
        __asm__ volatile("" : "+r"(t));
        s[10] = t & m;
    }
    goto tail_inc;
tail_inc:
    s[13]++;
    return 0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        return 0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
}
