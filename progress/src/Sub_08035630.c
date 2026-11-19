/* Sub_08035630 @ 0x08035630 (520 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w126a_08035630_MATCHED.c (registry: src/w126a_08035630_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 table_0822ea88[];

extern u16 gEwram_02002F50[];

void Task_35BC8(u8 *s);

void Task_35DA4(u8 *s);

void Text_SelectBlobIdx(int x);

void sub_08035AFC(u8 *s);

void Sub_08035C5C(u8 *s);

__attribute__((section(".text.w126a_08035630")))
int Sub_08035630(u8 *s)
{
    int key = 0;
    int ret = 0;
    u8 max = table_0822ea88[s[20]];
    /* kp is gEwram_02002F50 (extern array, .set below) */

    if ((gEwram_02002F50[0] & 0x20) != 0) {
        if ((gEwram_02002F50[3] & 0x20) != 0)
            key = 0x20;
    }
    if ((gEwram_02002F50[0] & 0x10) != 0) {
        if ((gEwram_02002F50[3] & 0x10) != 0)
            key = 0x10;
    }
    if ((gEwram_02002F50[0] & 0x40) != 0) {
        if ((gEwram_02002F50[2] & 0x40) != 0)
            key = 0x40;
    }
    if ((gEwram_02002F50[0] & 0x80) != 0) {
        if ((gEwram_02002F50[2] & 0x80) != 0)
            key = 0x80;
    }
    if ((gEwram_02002F50[0] & 0x02) != 0) {
        if ((gEwram_02002F50[2] & 0x02) != 0)
            key = 0x02;
    }
    if ((gEwram_02002F50[0] & 0x08) != 0) {
        if ((gEwram_02002F50[2] & 0x08) != 0)
            key = 0x08;
    }
    if ((gEwram_02002F50[0] & 0x100) != 0) {
        if ((gEwram_02002F50[2] & 0x100) != 0)
            key = 0x100;
    }

    switch (key) {
    case 64:
    case 128:
        if (max > 12) {
            if ((s8)s[0x46aa] > 12) {
                if ((s8)(s[0x46aa] -= 13) < 0)
                    s[0x46aa] = 0;
            } else {
                s[0x46aa] += 13;
                if ((s8)s[0x46aa] > max - 1)
                    s[0x46aa] = max - 1;
            }
            Task_35BC8(s);
        }
        break;
    case 32:
        if ((s8)--s[0x46aa] < 0)
            s[0x46aa] = max - 1;
        Task_35BC8(s);
        break;
    case 16:
        s[0x46aa]++;
        if ((s8)s[0x46aa] >= max) {
            s[0x46aa] = max - 1;
            Task_35DA4(s);
            s[0x46ac] = 28;
            Text_SelectBlobIdx(0x77);
            sub_08035AFC(s);
            Sub_08035C5C(s);
        } else {
            Task_35BC8(s);
        }
        break;
    case 2: {
        u8 *p = s + 0x46a8;
        u8 z = 0;
        *p = 3;
        s[0x46a9] = z;
        Text_SelectBlobIdx(0x67);
        ret = 1;
        break;
    }
    case 8:
        s[0x46a8] = 0;
        s[0x46a9] = 0;
        Text_SelectBlobIdx(0x67);
        ret = 1;
        break;
    case 256:
        Task_35DA4(s);
        s[0x46ac] = 28;
        Text_SelectBlobIdx(0x77);
        sub_08035AFC(s);
        Sub_08035C5C(s);
        break;
    default:
        break;
    }
    return ret;
}
