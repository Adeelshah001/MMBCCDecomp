extern u8 D_02002FB0[];

int QueueResourceTransfer(const void *resource, u32 destination)
{
    int i = 0;
    u8 *base = D_02002FB0;
    u32 count = *(u32 *)base;
    u8 *queue = base;
    u32 destField;
    u32 resourceField;
    u32 offset;
    int flags;

    if ((u32)i < count) {
        destField = (u32)(queue + 8);
        resourceField = (u32)(queue + 12);
    scan:
        if (*(const void **)resourceField == resource && *(u32 *)destField == destination)
            goto success;
        destField += 12;
        resourceField += 12;
        i++;
        if ((u32)i < count)
            goto scan;
    }

    if (*(u32 *)queue <= 15) {
        offset = 12 * (u32)i;
        base = queue + 8;
        *(u32 *)(offset + (u32)base) = destination;
        i = offset + (u32)queue;
        flags = -4;
        destField = ((u8 *)i)[4];
        flags &= destField;
        ((u8 *)i)[4] = flags;
        base = queue + 12;
        resourceField = offset + (u32)base;
        *(const void **)resourceField = resource;
        (*(u32 *)queue)++;
    } else {
        return -1;
    }

success:
    return 0;
}
