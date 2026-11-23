struct Obj {
    u8 f0;
    u8 f1;
    u8 pad2[2];
    u16 f4;
    u16 f6;
    u16 f8;
    u16 f10;
};

struct S {
    struct Obj *arr[6];
    u32 f24;
};

extern u16 sub_0802458C(u8 x);
extern u16 sub_08024570(u8 x);
extern u8 sub_080245FC(u8 x);
extern u8 sub_0803FB9C(u16 x);

void sub_0802D670(struct S *s)
{
    u8 i;

    s->arr[0] = 0;
    s->arr[1] = 0;
    s->f24 = 0;
    for (i = 2; i <= 5; i++) {
        if (s->arr[i] != 0) {
            s->arr[i]->f4 = sub_0802458C(s->arr[i]->f0);
            s->arr[i]->f6 = sub_08024570(s->arr[i]->f0);
            s->arr[i]->f1 = sub_080245FC(s->arr[i]->f0);
            if (i == 2) {
                int m = 0x80;
                s->arr[2]->f10 = m & s->arr[2]->f10;
            } else if (sub_0803FB9C(s->arr[i]->f8) == 0) {
                s->arr[i]->f10 = 0;
            }
        }
    }
}
