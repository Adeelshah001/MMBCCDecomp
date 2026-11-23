struct Rect {
    short x;
    short y;
    short w;
    short h;
};

extern const u8 D_0830B764[];
extern void sub_080024BC(const void *, u32, struct Rect *);

void sub_08009994(u8 ch, u16 tileBase, u8 col, u8 row)
{
    register const u8 *base = D_0830B764;
    struct Rect rect;
    rect.x = ch & 0x1F;
    rect.y = ch >> 5;
    rect.w = 1;
    rect.h = 1;
    sub_080024BC(base, ((tileBase + col + (row << 5)) << 5) + 0x10000, &rect);
}
