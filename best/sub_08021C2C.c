extern void sub_08002300(u8 *p, int v);
extern void sub_08002904(u8 *p, int a, u8 b);
extern u32 D_08173760[];
extern u16 D_08227104[];
extern u16 D_08227114[];
extern u16 D_0817386C[];
extern u8 D_081738F2[];

void sub_08021C2C(void)
{
    short i = 0;
    u32 *t2 = D_08173760;
    u16 *t1 = D_08227104;

    do {
        u32 idx = i * 2;
        u16 *ep = (u16 *)(idx + (u32)t1);
        u16 v = *ep;
        u32 bv = t2[v];
        u32 tmp;
        u8 *q;

        tmp = (u32)D_08227114;
        idx += tmp;
        idx = *(u16 *)idx;
        tmp = idx << 2;
        q = (u8 *)(bv + tmp);
        q = (u8 *)((u32)q + *(u32 *)q);
        sub_08002300(q, (D_0817386C[v] << 5) + 0x10000);
        q += 12;
        sub_08002904(q, 0, D_081738F2[(*ep) * 2]);
        i++;
    } while (i <= 7);
}
