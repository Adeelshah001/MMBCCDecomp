typedef short s16;

struct Entry08322B80 {
    u8 unk00[0x14];
};

struct Sub23C {
    u32 unk00;
    u32 unk04;
};

struct State02003670 {
    u8 unk000[0x23C];
    struct Sub23C unk23C;
};

struct State02004F40 {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    struct Entry08322B80 *unk0C;
};

typedef void (*CallbackFn)(struct State02004F40 *, u32, int);

extern struct State02003670 D_02003670;
extern struct State02004F40 D_02004F40;
extern struct Entry08322B80 D_08322B80[];
extern const s8 D_0817313C[];
extern const CallbackFn D_08173180[];

extern s8 sub_0800C248(s16);
extern void sub_08005268(struct Entry08322B80 *, u32);

void sub_0800C41C(s16 arg0)
{
    struct State02003670 *s = &D_02003670;
    struct Sub23C *sub;
    s8 idx;

    idx = sub_0800C248(arg0);
    sub = &s->unk23C;
    if (idx >= 0) {
        u32 dst = sub->unk04 + 0xFA000A20;
        struct Entry08322B80 *entry = &D_08322B80[idx];
        sub_08005268(entry, dst);
        D_02004F40.unk0C = entry;
    }
    D_08173180[D_0817313C[arg0]](&D_02004F40, sub->unk00, 0x51);
}
