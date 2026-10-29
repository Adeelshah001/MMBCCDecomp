/* Wave 68-A: 0x08026238, fresh. True (tiling) extent 324 B
 * (322 code through bx @0x26378 + 2 pad bytes to next fn @0x2637C).
 * Find-or-append a 28-byte record (sibling of landed 0x08026430):
 *   q[24]=q[25]=0; if (Validate_23AEC(key, buf)) { q[24]=3; return 0; }
 *   if (Validate_263A4(buf)) { q[24]=3; return 0; }
 *   for (i = 0; i < *(u16 *)(q+22); i++):
 *     idx = GetIdx_252D0(q+16, i); elem = base + idx*28;
 *     if (elem[24] != buf[13]) continue;
 *     if (Cmp_2637C(key, elem+14)) continue;
 *     if (idx == 0) { q[24]=1; q[25]=idx; } else { q[24]=2; q[25]=i; }
 *     return 0;
 *   if (*(u16 *)(q+22) > 127) { q[24]=4; return 0; }
 *   idx = BufRemove_25290(q+8, *(u16 *)(q+14)-1); Append_2526C(q+16, idx);
 *   ent = base + idx*28; ent[0]=buf[0]; ent[1]=Clamp_26720(buf[0]);
 *   ent[2..13]=buf[1..12]; ent u16[14,16,18,20]=key u16[0,2,4,6];
 *   *(u16 *)(ent+22)=0x8000; ent[24]=buf[13]; ent[25]=1;
 *   return idx | 0x2000;
 * Techniques (all plain C except the noted idiom, no r7 pin, no asm):
 *   (a) loop add as pointer-offset form elem = (u8 *)(idx*28) + (u32)bs
 *       with bs loaded first -> ROM's ldr r1 / lsls / adds r1,r0,r1;
 *   (b) plain u16 variable hv assigned inline just before the tail store
 *       -> ROM's movs r0,#128; lsls r0,#8; strh (sibling 26430 idiom);
 *   (c) trailing __asm__(".balign 4, 0") -> the ROM's 00 00 padding.
 * Arg2 of the caller (w34c 24FBC) is unused by this function.
 * .set stubs for ALL callees are verification-only; coordinator strips
 * landed-callee stubs at landing. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

u8 F_08023AEC(u8 *key, u8 *buf);
u8 F_080263A4(u8 *buf);
u8 F_080252D0(u8 *p, u16 i);
u8 F_08025290(u8 *p, u16 v);
void F_0802526C(u8 *p, u8 v);
u8 F_0802637C(u8 *a, u8 *b);
u8 F_08026720(u8 v);

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
    if (F_080263A4(buf) != 0) {
        q[24] = 3;
        return 0;
    }
    for (i = 0; i < *(u16 *)(q + 22); i++) {
        u8 *elem;
        u8 *bs;
        idx = F_080252D0(q + 16, i);
        bs = *(u8 **)(q + 4);
        elem = (u8 *)(idx * 28) + (u32)bs;
        if (elem[24] != buf[13])
            continue;
        if (F_0802637C(key, elem + 14) != 0)
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
    idx = F_08025290(q + 8, *(u16 *)(q + 14) - 1);
    F_0802526C(q + 16, idx);
    {
        u8 *elem;
        u16 hv;
        elem = *(u8 **)(q + 4) + idx * 28;
    elem[0] = buf[0];
    elem[1] = F_08026720(buf[0]);
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
__asm__(".balign 4, 0");
__asm__(
    ".globl F_08023AEC\n.set F_08023AEC, 0x08023AEC\n"
    ".globl F_080263A4\n.set F_080263A4, 0x080263A4\n"
    ".globl F_080252D0\n.set F_080252D0, 0x080252D0\n"
    ".globl F_08025290\n.set F_08025290, 0x08025290\n"
    ".globl F_0802526C\n.set F_0802526C, 0x0802526C\n"
    ".globl F_0802637C\n.set F_0802637C, 0x0802637C\n"
    ".globl F_08026720\n.set F_08026720, 0x08026720\n"
);
