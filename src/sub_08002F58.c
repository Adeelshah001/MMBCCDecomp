struct MusicPlayer;
struct MusicPlayerEntry {
    struct MusicPlayer *player;
    void *tracks;
    u8 trackCount;
    u8 reserved09[3];
};
extern const struct MusicPlayerEntry D_08106D7C[];
extern const u8 D_00000007[];
extern const u8 D_000000AA[];
extern u8 D_02000818;
extern u8 D_02000819;
extern u32 D_02003244;
extern void sub_0804C630(void);
extern void sub_0804D65C(struct MusicPlayer *, u32, u32);

void sub_08002EF4(void) {
    sub_0804C630();
    D_02003244 = (u16)(u32)D_000000AA;
    D_02000818 = 0;
    D_02000819 = 0;
}

void sub_08002F58(void) {
    u16 count = (u32)D_00000007;
    if (count != 0) {
        const struct MusicPlayerEntry *entry = D_08106D7C;
        int remaining = count;
        do {
            sub_0804D65C(entry->player, 0xFFFF, 0x60);
            entry++;
        } while (--remaining != 0);
    }
}

void sub_08002F8C(void) {
    u16 count = (u32)D_00000007;
    if (count != 0) {
        const struct MusicPlayerEntry *entry = D_08106D7C;
        int remaining = count;
        do {
            sub_0804D65C(entry->player, 0xFFFF, 0x80 << 1);
            entry++;
        } while (--remaining != 0);
    }
}
