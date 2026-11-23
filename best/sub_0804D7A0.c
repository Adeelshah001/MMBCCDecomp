struct Track4D7 {
    u8 flags;
    u8 pad01[0x15];
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
};

void sub_0804D7A0(struct Track4D7 *track)
{
    track->unk1A = 0;
    track->unk16 = 0;
    track->flags |= (track->unk18 == 0) ? 0x0C : 0x03;
}
