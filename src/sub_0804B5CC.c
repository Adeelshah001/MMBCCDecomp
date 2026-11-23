struct State4B5CC {
    u8 pad0[2];
    u8 unk2;
    u8 unk3;
    u8 pad4[2];
    u16 unk6;
};

extern u8 D_03002420[];
extern const u8 D_082350A0[];
extern void sub_0800DDE4(u8 *a, const u8 *b, u8 *c, u8 d);

void sub_0804B5CC(struct State4B5CC *s)
{
    short i;
    int mask;

    switch (s->unk3) {
    case 0:
        s->unk3 = 1;
        s->unk6 = 32;
    case 1:
        mask = 3;
        mask &= s->unk6;
        if (mask == 0) {
            for (i = 0; i < 4; i++) {
                u8 *dst = &D_03002420[(i + 1) * 32];
                sub_0800DDE4(dst, D_082350A0, dst, 1);
            }
        }
        if (--s->unk6 == 0) {
            s->unk2++;
            s->unk3 = 0;
        }
        break;
    }
}
