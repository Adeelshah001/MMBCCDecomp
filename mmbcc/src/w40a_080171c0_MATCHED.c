/* W39-B V6: 0x080171c0, move-task step (mode on s[13]).
 * Path A (s[40]==0): mode machine. Path B (s[40]!=0): follow other[80].
 * Callees: Byte12_Gt1_080170c4 (MATCHED, strip .set at landing),
 * ChipSlot_Tick 0x0800d9fc (MATCHED, strip .set), Sub_080052A0 AbsScale
 * (BLOCKED, keep .set), gEwram_02003670 (build global, strip .set),
 * Tbl 0x082243d8 (build global Tbl_082243D8, strip .set).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern unsigned int Byte12_Gt1_080170c4(u8 *s);
extern void ChipSlot_Tick(u8 *s);
extern int Sub_080052A0(int x);
extern u8 gEwram_02003670[];
extern u32 *Tbl_082243D8[];

__attribute__((section(".text.w40a_080171c0")))
void Sub_080171C0(u8 *s)
{
    u8 *other = *(u8 **)(s + 40);
    if (other == 0) {
        register int mode __asm__("r6") = s[13];
        if (mode == 1) goto c1;
        else if (mode > 1) goto gt;
        else if (mode == 0) goto c0;
        else goto tail;
    gt:
        if (mode == 2) goto c2;
        else if (mode == 3) goto c3;
        else goto tail;
    c0:
        s[13] = 1;
        *(int *)(s + 88) = 512;
        *(int *)(s + 96) = 96;
    c1:
        *(int *)(s + 80) -= *(int *)(s + 88);
        *(int *)(s + 88) += *(int *)(s + 96);
        if (*(int *)(s + 88) > 3072)
            *(int *)(s + 88) = 3072;
        {
            int v = *(int *)(s + 80);
            if (gEwram_02003670[0x11ae] & 4) {
                if (v > 0x77ff) { __asm__ volatile(""); goto tail; }
            } else if (v > 0x6fff) {
                goto tail;
            }
        }
        *(int *)(s + 80) = (gEwram_02003670[0x11ae] & 4) ? 0x7800 : 0x7000;
        s[13]++;
        s[18] = 60;
        goto tail;
    c2: {
        if (s[18] > 51) {
            u8 *base = gEwram_02003670;
            u16 pos = (base[0x11ae] & 4) ? 0x7800 : 0x7000;
            if (s[18] != 52) {
                unsigned fx = (s[18] - 52) << 15;
                u16 half = fx >> 16;
                int sc = Sub_080052A0(fx);
                u16 d = half + (sc & 3);
                u32 gw = *(u32 *)base;
                int sd, spos;
                if (gw & 1)
                    d = 0;
                else
                    d = (gw & mode) ? d : -d;
                sd = (s16)d << 8;
                spos = (s16)pos;
                __asm__ volatile("" : "+r"(sd), "+r"(spos));
                pos = (u16)(spos + sd);
            }
            *(int *)(s + 80) = (s16)pos;
        }
        if (--s[18] != 0)
            goto tail;
        s[13]++;
        *(int *)(s + 88) = 512;
        *(int *)(s + 96) = 96;
        goto tail;
    }
    c3:
        *(int *)(s + 80) -= *(int *)(s + 88);
        *(int *)(s + 88) += *(int *)(s + 96);
        if (*(int *)(s + 80) < -20480) {
            u32 **tbl = (u32 **)Tbl_082243D8;
            u32 **row = tbl + s[9];
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = (*row)[2];
        }
        goto tail;
    } else {
        {
            register u8 *o __asm__("r1") = other;
            if (s[18] != 0) {
                s[18]--;
                goto tail;
            }
            if ((u8)Byte12_Gt1_080170c4(o)) {
            u32 **tbl = (u32 **)Tbl_082243D8;
            u32 **row = tbl + s[9];
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = (*row)[2];
        }
        {
            int cur = *(int *)(s + 80);
            int tgt = *(int *)(other + 80);
            int d = cur - tgt;
            if (d >= 0) {
                if (d <= 256)
                    goto snap;
                goto step;
            } else if (tgt - cur > 256) {
                goto step;
            }
        snap:
            *(int *)(s + 80) = tgt;
            goto tail;
        step: {
            int tt = (short)tgt;
            short st;
            short st2;
            __asm__ volatile("" : "+r"(tt));
            st = (short)(tt - cur) >> 1;
            st2 = st ? st : 1;
            *(int *)(s + 80) = cur + st2;
            goto tail;
        }
        }
        }
    }
tail:
    ChipSlot_Tick(s);
}

__asm__(".set Sub_080052A0, 0x080052a0");
__asm__(".set gEwram_02003670, 0x02003670");
__asm__(".set Tbl_082243D8, 0x082243d8");

__asm__(".hword 0");
