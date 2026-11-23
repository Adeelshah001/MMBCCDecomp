extern struct LinkSlotRecord D_02002F50[2];
extern void sub_08001D68(u8 *);

void InitLinkSlotRecords(void)
{
    u32 offset = 0;
    struct LinkSlotRecord *base = D_02002F50;
    int i = 1;
    struct LinkSlotRecord *slot;

next:
    slot = (struct LinkSlotRecord *)(offset + (u32)base);
    sub_08001D68((u8 *)slot);
    slot->unk14 = 24;
    slot->unk15 = 4;
    offset += sizeof(*slot);
    i--;
    if (i >= 0)
        goto next;
}

