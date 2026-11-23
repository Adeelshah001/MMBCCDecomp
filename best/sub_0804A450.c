struct Struct2EE0 {
    u8 flags;
    u8 pad01;
    volatile u16 unk02;
};

extern u8 D_0200BD20[];
extern struct Struct2EE0 D_02002EE0;

void sub_0804A450(void)
{
    u8 *a = D_0200BD20;
    struct Struct2EE0 *b = &D_02002EE0;
    int m = 1;

    m &= b->flags;
    if (m != 0) {
        a += 0x7C;
        if (*(short *)a != 0) {
            (*(short *)a)--;
            if (*(short *)a == 8) {
                b->unk02 &= 0xFFFD;
            }
        }
    }
}
