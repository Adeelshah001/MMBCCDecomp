/* W47-D v8 (v6 + mode4 ptr-first only) (pinned r0, mode2 base pin) (v1 + s16 param, shift-test tail, mode4 z): 0x0804472c, 252 B, jump-table state machine (4713c family).
 * Decode from fresh ROM disassembly (pools re-derived from raw LE bytes):
 *  push {r4,lr}; r4=s; mode = s[0x46ad]; if (mode>4) -> ret;
 *  jump table at 0x08044650 (entries 4664/4684/46c0/46e4/4700).
 *  case 0: r = B148(1, (s16)Sub200((u8)Tbl241F8(4096)), 1); goto tail;
 *  case 1: if (B2D8()==0) -> ret;
 *          r = B320(((u32*)0x08232dd8)[(u8)(Tbl24384(4096)-50)], 0,0,0);
 *          if (r==0) -> ret; s[0x46ad]++; -> ret;
 *  case 2: gEwram_02004E40[20] |= 1; if (B308()==0) -> ret;
 *          s[0x46ad]++; -> ret;
 *  case 3: r = B2B4(); goto tail;
 *  case 4: if (B2F0()==0) -> ret; s[0x46ac]=5; s[0x46ad]=0; -> ret;
 *  tail: if (r!=0) s[0x46ad]++;
 *  ret: return 0.
 *  Pools (raw LE): 4648=0x000046ad, 464c=0x08044650 (table, linker),
 *  46b8=0x08232dd8, 46bc=0x000046ad, 46dc=0x02004e40, 46e0=0x000046ad,
 *  46fc=0x000046ad, 4724=0x000046ac, 4728=0x000046ad.
 *  All callees MATCHED (registry-checked).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

extern u8 TblGetByte_241F8(u16 a);
extern u16 Sub200_08024514(u8 v);
extern u8 Sub_0800B148(u8 a, s16 b, u8 c);
extern u8 Tst_0800B2D8(void);
extern u8 TblGetByte_24384(u16 a);
extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);
extern u8 Check_B308(void);
extern u8 CheckAndSet_B2B4(void);
extern u8 Tst_0800B2F0(void);
extern u8 gEwram_02004E40[];

__attribute__((section(".text.w47d_0804472c")))
int Sub_0804472c(u8 *s)
{
    register u8 r __asm__("r0");
    switch (s[0x46ad]) {
    case 0:
        r = Sub_0800B148(1, (s16)Sub200_08024514((u8)TblGetByte_241F8(4096)), 1);
        goto tail;
    case 1:
        if (Tst_0800B2D8() == 0)
            goto ret;
        r = Sub_0800B320(((u32 *)0x08232dd8)[(u8)(TblGetByte_24384(4096) - 50)], 0, 0, 0);
        if (r == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 2:
        {
            register u8 *gp __asm__("r0") = gEwram_02004E40;
            gp[20] |= 1;
        }
        if (Check_B308() == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 3:
        r = CheckAndSet_B2B4();
        goto tail;
    tail:
        if ((r << 24) != 0)
            s[0x46ad]++;
        goto ret;
    case 4:
        if (Tst_0800B2F0() == 0)
            goto ret;
        {
            u8 *pp = s + 0x46ac;
            int z = 0;
            *pp = 5;
            s[0x46ad] = z;
        }
        goto ret;
    default:
        goto ret;
    }
ret:
    return 0;
}

__asm__(
    ".set Sub_0800B148, 0x0800b148\n"
    ".set TblGetByte_24384, 0x08024384\n"
    ".globl gEwram_02004E40\n.set gEwram_02004E40, 0x02004e40\n"
);
