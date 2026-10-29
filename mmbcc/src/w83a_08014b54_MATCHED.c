/* Wave 81-A v1: 0x08014B54, registry-fresh. TRUE extent 412 B (next 0x08014CF0).
 * Decode: void F(u8 *s). r5 = s+124. Switch on s[14] (10 cases, jump table;
 * pool word at 0x8014B70 holds table base 0x8014B74; >9 -> epilogue).
 * Epilogue (all paths): Call_0800D9FC(s) [ChipSlot_Tick stub]; return.
 * Inc path (most cases): s[14]++ then epilogue.
 * case 0: SetMirrored(s,-15360,0); D9EC(s,2); A378(152); inc.
 * case 1: if (Poll1F50(s)==0) break; SetMirrored(s,-1536,0); D9EC(s,1); inc.
 * case 2: if (Poll1F50(s)==0) break; SetBit16(*(u32*)(s+44),3); D9EC(s,8); inc.
 * case 3: if (Poll1F50(s)==0) break; ChipInit178A8(132, s[35]&0xF, 240<<6, 0,
 *   *(u32*)(s+44)); D9EC(s,9); inc.
 * case 4: if (Poll1F50(s)==0) break; T[0x11AF]=(T[0x11AF]&15)|(240<<6);
 *   A378(135); s[18]=25; inc.
 * case 5: if ((s8)--s[18] != 0) break; D9EC(s,10); inc.
 * case 6: if (Poll1F50(s)==0) break; D9EC(s,2); inc.
 * case 7: if (Poll1F50(s)==0) break; SetMirrored(s,-15360,0); D9EC(s,2); inc.
 * case 8: if (Poll1F50(s)==0) break; D9EC(s,0); inc.
 * case 9: if ((u8)GetField17(*(u32*)(s+44)) <= 5) break; Call17478(*(u32*)(s+44),7);
 *   Call17464(*(u32*)(s+44)); *(u32*)(s+44)=0; s[128]=0; Call1F68(s,0); epilogue.
 * .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

void Call_0800DD2C(u8 *s, s32 x, s32 y);
void Call_0800D9EC(u8 *s, u32 a);
void Call_0804A378(u32 a);
s16 Call_08011F50(u8 *s);
void Call_080174A4(u32 a, u32 b);
void Call_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);
u8 Call_08017474(u8 *s);
void Call_08017478(u32 a, u32 b);
void Call_08017464(u32 a);
void Call_08011F68(u8 *s, u32 a);
void Call_0800D9FC(u8 *s);

extern u8 T_02003670[];

__attribute__((section(".text.w83a_08014b54")))
void sub_08014B54(u8 *s)
{
    u8 *q = s + 124;
    switch (s[14]) {
    case 0:
        Call_0800DD2C(s, -15360, 0);
        Call_0800D9EC(s, 2);
        Call_0804A378(152);
        s[14]++;
        break;
    case 1:
        if (Call_08011F50(s) == 0)
            break;
        Call_0800DD2C(s, -1536, 0);
        Call_0800D9EC(s, 1);
        s[14]++;
        break;
    case 2:
        if (Call_08011F50(s) == 0)
            break;
        Call_080174A4(*(u32 *)(s + 44), 3);
        Call_0800D9EC(s, 8);
        s[14]++;
        break;
    case 3:
        if (Call_08011F50(s) == 0)
            break;
        Call_080178A8(132, ((u32)s[35] << 28) >> 28, 240 << 6, 0, *(u32 *)(s + 44));
        Call_0800D9EC(s, 9);
        s[14]++;
        break;
    case 4:
        if (Call_08011F50(s) == 0)
            break;
        {
            u8 mk = 15;
            u32 off = 0x11AF;
            u8 *p = T_02003670 + off;
            u8 c = 240;
            u8 b = *p;
            *p = (b & mk) | c;
        }
        Call_0804A378(135);
        s[18] = 25;
        s[14]++;
        break;
    case 5:
        if ((s8)--s[18] != 0)
            break;
        Call_0800D9EC(s, 10);
        s[14]++;
        break;
    case 6:
        if (Call_08011F50(s) == 0)
            break;
        Call_0800D9EC(s, 2);
        s[14]++;
        break;
    case 7:
        if (Call_08011F50(s) == 0)
            break;
        Call_0800DD2C(s, -15360, 0);
        Call_0800D9EC(s, 2);
        s[14]++;
        break;
    case 8:
        if (Call_08011F50(s) == 0)
            break;
        Call_0800D9EC(s, 0);
        s[14]++;
        break;
    case 9:
        if ((u8)Call_08017474((u8 *)*(u32 *)(s + 44)) <= 5)
            break;
        Call_08017478(*(u32 *)(s + 44), 7);
        Call_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        q[4] = 0;
        Call_08011F68(s, 0);
        break;
    default:
        break;
    }
    Call_0800D9FC(s);
}

__asm__(
    ".globl Call_0800DD2C\n.set Call_0800DD2C, 0x0800DD2C\n"
    ".globl Call_0800D9EC\n.set Call_0800D9EC, 0x0800D9EC\n"
    ".globl Call_0804A378\n.set Call_0804A378, 0x0804A378\n"
    ".globl Call_08011F50\n.set Call_08011F50, 0x08011F50\n"
    ".globl Call_080174A4\n.set Call_080174A4, 0x080174A4\n"
    ".globl Call_080178A8\n.set Call_080178A8, 0x080178A8\n"
    ".globl Call_08017474\n.set Call_08017474, 0x08017474\n"
    ".globl Call_08017478\n.set Call_08017478, 0x08017478\n"
    ".globl Call_08017464\n.set Call_08017464, 0x08017464\n"
    ".globl Call_08011F68\n.set Call_08011F68, 0x08011F68\n"
    ".globl Call_0800D9FC\n.set Call_0800D9FC, 0x0800D9FC\n"
    ".globl T_02003670\n.set T_02003670, 0x02003670\n"
);
