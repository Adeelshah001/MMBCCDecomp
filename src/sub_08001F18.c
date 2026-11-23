void sub_08001F18(void)
{
}

typedef void (*SerialStateCallback)(u8 *);
extern u8 D_02002F80[];
extern SerialStateCallback const D_0816E2C0[];

void sub_08001D98(void)
{
    u8 *s = D_02002F80;
    SerialStateCallback const *table = D_0816E2C0;
    u32 index = s[2];
    table[index](s);
}

typedef struct {
    u8 unk00[20];
    u8 length;
    u8 mode;
    u8 unk16[2];
} SlotRecord;
extern SlotRecord D_02002F50[2];
extern void sub_08001D68(SlotRecord *);

void InitLinkSlotRecords(void)
{
    u32 offset = 0;
    SlotRecord *base = D_02002F50;
    int i = 1;
    do {
        SlotRecord *slot = (SlotRecord *)(offset + (u32)base);
        sub_08001D68(slot);
        slot->length = 24;
        slot->mode = 4;
        offset += sizeof(*slot);
        i--;
    } while (i >= 0);
}

typedef struct {
    u16 unk00;
    u16 enabled;
    u8 id;
    u8 ready;
} SerialStatus;
extern volatile SerialStatus D_02002EE0;
extern volatile u16 D_04000128;
extern void sub_08001800(void);
extern void sub_08001AE4(void);

void UpdateSerialLinkStatus(void)
{
    volatile u16 *control = &D_04000128;
    u16 current = *control;
    if (!(0x40 & current)) {
        volatile SerialStatus *state = &D_02002EE0;
        if (state->id == 0) {
            u32 id = 0x30;
            id &= *control;
            id >>= 4;
            (void)state->id;
            state->id = id;
        }
        (void)state->ready;
        state->ready = 1;
        if (state->enabled != 0) {
            sub_08001800();
            sub_08001AE4();
        }
    }
}
