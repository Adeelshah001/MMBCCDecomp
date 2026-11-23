struct MusicPlayer {
    void *info;
    void *track;
    u8 numTracks;
    u8 unk9;
    u16 unkA;
};

struct Song {
    void *header;
    u16 ms;
    u16 me;
};

extern const struct MusicPlayer D_08106D7C[];
extern const struct Song D_08106DD0[];
void sub_0804CDE8(void *info, void *header);

void sub_0804C6B4(u16 n)
{
    const struct MusicPlayer *mplayTable = D_08106D7C;
    u32 tmp = (u32)D_08106DD0;
    const struct Song *song = (const struct Song *)(tmp + n * 8);

    tmp = song->ms;
    sub_0804CDE8(mplayTable[tmp].info, song->header);
}
