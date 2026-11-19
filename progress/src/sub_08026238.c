/* sub_08026238 @ 0x08026238 (322 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w68a_08026238_MATCHED.c (registry: src/w68a_08026238_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 F_08023AEC(u8 *key, u8 *buf);

u8 sub_080263A4(u8 *buf);

u8 GetBoundedByte_080252D0(u8 *p, u16 i);

u8 Buf_RemoveAt_25290(u8 *p, u16 v);

void Append_0802526C(u8 *p, u8 v);

u8 Cmp8(u8 *a, u8 *b);

u8 Clamp_26720(u8 v);

__attribute__((section(".text.w68a_08026238")))
u16 sub_08026238(u8 *q, u8 *key)
{
    u8 buf[16];
    u16 i;
    u8 idx;

    q[24] = 0;
    q[25] = 0;
    if (F_08023AEC(key, buf) != 0) {
        q[24] = 3;
        return 0;
    }
    if (sub_080263A4(buf) != 0) {
        q[24] = 3;
        return 0;
    }
    for (i = 0; i < *(u16 *)(q + 22); i++) {
        u8 *elem;
        u8 *bs;
        idx = GetBoundedByte_080252D0(q + 16, i);
        bs = *(u8 **)(q + 4);
        elem = (u8 *)(idx * 28) + (u32)bs;
        if (elem[24] != buf[13])
            continue;
        if (Cmp8(key, elem + 14) != 0)
            continue;
        if (idx == 0) {
            q[24] = 1;
            q[25] = idx;
        } else {
            q[24] = 2;
            q[25] = i;
        }
        return 0;
    }
    if (*(u16 *)(q + 22) > 127) {
        q[24] = 4;
        return 0;
    }
    idx = Buf_RemoveAt_25290(q + 8, *(u16 *)(q + 14) - 1);
    Append_0802526C(q + 16, idx);
    {
        u8 *elem;
        u16 hv;
        elem = *(u8 **)(q + 4) + idx * 28;
    elem[0] = buf[0];
    elem[1] = Clamp_26720(buf[0]);
    elem[2] = buf[1];
    elem[3] = buf[2];
    elem[4] = buf[3];
    elem[5] = buf[4];
    elem[6] = buf[5];
    elem[7] = buf[6];
    elem[8] = buf[7];
    elem[9] = buf[8];
    elem[10] = buf[9];
    elem[11] = buf[10];
    elem[12] = buf[11];
    elem[13] = buf[12];
    *(u16 *)(elem + 14) = *(u16 *)(key + 0);
    *(u16 *)(elem + 16) = *(u16 *)(key + 2);
    *(u16 *)(elem + 18) = *(u16 *)(key + 4);
    *(u16 *)(elem + 20) = *(u16 *)(key + 6);
    hv = 0x8000;
    *(u16 *)(elem + 22) = hv;
    elem[24] = buf[13];
    elem[25] = 1;
    return idx | 0x2000;
    }
}
