struct SeqChannelC4 {
    u8 flags;
    u8 pad1[0x10];
    u8 key;
    u8 pad12[0x22];
    struct SeqChannelC4 *next;
};

struct SeqTrackC4 {
    u8 flags;
    u8 pad1[4];
    u8 key;
    u8 pad6[0x10];
    u8 modValue;
    u8 modDepth;
    u8 modType;
    u8 lfoSpeed;
    u8 lfoPhase;
    u8 pad1B[5];
    struct SeqChannelC4 *channels;
    u8 pad24[0x1C];
    const u8 *cursor;
};
void sub_0804C53C(void *player, struct SeqTrackC4 *track)
{
    unsigned int mask;
    track->modValue = 0;
    track->lfoPhase = 0;
    mask = track->modType == 0 ? 12 : 3;
    track->flags |= mask;
}

u8 sub_0804C558(void *player, struct SeqTrackC4 *track)
{
    const u8 *cursor = track->cursor++;
    return *cursor;
}

void sub_0804C564(void *player, struct SeqTrackC4 *track)
{
    if ((track->lfoSpeed = sub_0804C558(player, track)) == 0)
        sub_0804C53C(player, track);
}

void sub_0804C578(void *player, struct SeqTrackC4 *track)
{
    if ((track->modDepth = sub_0804C558(player, track)) == 0)
        sub_0804C53C(player, track);
}

void sub_0804C4FC(void *player, struct SeqTrackC4 *track)
{
    const u8 *cursor = track->cursor;
    unsigned int key = *cursor;
    struct SeqChannelC4 *chan;
    if (key < 0x80) {
        track->key = key;
        track->cursor = cursor + 1;
    } else {
        key = track->key;
    }
    chan = track->channels;
    while (chan != 0) {
        unsigned int flags = chan->flags;
        if ((flags & 0x83) && !(flags & 0x40) && chan->key == key) {
            chan->flags = flags | 0x40;
            break;
        }
        chan = chan->next;
    }
}

void sub_0804C5F4(void *s)
{
    register unsigned int v = *(unsigned int *)((unsigned char *)s + 52);
    if (v == 0x68736d53)
        *(unsigned int *)((unsigned char *)s + 4) &= 0x7fffffff;
}
