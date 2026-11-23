// sub_080174D4
struct S_74D4 {
    u8 pad[0x78];
    short val;
};

short sub_080174D4(struct S_74D4 *s)
{
    return s->val;
}

// sub_080174B4
void sub_080174B4(u8 *s, u8 bit)
{
    s[16] &= ~(1 << bit);
}
