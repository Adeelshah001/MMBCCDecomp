/* Wave 6 L1 batch (coordinator-verified).
   Evidence: docs/match_notes_wave6_l1.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08038AD4: Task_38AD4 (coordinator-verified). */
/* MMBCCDecomp — Wave 6 batch L1 worker scratch.
 * 0x08038AD4 (306 B): bit-test priority ladder on EWRAM 0x02002F50,
 * Text_SelectBlobIdx dispatch, EWRAM 0x02002F50 setup. Tentative name.
 * Attempt B: branchless idiom f2, scoped g, <= lim form.
 */


extern void Text_SelectBlobIdx(u16 idx);
extern u8 gEwram_02002F50[];
extern u8 gEwram_02004CE0[];

__attribute__((section(".text.w6l1_38ad4")))
u8 Task_38AD4(u8 *p)
{
    u8 ret = 0;
    u8 v = 0;
    {
        register u16 *g __asm__("r1") = (u16 *)gEwram_02002F50;
        register u16 w1 __asm__("r3");
        w1 = g[0];

        if ((0x40 & w1) != 0) {
            u16 w2 = g[3];
            v = (0x40 & w2) ? 0x40 : 0;
        }
        if ((0x80 & w1) != 0) {
            u16 w2 = g[3];
            if ((0x80 & w2) != 0)
                v = 0x80;
        }
        w1 = g[0];
        if ((1 & w1) != 0) {
            u16 w2 = g[2];
            if ((1 & w2) != 0)
                v = 1;
        }
        w1 = g[0];
        if ((2 & w1) != 0) {
            u16 w2 = g[2];
            if ((2 & w2) != 0)
                v = 2;
        }
    }

    switch (v) {
    case 0x40:
        if (p[0x4698] != 0) {
            Text_SelectBlobIdx(0x66);
            p[0x4698]--;
            ret = 1;
        }
        break;
    case 0x80: {
        u8 lim = 0;
        u8 x = p[20];
        if (x <= 8)
            goto t1;
        lim = 3;
        goto limdone;
      t1:
        if (x <= 5)
            goto t2;
        lim = 2;
        goto limdone;
      t2:
        if (x <= 1)
            goto limdone;
        lim = 1;
      limdone:
        if (p[0x4698] < lim) {
            Text_SelectBlobIdx(0x66);
            p[0x4698]++;
            ret = 1;
        }
        break;
    }
    case 1: {
        u8 z;
        ret = 2;
        Text_SelectBlobIdx(0x67);
        {
            u8 *addr = p + 0x469c;
            z = 0;
            *addr = v;
        }
        p[0x469d] = z;
        {
            u8 t = p[0x4698];
            p[0x4699] = t;
        }
        break;
    }
    case 2:
        Text_SelectBlobIdx(0x68);
        ret = 3;
        break;
    }

    {
        u16 *g = (u16 *)gEwram_02004CE0;
        g[0x14] = 0x14;
        g[0x15] = (u16)((p[0x4698] << 4) + 8);
    }
    return ret;
}

__asm__(
    ".set gEwram_02002F50, 0x02002F50\n\t"
);
