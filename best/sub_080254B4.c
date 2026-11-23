u8 sub_08025478(void *s, u16 idx)
{
    u16 lim = *(u16 *)((u8 *)s + 18);
    return idx < lim ? (*(u8 **)((u8 *)s + 8))[idx] : 0;
}

void sub_08025290(u8 *p, u8 i);

void sub_080254B4(u8 *p, u8 i)
{
    u8 *q = *(u8 **)(p + 8) + i;
    u32 base = *(u32 *)(p + 4);
    u8 *r = (u8 *)(base + *q);
    if (--*r == 0)
        sub_08025290(p + 12, i);
}

extern void sub_0802533C(u8 *p, u8 idx);
extern void sub_080253BC(u8 *s);

void sub_0802541C(u8 *s, u8 *p, u16 n)
{
    u16 i;
    for (i = 0; i < n; i++) {
        u8 *s4;
        sub_0802533C(*(u8 **)s, p[i]);
        s4 = *(u8 **)(s + 4);
        s4 += p[i];
        ++*s4;
    }
    sub_080253BC(s);
}

extern void sub_0802526C(u8 *, u8);
extern u8 sub_08025324(u8 *, u8);

void sub_080254E0(u8 *s, u8 i)
{
    u8 *count = *(u8 **)(s + 4) + i;
    u8 limit = sub_08025324(*(u8 **)s, i);
    u32 value = *count;
    if (value != limit) {
        count = *(u8 **)(s + 4) + i;
        ++*count;
        if ((*(u8 **)(s + 4))[i] == 1)
            sub_0802526C(s + 12, i);
    }
}
