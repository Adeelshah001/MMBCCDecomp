/* Wave 41 coordinator landing: coordinator-verified 0-diff (standalone
 * rebuild + independent ROM-extract cmp). See staging/w41coord_verify/COORD_LOG.md.
 */
/* Wave 41 Worker D: 0x08020870, 232 B. State machine on struct s.
   t = *(s+40), u = *(s+44); tail call ChipSlot_Tick (0x0800D9FC, MATCHED).
   Externs: ChipSlot_Tick(u8*). Table 0x082243d8 (entries: +0 ptr, +8 u32). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w41d_08020870")))
void F_08020870(u8 *s)
{
    u8 *t = *(u8 **)(s + 40);
    u8 *u = *(u8 **)(s + 44);
    u32 a = *(u32 *)(t + 84);
    u32 b = *(u32 *)(t + 80);
    *(u32 *)(s + 80) = b;
    *(u32 *)(s + 84) = a;
    switch (s[13]) {
    case 0:
        if (*(s32 *)(s + 96) < 0) {
            *(s32 *)(s + 96) += 2048;
            if (*(s32 *)(s + 96) < 0)
                break;
            *(s32 *)(s + 96) = 0;
            *(s32 *)(s + 88) = 2048;
            s[13]++;
        } else {
            *(s32 *)(s + 96) += -2048;
            if (*(s32 *)(s + 96) > 0)
                break;
            *(s32 *)(s + 96) = 0;
            __asm__ volatile("" ::: "memory");
            *(s32 *)(s + 88) = -2048;
            s[13]++;
        }
        break;
    case 1:
        s[13]++;
        u[0]++;
        s[18] = u[0];
    case 2:
        if (u[0] >= s[18])
            break;
        s[13]++;
    case 3: {
        s32 nv = *(s32 *)(s + 96) + *(s32 *)(s + 88);
        *(s32 *)(s + 96) = nv;
        if (*(s32 *)(s + 88) > 0) {
            if (nv <= 76799)
                break;
        } else {
            if (nv > -76800)
                break;
        }
        s[13]++;
        break;
    }
    case 4: {
        u8 *base;
        u32 *slot;
        u[0]++;
        base = (u8 *)0x082243d8;
        __asm__ volatile("" ::: "memory");
        slot = (u32 *)(base + s[9] * 4);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)(*slot + 8);
        break;
    }
    default:
        break;
    }
    *(u32 *)(s + 80) += *(u32 *)(s + 96);
    *(u32 *)(s + 84) += *(u32 *)(s + 100);
    ChipSlot_Tick(s);
}
