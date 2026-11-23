struct SeqTrackBF {
    u8 flags;
    u8 pad1[0xD];
    s8 pan;
    u8 padF[5];
    s8 bend;
    u8 pad15[0x2B];
    const u8 *cursor;
};

extern u32 sub_0804BE44(void *, struct SeqTrackBF *);
extern u32 sub_0804BE46(volatile u8 *, struct SeqTrackBF *, const u8 *);
extern volatile u8 D_04000060[];
extern const u8 D_08105CC8[];

static inline u8 ReadSequenceByte(struct SeqTrackBF *track, const u8 *cursor)
{
    const u8 *next = cursor + 1;
    u32 address = (u32)cursor;
    u8 value;
    track->cursor = next;
    value = *cursor;
    if ((address >> 25) == 0 && (address < (u32)D_08105CC8 || (address >> 14) != 0))
        value = 0;
    return value;
}
struct SoundDmaState {
    u32 ident;
    u8 counter;
    u8 pad5[6];
    u8 period;
};

extern struct SoundDmaState *D_03007FF0;
extern volatile u8 D_040000BC[];
void sub_0804BF48(void *player, struct SeqTrackBF *track)
{
    track->bend = sub_0804BE44(player, track) - 0x40;
    track->flags |= 3;
}

void sub_0804BF5C(void *player, struct SeqTrackBF *track)
{
    track->pan = sub_0804BE44(player, track) - 0x40;
    track->flags |= 12;
}

void sub_0804BFBC(void *player, struct SeqTrackBF *track)
{
    const u8 *cursor = track->cursor;
    volatile u8 *reg = D_04000060 + cursor[0];
    *reg = sub_0804BE46(reg, track, cursor + 1);
}

void sub_0804BFD4(void)
{
    struct SoundDmaState *sound = D_03007FF0;
    int counter;
    volatile u8 *dma = D_040000BC;
    if (sound->ident - 0x68736D53u <= 1u) {
        counter = sound->counter - 1;
        sound->counter = counter;
        if (counter <= 0) {
            sound->counter = sound->period;
            if (*(volatile u32 *)(dma + 8) & 0x02000000)
                *(volatile u32 *)(dma + 8) = 0x84400004;
            if (*(volatile u32 *)(dma + 0x14) & 0x02000000)
                *(volatile u32 *)(dma + 0x14) = 0x84400004;
            *(volatile u16 *)(dma + 0xA) = 0x400;
            *(volatile u16 *)(dma + 0x16) = 0x400;
            *(volatile u16 *)(dma + 0xA) = 0xB600;
            *(volatile u16 *)(dma + 0x16) = 0xB600;
        }
    }
}
