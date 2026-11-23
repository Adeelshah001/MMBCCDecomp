struct Point30C4 {
    int x, y;
};

struct PointPair30C4 {
    const struct Point30C4 *first;
    const struct Point30C4 *second;
};

struct Offset30C4 {
    u8 unused[8];
    short x, y;
};

void sub_080030C4(struct Point30C4 *out,
                  const struct PointPair30C4 *points,
                  const struct Offset30C4 *offset)
{
    short x, y;
    if (offset != 0) {
        x = offset->x;
        y = offset->y;
    } else {
        x = 0;
        y = 0;
    }

    if (points != 0) {
        const struct Point30C4 *first = points->first;
        const struct Point30C4 *second;
        int firstX, sum, origin;

        out[0].x = first->x;
        out[0].y = first->y;
        firstX = first->x >> 8;
        second = points->second;
        sum = firstX + (second->x >> 8);
        origin = x + 120;
        sum -= origin;
        sum = (u32)sum << 8;
        out[1].x = sum;
        sum = (first->y >> 8) + (second->y >> 8);
        origin = y + 80;
        sum -= origin;
        sum = (u32)sum << 8;
        out[1].y = sum;
        out[2].x = second->x;
        out[2].y = second->y;
    } else {
        out[0].y = 0;
        out[0].x = 0;
        out[1].y = 0;
        out[1].x = 0;
        out[2].y = 0;
        out[2].x = 0;
    }
}
