struct SequenceTrack4BE {
    u8 flags;
    u8 pad01[2];
    u8 repeatCount;
    u8 pad04[6];
    u8 keyShift;
    u8 pad0B[0x12];
    u8 priority;
    u8 pad1E[0x22];
    const u8 *cursor;
};

struct SequencePlayer4BE {
    u8 pad00[0x1C];
    u16 tempo;
    u16 tempoScale;
    u16 scaledTempo;
};

static inline unsigned int ReadSequenceArgument(struct SequenceTrack4BE *track)
{
    const u8 *cursor = track->cursor++;
    unsigned int value = *cursor;
    if ((u32)cursor < 0x02000000)
        value = 0;
    return value;
}

void sub_0804BED0(void *player, struct SequenceTrack4BE *track)
{
    track->priority = ReadSequenceArgument(track);
}

void sub_0804BEDC(struct SequencePlayer4BE *player, struct SequenceTrack4BE *track)
{
    unsigned int tempo = ReadSequenceArgument(track) * 2;
    player->tempo = tempo;
    player->scaledTempo = (tempo * player->tempoScale) >> 8;
}

void sub_0804BEF0(void *player, struct SequenceTrack4BE *track)
{
    track->keyShift = ReadSequenceArgument(track);
    track->flags |= 12;
}

static inline void JumpSequence(struct SequenceTrack4BE *track)
{
    const u8 *source = track->cursor;
    unsigned int low = source[0];
    unsigned int address = ((u32)source[3] << 24) | ((u32)source[2] << 16)
                         | ((u32)source[1] << 8);
    if ((u32)source < 0x02000000)
        low = 0;
    track->cursor = (const u8 *)(address | low);
}

void sub_0804BEA0(void *player, struct SequenceTrack4BE *track)
{
    const u8 *source = track->cursor;
    unsigned int repeats;
    if (*source == 0) {
        track->cursor = source + 1;
        JumpSequence(track);
        return;
    }
    repeats = track->repeatCount + 1;
    track->repeatCount = repeats;
    if (repeats < ReadSequenceArgument(track)) {
        JumpSequence(track);
    } else {
        track->repeatCount = 0;
        track->cursor = source + 5;
    }
}
