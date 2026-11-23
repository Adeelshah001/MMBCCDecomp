typedef signed short s16;

struct Buf {
    u8 *p;
    u16 a;
    u16 b;
};

struct Header26184 {
    u8 pad00[0x0E];
    u16 unk0E;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u8 unk18;
    u8 unk19;
};

struct State26184 {
    u8 *base;
    struct Header26184 *hdr;
    struct Buf buf1;
    struct Buf buf2;
};

extern void sub_0802520C(struct Buf *s, u8 *ptr, u16 n);
extern int sub_0802526C(struct Buf *s, u8 v);

void sub_08026184(struct State26184 *s, u16 *vals)
{
    s16 i;

    sub_0802520C(&s->buf1, s->base + 0xE00, 0x82);
    sub_0802520C(&s->buf2, s->base + 0xE82, 0x82);
    sub_0802526C(&s->buf2, 0);

    s->hdr->unk0E = vals[0];
    s->hdr->unk10 = vals[1];
    s->hdr->unk12 = vals[2];
    s->hdr->unk14 = vals[3];
    s->hdr->unk16 = 0x8000;
    s->hdr->unk18 = 1;
    s->hdr->unk19 = 1;

    for (i = 1; i < 128; i++)
        sub_0802526C(&s->buf1, i);
}
