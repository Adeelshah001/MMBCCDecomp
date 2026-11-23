typedef void (*AudioCallback)(u8 *);

struct MusicPlayer {
    u32 song;
    u8 reserved04[0x20];
    u16 fadeInterval;
    u16 fadeCounter;
    u16 fadeVolume;
    u8 reserved2A[0x0A];
    u32 ident;
};

struct MusicPlayerEntry {
    struct MusicPlayer *player;
    void *tracks;
    u8 trackCount;
    u8 reserved09[3];
};

struct SongEntry {
    u32 song;
    u16 playerIndex;
    u16 priority;
};

extern AudioCallback D_0200CE08;
extern const struct MusicPlayerEntry D_08106D7C[];
extern const struct SongEntry D_08106DD0[];
extern const u8 D_00000007[];
extern void sub_0804CECC(struct MusicPlayer *);

void sub_0804CA08(u8 *state)
{
    D_0200CE08(state);
}

void sub_0804C85C(struct MusicPlayer *player, u16 speed)
{
    if (player->ident == 0x68736D53) {
        player->fadeCounter = speed;
        player->fadeInterval = speed;
        player->fadeVolume = 0x101;
    }
}

void m4aMPlayAllStop(void)
{
    unsigned int count = (u16)(u32)D_00000007;
    const struct MusicPlayerEntry *entry;

    if (count != 0) {
        entry = D_08106D7C;
        do {
            sub_0804CECC(entry->player);
            entry++;
        } while (--count != 0);
    }
}

void sub_0804C780(int rawIndex)
{
    u32 index = (u32)rawIndex << 16;
    const struct MusicPlayerEntry *players = D_08106D7C;
    const struct SongEntry *songs = D_08106DD0;
    const struct SongEntry *song = (const struct SongEntry *)((const u8 *)songs + (index >> 13));
    struct MusicPlayer *player = players[song->playerIndex].player;

    if (player->song == song->song)
        sub_0804CECC(player);
}
