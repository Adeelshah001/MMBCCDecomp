extern u8 gUnknown_0804BA05[];
extern u8 gUnknown_03000000[];
extern u8 gUnknown_00000007[];
extern void sub_0804DB28(u32 a, u32 b, u32 c);
extern void sub_0804CA30(u32 a);
extern void sub_0804C8EC(u32 a);
extern void sub_0804CBCC(u32 a);
extern void sub_0804CD70(u32 a, u32 b, u32 c);

typedef struct
{
    u32 f0;
    u32 f4;
    u8 f8;
    u8 f9;
    u16 f10;
} Ent;

void sub_0804C630(void)
{
    int i;
    Ent *t;

    sub_0804DB28(((u32)gUnknown_0804BA05) & (~1), (u32)gUnknown_03000000, 0x04000100);
    sub_0804CA30(0x0200BDD0);
    sub_0804C8EC(0x0200CE10);
    sub_0804CBCC(0x0095FA00);

    for (i = 0; i < (u16)(u32)gUnknown_00000007; i++) {
        u32 f0;
        t = &((Ent *)0x08106D7C)[i];
        f0 = t->f0;
        sub_0804CD70(f0, t->f4, t->f8);
        *(u8 *)(f0 + 11) = t->f10;
        *(u32 *)(f0 + 24) = 0x0200D090;
    }
}
