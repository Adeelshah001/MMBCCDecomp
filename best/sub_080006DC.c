/* extern void sub_0804DB24(void *src, void *dst, u32 count); */
/* extern void sub_0804DB28(void *src, void *dst, u32 count); */

void sub_080006DC(u16 value, u8 *dest, int count)
{
    u8 *aligned_dest;
    int aligned_count;
    u32 pattern;
    unsigned int bulk_count;
    int words;
    u32 saved_value;
    u16 stack_value;
    
    // Match target order: dest/count copies first
    aligned_dest = dest;
    aligned_count = count;
    
    // Then sign-extension
    saved_value = (u32)(u16)value;
    
    aligned_count = aligned_count & ~1;
    if (aligned_count == 0)
        return;

    aligned_dest = (u8 *)((u32)aligned_dest & ~1);
    
    if ((u32)aligned_dest & 2) {
        *(u16 *)aligned_dest = value;
        aligned_dest += 2;
        aligned_count -= 2;
        if (aligned_count == 0)
            return;
    }

    if ((unsigned)aligned_count > 0x20) {
        pattern = saved_value | (saved_value << 16);
        bulk_count = aligned_count & ~0x1F;
        words = bulk_count >> 2;
        // Match target: words & 0x001FFFFF
        words = words & 0x001FFFFF;
        sub_0804DB24(&pattern, aligned_dest, words | 0x1000000);
        aligned_dest += bulk_count;
        aligned_count &= 0x1F;
        if (aligned_count == 0)
            return;
    }

    // Match target's r2 calc: (aligned_count << 10) >> 11
    stack_value = (u16)saved_value;
    sub_0804DB28(&stack_value, aligned_dest, (((unsigned)aligned_count << 10) >> 11) | 0x1000000);
}
