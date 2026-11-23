extern const u32 *D_082243D8[];

void sub_0801AB74(u8 *actor)
{
    u32 mask = 254;
    u32 base;
    u8 kind;
    const u32 **slot;

    mask &= ((volatile u8 *)actor)[10];
    actor[10] = mask;
    base = (u32)D_082243D8;
    kind = ((volatile u8 *)actor)[9];
    slot = (const u32 **)(base + (kind << 2));
    *(u32 *)(actor + 12) = 4;
    *(u32 *)(actor + 20) = (*slot)[4];
}

u8 sub_08017494(const u8 *actor, u8 bit)
{
    return (1U << bit) & actor[16];
}

void sub_08017478(u8 *actor, u8 value)
{
    if (actor[17] < value)
        actor[17] = value;
}

void sub_08017464(u8 *actor)
{
    u8 delay = actor[18];
    if (delay)
        actor[18] = delay - 1;
}
