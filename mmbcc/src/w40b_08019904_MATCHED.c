/* W39-A: 0x08019904, 312 B (TSV; next 0x08019a3c).
 * Vec2_AddMirrored(s, s[88], s[92]); s[88]+=s[96]; s[92]+=s[100];
 * Vec2_CopyMirrored(buf, s); switch (s[13]) {
 *  case 0: if ((u8)(s[119]-3)>1) return 0; Text_SelectBlobIdx(132);
 *    s[100]=80; IncUse(s,7); goto tail;
 *  case 1: if (buf[1]<=-1280) return 0; s[92]=-768; IncUse(s,7); goto tail;
 *  case 2: if (buf[1]<=-1280) return 0; if (s[92]<=0) return 0;
 *    s[92]=0; s[100]=0; IncUse(s,s[17]); s[18]=20; goto tail;
 *  case 3: s[18]--; if (s[18]!=0) return 0; SetBit16(*(u8**)(s+44),3);
 *    IncUse(s,8); s[18]=15; goto tail;
 *  case 4: s[18]--; if (s[18]!=0) return 0;
 *    ChipInit(0x59, s[35]&0xF, 0x3c00, -2560, *(u8**)(s+44));
 *    s[10]=(s[10]&0xfd)&0xfe; goto tail;
 *  case 5: if ((u8)GetField17(*(u8**)(s+44))<=5) return 0; return 1;
 *  default: return 0; }
 * tail: s[13]++; return 0.
 * Jump table: literal 0x08019944 at +0x3c, entries at +0x40..+0x54.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *o, int x, int y);
extern void Vec2_CopyMirrored(int *d, u8 *s);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern int Text_SelectBlobIdx(int idx);
extern void SetBit16(u8 *s, int bit);
extern void ChipInit_080178A8(int a, int b, int c, int d, u8 *e);
extern int GetField17_U8(u8 *s);

__attribute__((section(".text.w40b_08019904")))
int Sub_08019904(u8 *s)
{
    int buf[2];
    register int x __asm__("r2");
    int y;

    Vec2_AddMirrored(s, *(int *)(s + 88), *(int *)(s + 92));
    *(int *)(s + 88) += *(int *)(s + 96);
    *(int *)(s + 92) += *(int *)(s + 100);
    Vec2_CopyMirrored(buf, s);
    x = buf[0];
    y = buf[1];
    __asm__ volatile("" : : "r"(x));
    switch (s[13]) {
    case 0:
        if ((u8)(s[119] - 3) > 1)
            return 0;
        Text_SelectBlobIdx(132);
        *(int *)(s + 100) = 80;
        ChipSlot_IncUse(s, 7);
        __asm__ volatile("" ::: "memory");
        goto tail;
    case 1:
        if (y <= -1280)
            return 0;
        *(int *)(s + 92) = -768;
        ChipSlot_IncUse(s, 7);
        goto tail;
    case 2:
        if (y <= -1280)
            return 0;
        if (*(int *)(s + 92) <= 0)
            return 0;
        *(int *)(s + 92) = 0;
        *(int *)(s + 100) = 0;
        ChipSlot_IncUse(s, s[17]);
        s[18] = 20;
        goto tail;
    case 3:
        s[18]--;
        if (s[18] != 0)
            return 0;
        SetBit16(*(u8 **)(s + 44), 3);
        ChipSlot_IncUse(s, 8);
        s[18] = 15;
        goto tail;
    case 4:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipInit_080178A8(0x59, (int)(((u32)s[35] << 28) >> 28), 0x3c00, -2560, *(u8 **)(s + 44));
        s[10] &= 0xfd;
        s[10] &= 0xfe;
        /* fall through to tail (label inside switch, before case 5) */
    tail:
        s[13]++;
        return 0;
    case 5:
        if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
            return 0;
        return 1;
    default:
        return 0;
    }
}

__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
