typedef signed short s16;
typedef signed int s32;

extern u8 gUnknown_030005C0[];
extern u32 D_02000800;
extern void sub_08000328(u32);

void sub_08000E80(u32 arg0) {
    u8 *r3 = gUnknown_030005C0;
    u32 r2 = 0x1E50;
    u32 *r1 = (u32 *)(r3 + r2);
    u32 idx = *r1;
    u32 r1_val = idx * 2;
    u8 *elem;
    r1_val += idx;
    r1_val <<= 3;
    r2 = 0x1E08;
    r3 += r2;
    elem = (u8 *)(r1_val + (u32)r3);
    elem[1] = 1;
    *(u32 *)(elem + 4) = arg0;
    sub_08000328(D_02000800);
}
