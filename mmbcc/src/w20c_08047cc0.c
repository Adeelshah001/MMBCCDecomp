/* Wave20 worker C @0x08047cc0 (36 B: 32 code + 4 pool), attempt 2. Pin off->r3, reassign to 0
 * before the store to get movs r3,#0 hoisted.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
__attribute__((section(".text.w20c_08047cc0")))
u32 sub_08047CC0(u8 *s)
{
    u8 v = s[0xc];
    register u32 off __asm__("r3") = 0x46B4;
    u8 *p = s + off;
    off = 0;
    *p = v;
    s[4] = 1;
    s[5] = (u8)off;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
