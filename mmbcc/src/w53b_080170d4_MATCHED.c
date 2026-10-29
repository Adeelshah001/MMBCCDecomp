/* W53-B 0x080170d4 CLAIM (v19 + asm-copy clamp + base/j/t10/t17 pins + off-first adds)
 * 236 B exact, 0 diffs, old_agbcc -O2 -mthumb-interwork, linked-at-address.
 * TRUE extent 236 B (bx 0x080171a8, pad 0x080171aa, pools 0x080171ac-0x080171bf, next fn 0x080171c0).
 * Pools raw LE (re-derived): 0x082243d8 (71ac), 0x081705b0 (71b0), 0x020031e4 (71b4),
 * 0x02003670 (71b8), 0x000011ae (71bc).
 * Clamp: C masks first (ands r1,r0), THEN the asm copy (add r0,r1,#0) is compared
 * (cmp r0,#3) — unlike deleted v17, which compared the raw byte. v is &3-masked
 * (0..3), so the clamp never fires in ROM or here; the copy is a real copy, not
 * a miscompile. Pins are block-scoped with no call between def and last use
 * (base r1, one r1, t10 r3, t17 r0 — condition only, calls set args afresh,
 * j r0 — G load only). NOT v11/v17; no must-not-stage content.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

extern u32 *Tbl_082243D8[];
extern u16 Ptr_081705B0;
extern u8 G_02003670[];
extern u8 G_020031E4[];
extern u8 *Sub_08017000(int a, int b, int c, int d);
extern void ChipSlot_Setup(u8 *s, int a, int b);
extern void ChipSlot_IncUse(u8 *s, u8 n);
extern void Sub_080171C0(u8 *s);
__asm__(".set Tbl_082243D8, 0x082243d8");
__asm__(".set Ptr_081705B0, 0x081705b0");
__asm__(".set G_02003670, 0x02003670");
__asm__(".set G_020031E4, 0x020031e4");
__asm__(".set Sub_08017000, 0x08017000");

__attribute__((section(".text.w53b_080170d4")))
void Sub_080170D4(u8 *s)
{
    int v;
    u8 *q;
    u32 *e;
    {
        register u32 *base __asm__("r1") = Tbl_082243D8;
        int idx = s[9];
        int off = idx << 2;
        u32 *t = (u32 *)(off + (u32)base);
        {
            register u32 one __asm__("r1");
            one = 1;
            *(u32 *)(s + 12) = one;
            e = *t;
            *(u32 *)(s + 20) = e[1];
            *(u32 *)(s + 108) = 0;
            {
                register u8 t10 __asm__("r3") = s[10];
                s[10] = (t10 | 2) | one;
            }
        }
    }
    {
        register u8 t17 __asm__("r0") = s[17];
        if (t17 <= 1) {
            q = Sub_08017000(0, 0, 0, 0);
            if (q != 0) {
                *(u8 **)(q + 40) = s;
                q[16] = s[16];
                q[17] = s[17] + 1;
            }
        }
    }
    ChipSlot_Setup(s, 1536, 0);
    ChipSlot_IncUse(s, s[16]);
    if (*(u32 *)(s + 40) != 0) {
        u8 *p65 = s + 65;
        int m = -13;
        *p65 = (*p65 & m) | 4;
    }
    {
        register int j __asm__("r0") = (Ptr_081705B0 >> 4) * 2;
        v = G_020031E4[j] & 3;
    }
    {
        int c;
        __asm__ volatile("add %0, %1, #0" : "=r" (c) : "r" (v));
        if (c > 3)
            v = 3;
    }
    {
        u8 *p69 = s + 69;
        int sh = v << 2;
        int m = -13;
        *p69 = (*p69 & m) | sh;
    }
    {
        u8 *p34 = s + 34;
        int z = 0;
        *p34 = z;
        {
            int fl = G_02003670[0x11ae] & 4;
            u32 v80 = 152 << 9;
            if (fl != 0)
                v80 = 160 << 9;
            *(u32 *)(s + 80) = v80;
        }
        *(u32 *)(s + 84) = 240 << 6;
        s[18] = z;
    }
    Sub_080171C0(s);
}
