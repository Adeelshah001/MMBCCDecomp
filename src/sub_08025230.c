typedef struct {
    u8 *p;
    u16 a;
    u16 b;
} Buf;

void sub_0802520C(Buf *s, u8 *ptr, u16 n) {
    s->p = ptr;
    s->a = n;
    s->b = 0;
    while (n != 0) {
        *ptr++ = 0xFF;
        n--;
    }
}

void sub_08025230(Buf *s, u8 *ptr, u16 n) {
    u16 i;
    s->p = ptr;
    s->a = n;
    s->b = 0;
    i = 0;
    if (i < n && ptr[i] != 0xFF) {
        do {
            s->b++;
            i++;
        } while (i < n && ptr[i] != 0xFF);
    }
}

u8 sub_080251B8(u8 *p);
u8 sub_08025730(u8 *p, u8 v);

u8 sub_080251D8(u8 *p) {
    u8 v = p[0xD8 << 1];
    u8 w = sub_08025730(p + v * 144, 0);
    if (w == 0)
        w = sub_080251B8(p);
    return w;
}

int sub_0802526C(Buf *s, u8 v) {
    if (s->b >= s->a)
        return 1;
    s->p[s->b] = v;
    s->b++;
    return 0;
}
