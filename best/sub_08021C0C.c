void *sub_08021C0C(u32 arg0) {
    u32 shift_tmp = (u32)arg0 << 24;
    u8 *g = (u8 *)0x08173760;
    u8 *base = *(u8 **)(g + 0x6C);
    u8 *ptr = base + *(u32 *)(base + 0x44) + 0x44;
    u8 *t1 = ptr + 0x0C;
    u32 t2 = *(u32 *)(ptr + 0x0C);
    u32 t3 = (u32)t1 + t2;
    u32 shift = shift_tmp >> 19;
    return (void *)(t3 + shift);
}

extern void QueueResourceTransfer(void *, u32);
extern void sub_0800288C(void *, u32);

void sub_0802366C(void) {
    u8 *g = (u8 *)0x08173760;
    u8 *base = *(u8 **)(g + 0x2C);
    u32 off = *(u32 *)(base + 0x10) + 0x10;
    u8 *ptr = base + off;
    QueueResourceTransfer(ptr, (*(u16 *)(&ptr[-0xC] + 0x978) << 5) + 0x10000);
    sub_0800288C(ptr + 0x0C, (*(u16 *)(&ptr[-0xC] + 0x9F2) << 5) + 0x200);
}

extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);

u8 *sub_080236B0(u32 a, u8 *b, u8 *c, u8 *d) {
    u8 *cc = c;
    u8 *dd = d;
    u8 *bb = b;
    u8 aa = (u8)a;
    u8 nib;
    u32 w35;
    u8 *p;
    w35 = cc[35];
    nib = (w35 << 28) >> 28;
    p = (u8 *)sub_08020ED4(0, 1, nib, 7);
    if (p != 0) {
        u8 z = 0;
        u32 dw0;
        u32 dw1;
        p[16] = z;
        p[17] = aa;
        dw0 = *(u32 *)dd;
        dw1 = *(u32 *)(dd + 4);
        *(u32 *)(p + 0x60) = dw0;
        *(u32 *)(p + 0x64) = dw1;
        *(u32 *)(p + 0x28) = (u32)bb;
        *(u32 *)(p + 0x2C) = (u32)cc;
    }
    return p;
}
