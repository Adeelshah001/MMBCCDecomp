typedef struct {
    u8 pad0[9];
    u8 kind;
    u8 flags;
    u8 padB;
    u32 phase;
    u8 pad10[2];
    u8 delay;
    u8 pad13;
    const void *script;
    u8 pad18[10];
    u8 tileOffset;
    u8 pad23[34];
    u8 drawFlags;
} Actor;

typedef void (*ActorCallback)(Actor *);
extern void sub_0804DCD0(Actor *, ActorCallback);
extern ActorCallback const D_08223CF0[];
extern const void *const *D_082243D8[];
extern const u16 D_081705B0[];
extern u8 D_020031E4[][2];

u32 sub_080170C4(const u8 *actor)
{
    return actor[12] > 1 ? 1 : 0;
}

void sub_080173FC(Actor *actor);

void sub_080173D4(Actor *actor)
{
    u32 base = (u32)D_082243D8;
    u8 kind = *(volatile u8 *)&actor->kind;
    const void *const **slot = (const void *const **)((kind << 2) + base);
    actor->phase = 1;
    actor->script = (*slot)[1];
    {
        u32 mask = 0xFE;
        mask &= *(volatile u8 *)&actor->flags;
        actor->flags = mask;
    }
    sub_080173FC(actor);
}

void sub_08016DAC(Actor *actor)
{
    u8 *bytes = (u8 *)actor;
    u32 base = (u32)D_08223CF0;
    u32 index = ((volatile u8 *)bytes)[13] << 2;
    int level;
    int mask;
    u8 *entry;
    u32 shifted;
    u8 *flags;

    sub_0804DCD0(actor, *(ActorCallback *)(index + base));
    entry = &D_020031E4[D_081705B0[0] >> 4][0];
    level = 3;
    level &= *(volatile u8 *)entry;
    if (level > 3)
        level = 3;
    flags = &actor->drawFlags;
    shifted = (u32)level << 2;
    mask = 13;
    mask = -mask;
    *flags = (mask & *(volatile u8 *)flags) | shifted;
    actor->tileOffset = 16;
}

void sub_080173FC(Actor *actor)
{
    if (!actor->delay) {
        u32 base = (u32)D_082243D8;
        u8 kind = *(volatile u8 *)&actor->kind;
        const void *const **slot = (const void *const **)((kind << 2) + base);
        actor->phase = 2;
        actor->script = (*slot)[2];
    }
}
