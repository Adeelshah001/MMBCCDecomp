struct S_F9A4 {
    u8 pad0[9];
    u8 f9;
    u8 pad10[2];
    u32 f12;
    u8 pad16[4];
    u32 f20;
    u8 pad24[16];
    u32 f28;
    u32 f2C;
    u8 pad48[71];
    u8 f77;
};

extern void sub_0800D9FC(void *s);
extern int sub_0801F1D8(u8 *q);
extern u32 *D_082243D8[];

void sub_0801F9A4(struct S_F9A4 *s)
{
    u8 v;
    u8 *q;
    u8 *p2;
    u32 *entry;
    
    v = s->f77 - 3;
    if (v <= 1) {
        q = (u8 *)s->f28;
        if ((u8)sub_0801F1D8(q) == 0) {
            p2 = (u8 *)s->f2C;
            p2[0]++;
        }
        {
            u32 **table = D_082243D8;
            entry = &table[s->f9];
        }
        s->f12 = 2;
        s->f20 = ((u32 *)*entry)[2];
    }
    sub_0800D9FC(s);
}
