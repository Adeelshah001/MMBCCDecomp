struct MusicPlayerTrack {
    u8 flags;
    u8 pad1[0x16];
    u8 mod;
    u8 pad18[0x38];
};

struct MusicPlayerInfo {
    u8 pad0[0x08];
    u8 trackCount;
    u8 pad9[0x23];
    struct MusicPlayerTrack *tracks;
    u32 unk30;
    u32 ident;
};

extern void sub_0804D7A0(struct MusicPlayerTrack *track);

void sub_0804D7C0(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u8 md)
{
    int i;
    u32 bit;
    struct MusicPlayerTrack *track;
    u8 mdCopy;

    if (mplayInfo->ident != 0x68736D53)
        return;

    mplayInfo->ident++;

    i = mplayInfo->trackCount;
    track = mplayInfo->tracks;
    bit = 1;

    if (i > 0) {
        mdCopy = md;
        do {
            if (trackBits & bit) {
                int mask = 0x80;
                mask &= track->flags;
                if (mask) {
                    track->mod = md;
                    if (mdCopy == 0)
                        sub_0804D7A0(track);
                }
            }
            i--;
            track++;
            bit <<= 1;
        } while (i > 0);
    }

    mplayInfo->ident = 0x68736D53;
}
