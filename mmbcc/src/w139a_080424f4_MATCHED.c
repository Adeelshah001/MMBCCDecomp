/* Wave 139-A v8 (STAGED ONLY, NOT LANDED): 0x080424F4, TRUE extent 320 B
 * (next fn 0x08042634). Manual hand-read, plain-switch hypothesis: no
 * goto labels — GCC cross-jump merging is what shares case1/case3's
 * test+increment suffix (single test site at 0x25E8, single setup at
 * 0x25EE with scratch r2) and the increment tail (0x25F2, entered by
 * branch from case0/case2, fallthrough from case1/3). Case 0:
 * ldrh(s+0x46A4)==0 -> ret=1; else B148(1, 24514((u8)241F8(4096)), 5)
 * != 0 -> s[0x46AD]++. Case 1: B2D8 check; v = 24384(4096);
 * tv = Tbl[idx] with u8 idx = (u8)(v - 50) in its own statement;
 * B320(tv, *G1, *G2, 0) != 0 -> s[0x46AD]++. v8 fix vs v7: the
 * separate u8 idx statement makes old_agbcc emit the table-base
 * load AFTER subs/lsl and BEFORE lsrs, exactly as ROM does (v7
 * loaded it before subs/lsl: 6 diffs). Plain C, no barrier/pin.
 * Case 2: B308 check; ret = G[8]; if (ret==0) ret=1; else ret=0;
 * s[0x46AD]++. Case 3: B2B4 check -> s[0x46AD]++. Case 4: B2F0
 * check; s[0x46AC]=10; 5F44(0, T[0], T[1]). Return variable ret in
 * r5, s in r4. Plain C + file-scope .set stubs only (no pin, no
 * inline asm in body, no barrier). old_agbcc -O2 -mthumb-interwork.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 G_02004E40[];
extern s8 T_02004CA0[];
extern u32 Tbl_08232A5C[];
extern u32 G_082325D4;
extern u32 G_082325DC;
extern int Sub_080241F8(u16 a);
extern s16 Sub_08024514(u8 v);
extern int Sub_08024384(int a);
extern u8 Sub_0800B148(u8 a, s16 b, u8 c);
extern int Sub_0800B320(u32 a, u32 b, u32 c, u32 d);
extern u8 Sub_0800B2D8(void);
extern u8 Sub_0800B308(void);
extern u8 Sub_0800B2B4(void);
extern u8 Sub_0800B2F0(void);
extern void Sub_08005F44(int a, s8 b, s8 c);

__asm__(".set G_02004E40, 0x02004E40");
__asm__(".set T_02004CA0, 0x02004CA0");
__asm__(".set Tbl_08232A5C, 0x08232A5C");
__asm__(".set G_082325D4, 0x082325D4");
__asm__(".set G_082325DC, 0x082325DC");
__asm__(".set Sub_080241F8, 0x080241F8");
__asm__(".set Sub_08024514, 0x08024514");
__asm__(".set Sub_08024384, 0x08024384");
__asm__(".set Sub_0800B148, 0x0800B148");
__asm__(".set Sub_0800B320, 0x0800B320");
__asm__(".set Sub_0800B2D8, 0x0800B2D8");
__asm__(".set Sub_0800B308, 0x0800B308");
__asm__(".set Sub_0800B2B4, 0x0800B2B4");
__asm__(".set Sub_0800B2F0, 0x0800B2F0");
__asm__(".set Sub_08005F44, 0x08005F44");

__attribute__((section(".text.w139a_080424f4_v8")))
int Sub_080424F4(u8 *s)
{
    int ret = 0;
    { u8 *gp = G_02004E40; gp[20] |= 1; }
    switch (s[0x46AD]) {
    case 0:
        if (*(u16 *)(s + 0x46A4) == 0) {
            ret = 1;
            break;
        }
        if ((u8)Sub_0800B148(1, Sub_08024514((u8)Sub_080241F8(4096)), 5) != 0)
            s[0x46AD]++;
        break;
    case 1:
        if ((u8)Sub_0800B2D8() == 0)
            break;
        {
            int v = Sub_08024384(4096);
            u8 idx = (u8)(v - 50);
            int tv = Tbl_08232A5C[idx];
            if ((u8)Sub_0800B320(tv, G_082325D4, G_082325DC, 0) == 0)
                break;
        }
        s[0x46AD]++;
        break;
    case 2:
        if ((u8)Sub_0800B308() == 0)
            break;
        ret = G_02004E40[8];
        if (ret == 0)
            ret = 1;
        else
            ret = 0;
        s[0x46AD]++;
        break;
    case 3:
        if ((u8)Sub_0800B2B4() == 0)
            break;
        s[0x46AD]++;
        break;
    case 4:
        if ((u8)Sub_0800B2F0() == 0)
            break;
        s[0x46AC] = 10;
        Sub_08005F44(0, T_02004CA0[0], T_02004CA0[1]);
        break;
    default:
        break;
    }
    return ret;
}
