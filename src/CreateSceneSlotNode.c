struct SceneNode {
    u8 pad0[9];
    u8 resourceIndex;
    u8 padA[10];
    u32 resource;
    u8 pad18[11];
    u8 slot:4;
    u8 group:3;
    u8 enabled:1;
};

extern void *D_02005270;
extern struct SceneNode *D_02005020[];
extern const u32 *const D_08223CC0[];
extern struct SceneNode *sub_08004424(void *);

struct SceneNode *CreateSceneSlotNode(u8 group, u8 slot, u8 resource)
{
    struct SceneNode *node = sub_08004424(D_02005270);
    if (node != 0) {
        const u32 *const *table;
        struct SceneNode **slots;

        u8 *packed = (u8 *)node;
        u8 groupBits;
        int mask;
        int slotMask;
        u8 slotBits;

        packed += 0x23;
        groupBits = (group & 7) << 4;
        mask = ~0x70;
        mask &= *packed;
        mask |= groupBits;
        slotBits = slot & 0xF;
        slotMask = ~0x0F;
        mask &= slotMask;
        mask |= slotBits;
        *packed = mask;
        if (slot == 0)
            node->enabled = 0;
        else
            node->enabled = 1;
        table = D_08223CC0;
        node->resourceIndex = resource;
        node->resource = *table[resource];
        slots = D_02005020;
        slots[slot] = node;
    }
    return node;
}
