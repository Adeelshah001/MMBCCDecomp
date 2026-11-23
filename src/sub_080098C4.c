struct Rect {
    short x;
    short y;
    short w;
    short h;
};

extern const u8 D_0830B778[];
extern void sub_080024BC(const void *, u32, struct Rect *);

void sub_080098C4(u8 ch, u16 tileBase, u8 col, u8 row)
{
    const u8 *base = D_0830B778;
    struct Rect rect;
    rect.x = ch & 0x1F;
    rect.y = (ch >> 5) * 2;
    rect.w = 1;
    rect.h = 2;
    sub_080024BC(base, ((tileBase + col + (row << 5)) << 5) + 0x10000, &rect);
}
