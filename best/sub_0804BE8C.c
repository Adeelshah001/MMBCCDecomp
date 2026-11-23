struct MPlayTrackCommand {
    u8 pad0[2];
    u8 patternDepth;
    u8 pad3[0x21];
    u32 voice[3];
    u8 pad30[0x10];
    const u8 *cursor;
    const u8 *patternStack[3];
};

struct MPlayVoiceGroup {
    u8 pad0[0x30];
    const u32 (*voices)[3];
};

extern const u8 D_08105CC8[];
extern void sub_0804BDE0(void *, struct MPlayTrackCommand *);

static inline u32 FilterSequenceRead(const void *address, u32 value)
{
    u32 addr = (u32)address;
    if ((addr >> 25) == 0 && (addr < (u32)D_08105CC8 || (addr >> 14) != 0))
        value = 0;
    return value;
}
extern u32 sub_0804BE28(void *, struct MPlayTrackCommand *, const u8 *);
extern u32 sub_0804BE2A(struct MPlayVoiceGroup *, struct MPlayTrackCommand *, const u32 *, u32);
void sub_0804BE8C(void *player, struct MPlayTrackCommand *track)
{
    int depth = track->patternDepth;
    if (depth != 0) {
        depth--;
        track->patternDepth = depth;
        track->cursor = ((struct MPlayTrackCommand *)((u8 *)track + depth * 4))->patternStack[0];
    }
}

void sub_0804BE50(void *player, struct MPlayTrackCommand *track)
{
    const u8 *cursor = track->cursor;
    u32 dest = cursor[3];
    dest = (dest << 8) | cursor[2];
    dest = (dest << 8) | cursor[1];
    dest = (dest << 8) | sub_0804BE28(player, track, cursor);
    track->cursor = (const u8 *)dest;
}

void sub_0804BE70(void *player, struct MPlayTrackCommand *track)
{
    int depth = track->patternDepth;
    if (depth < 3) {
        ((struct MPlayTrackCommand *)((u8 *)track + depth * 4))->patternStack[0] = track->cursor + 4;
        track->patternDepth++;
        sub_0804BE50(player, track);
    } else {
        sub_0804BDE0(player, track);
    }
}

void sub_0804BF04(struct MPlayVoiceGroup *player, struct MPlayTrackCommand *track)
{
    const u8 *cursor = track->cursor;
    unsigned int voice = *cursor++;
    const u32 *entry;
    track->cursor = cursor;
    entry = player->voices[voice];
    track->voice[0] = sub_0804BE2A(player, track, entry, entry[0]);
    track->voice[1] = sub_0804BE2A(player, track, entry, entry[1]);
    track->voice[2] = sub_0804BE2A(player, track, entry, entry[2]);
}
