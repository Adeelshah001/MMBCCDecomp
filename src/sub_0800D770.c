struct UnkVec {
    u8 _00[35];
    u8 flip;
    u8 _36[44];
    int x;
    int y;
};

struct UnkPair {
    int a;
    int b;
};

void *sub_0800DD08(struct UnkPair *dst, struct UnkVec *src) {
    int val = src->x;
    if (src->flip & 0x80) {
        val = -val;
    }
    dst->a = val;
    dst->b = src->y;
    return dst;
}

void sub_0800DD4C(struct UnkVec *o, int x, int y) {
    if (o->flip & 0x80) {
        x = -x;
    }
    o->x += x;
    o->y += y;
}

void sub_0800DB40(u8 *p) {
    s8 *q = (s8 *)(p + 33);
    s8 c = q[0];
    int v;
    if (c != 0) {
        v = 14;
        q[0] = c - 1;
    } else {
        v = p[31] & 0x0F;
    }
    p += 69;
    v <<= 4;
    *p = (u8)((*p & 0x0F) | v);
}

extern void sub_0800D800(u8 *s, int one, u16 b, u8 c, int zero);

void sub_0800D770(u8 *s, int b, int c) {
    u16 bb = b;
    u8 cc = c;
    sub_0800D800(s, 0, bb, cc, 1);
}
