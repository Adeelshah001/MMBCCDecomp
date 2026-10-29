/* Wave 30-A: 0x0803ac4c - v7: old_agbcc, pins for r7 (o2, off), sed for push/pop.
 * B32: pa via immediate (proven ldr r5/adds r1); o2 pinned r7 defeats -3 fold.
 * B16: v4's off pin (proven ldr r7/adds r1/subs/adds r0 under old_agbcc).
 * r7 fixed by pins -> gcc won't push it -> harness sed-patches push/pop. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern u8 gEwram_02002F50[];
extern u8 gEwram_02004CE0[];
extern u8 gAddrZero[];
s16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w30a_0803ac4c")))
u32 Task_SelectBlobIdx_0803AC4C(u8 *p) {
    u32 ret = 0;
    u16 w;
    u8 *q;
    {
        u8 *hw = gEwram_02002F50;
        w = *(u16 *)(hw + 6);
    }
    {
        u32 m = 32;
        if ((m &= w) != 0) {
            u8 *tbl;
            u8 a, b, v;
            q = p + 0x469a;
            if (*q == 0)
                goto tbl32;
            (*q)--;
            __asm__ volatile("");
            goto snd;
          tbl32:
            tbl = &gAddrZero[0x8231790];
            a = p[0x469b];
            {
                register u32 o2 __asm__("r7") = 0x4698;
                u8 *pb = p + o2;
                b = *pb;
                v = tbl[a - b];
            }
            if (v == 1)
                goto hw4;
            *q = v - 1;
            goto snd;
        }
    }
    {
        u32 m = 16;
        if ((m &= w) == 0)
            goto hw4;
        {
            u8 *tbl;
            register u32 off __asm__("r7");
            u8 *pa, *pb;
            u8 t, a, b, v;
            q = p + 0x469a;
            t = *q;
            tbl = &gAddrZero[0x8231790];
            off = 0x469b;
            pa = p + off;
            off -= 3;
            pb = p + off;
            a = *pa;
            b = *pb;
            v = tbl[a - b];
            if (t < v - 1) {
                *q = t + 1;
            } else {
                if (v == 1)
                    goto hw4;
                *q = ret;
            }
        }
    }
  snd:
    Text_SelectBlobIdx(0x66);
    ret = 3;
  hw4: {
        u16 w2;
        {
            u8 *hw = gEwram_02002F50;
            w2 = *(u16 *)(hw + 4);
        }
        {
            u32 m = 1;
            if ((m &= w2) != 0) {
                Text_SelectBlobIdx(0x67);
                ret = 1;
                goto tail;
            }
        }
        {
            u32 m = 2;
            if ((m &= w2) != 0) {
                Text_SelectBlobIdx(0x68);
                ret = 2;
            }
        }
    }
  tail: {
        u16 *g = (u16 *)gEwram_02004CE0;
        g[20] = (u16)((p[0x469a] << 4) + 72);
        __asm__ volatile("" ::: "r2");
        g[21] = (u16)((p[0x4698] << 4) + 8);
    }
    return ret;
}

__asm__(".set gEwram_02002F50, 0x02002F50\n");
__asm__(".set gEwram_02004CE0, 0x02004CE0\n");
__asm__(".set gAddrZero, 0x0\n");
