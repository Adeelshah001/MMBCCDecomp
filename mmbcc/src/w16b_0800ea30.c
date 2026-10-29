/* Wave 16 worker B: 0x0800EA30 (24 B + pool).
 * Stores u8 to *(u16*)0x02005132, then SyncObjFlagBits_BEE0(s16 val, 128).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;


extern void SyncObjFlagBits_BEE0(u32 a, u32 b);
void SyncObjFlagBits_BEE0(u32 a, u32 b);
extern u8 EwrBase_2005130[];

void Set_0EA30(u8 a) __attribute__((section(".text.w16b_0800ea30")));
void Set_0EA30(u8 a)
{
    u8 *base = EwrBase_2005130;
    *(u16 *)(base + 2) = a;
    SyncObjFlagBits_BEE0(*(s16 *)(base + 2), 128);
}

__asm__(
    ".set EwrBase_2005130, 0x02005130\n"
);