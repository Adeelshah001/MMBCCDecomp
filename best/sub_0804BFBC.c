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
    u8 value = sub_0804BE44(player, track);
    track->bend = value - 0x40;
    track->flags |= 3;
}

void sub_0804BF5C(void *player, struct SeqTrackBF *track)
{
    u8 value = sub_0804BE44(player, track);
    track->pan = value - 0x40;
    track->flags |= 12;
}

void sub_0804BFBC(void *player, struct SeqTrackBF *track)
{
    const u8 *cursor = track->cursor;
    unsigned int offset = *cursor++;
    volatile u8 *reg = (volatile u8 *)0x04000060 + offset;
    *reg = sub_0804BE46(reg, track, cursor);
}

void sub_0804BFD4(void)
{
    struct SoundDmaState *sound = D_03007FF0;
    int counter;
    volatile u8 *dma;
    if (sound->ident == 0x68736D53u || sound->ident == 0x68736D54u) {
        counter = sound->counter - 1;
        sound->counter = counter;
        if (counter <= 0) {
            u16 stop = 4 << 8;
            u16 repeat = 0xB6 << 8;
            sound->counter = sound->period;
            dma = (volatile u8 *)0x040000BC;
            if ((int)(*(volatile u32 *)(dma + 8) << 6) < 0)
                *(volatile u32 *)(dma + 8) = 0x84400004;
            if ((int)(*(volatile u32 *)(dma + 0x14) << 6) < 0)
                *(volatile u32 *)(dma + 0x14) = 0x84400004;
            *(volatile u16 *)(dma + 0xA) = stop;
            *(volatile u16 *)(dma + 0x16) = stop;
            *(volatile u16 *)(dma + 0xA) = repeat;
            *(volatile u16 *)(dma + 0x16) = repeat;
        }
    }
}
