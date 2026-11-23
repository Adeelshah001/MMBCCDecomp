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
    int y = src->y;
    if (src->flip & 0x80) {
        val = -val;
    }
    dst->a = val;
    dst->b = y;
    return dst;
}

void sub_0800DD4C(struct UnkVec *o, int x, int y) {
    struct UnkVec *obj = o;
    if (obj->flip & 0x80) {
        x = -x;
    }
    obj->x += x;
    obj->y += y;
}

void sub_0800DB40(u8 *p) {
    s8 c = *(s8 *)(p + 33);
    int v;
    if (c != 0) {
        v = 14;
        *(s8 *)(p + 33) = c - 1;
    } else {
        v = p[31] & 0x0F;
    }
    p += 69;
    v <<= 4;
    *p = (u8)((*p & 0x0F) | v);
}
