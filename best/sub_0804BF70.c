static inline unsigned int ReadSequenceArgument(u8 *track)
{
    const u8 **cursor = (const u8 **)(track + 0x40);
    const u8 *source = (*cursor)++;
    unsigned int value = *source;
    if ((u32)source < 0x02000000)
        value = 0;
    return value;
}

void sub_0804BF84(void *player, u8 *track)
{
    track[0x1B] = ReadSequenceArgument(track);
}

void sub_0804BF90(void *player, u8 *track)
{
    unsigned int type = ReadSequenceArgument(track);
    if (type != track[0x18]) {
        track[0x18] = type;
        track[0] |= 0x0F;
    }
}

void sub_0804BF70(void *player, u8 *track)
{
    track[0x0F] = ReadSequenceArgument(track);
    track[0] |= 0x0C;
}

void sub_0804BFA8(void *player, u8 *track)
{
    track[0x0C] = ReadSequenceArgument(track) - 0x40;
    track[0] |= 0x0C;
}
