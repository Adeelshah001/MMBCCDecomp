struct Object {
    u8 reserved00[9];
    u8 kind;
    u8 reserved0A[10];
    const void *script;
    u8 reserved18[11];
    u8 flags;
};

struct ObjectPool;

extern struct ObjectPool *D_020066F0;
extern const void *const *const D_08226EF0[];
extern struct Object *sub_08004424(struct ObjectPool *);
extern struct Object *sub_08004454(struct ObjectPool *);

struct Object *sub_08020ED4(u8 atFront, u8 group, u8 slot, u8 kind)
{
    struct Object *object;

    if (atFront == 0)
        object = sub_08004424(D_020066F0);
    else
        object = sub_08004454(D_020066F0);

    if (object != 0) {
        u8 *flags = &object->flags;
        u32 groupBits = (group & 7) << 4;
        int value = -113;
        int slotBits;
        int slotMask;
        const void *const *const *scripts;

        value &= *flags;
        value |= groupBits;
        slotBits = slot & 15;
        slotMask = -16;
        value &= slotMask;
        value |= slotBits;
        *flags = value;
        if (slot == 0)
            *flags = value & 0x7F;
        else {
            int activeBit = 0x80;
            value |= activeBit;
            *flags = value;
        }

        scripts = D_08226EF0;
        object->kind = kind;
        object->script = *scripts[kind];
    }
    return object;
}
