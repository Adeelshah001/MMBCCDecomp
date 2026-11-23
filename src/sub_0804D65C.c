struct MusicPlayerTrack {
    u8 flags;
    u8 pad1[0x12];
    u8 volMR;
    u8 pad14[0x3C];
};

struct MusicPlayerInfo {
    u8 pad0[0x08];
    u8 trackCount;
    u8 pad9[0x23];
    struct MusicPlayerTrack *tracks;
    u32 unk30;
    u32 ident;
};

void sub_0804D65C(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u16 volume)
{
    int i;
    u32 bit;
    struct MusicPlayerTrack *track;

    if (mplayInfo->ident != 0x68736D53)
        return;

    mplayInfo->ident++;

    i = mplayInfo->trackCount;
    track = mplayInfo->tracks;
    bit = 1;

    while (i > 0) {
        if (trackBits & bit) {
            if (track->flags & 0x80) {
                track->volMR = volume / 4;
                track->flags |= 3;
            }
        }
        i--;
        track++;
        bit <<= 1;
    }

    mplayInfo->ident = 0x68736D53;
}
