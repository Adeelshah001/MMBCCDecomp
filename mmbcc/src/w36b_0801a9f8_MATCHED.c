/* Wave 36 Worker B2 — 0x0801a9f8, TRUE extent 88 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: code + 2-word pool + pad to 0x0801aa50. The task-list 120 B is the
 * func_list gap to 0x0801aa70; the bytes 0x0801aa50-0x0801aa6f are a SEPARATE
 * function (at 0x0801aa50) NOT part of this claim — flag to coordinator as a
 * func_list gap; do NOT extend this file to 120 B.
 * Variant count: 2 (v2 + patch). Callees ChipSlot_Tick (0x0800d9fc), Sub_08017478,
 * Sub_08017464 via .set; indirect call via _call_via_r1 (harness symdef).
 * Pool: table1 0x08226644, table2 0x082243d8.
 * Key idioms: table-pointer variables so the s[12]=2 store lands between the
 * pointer computation and the table load (matching ROM's interleaving).
 * Patch: both table loads moved before their idx computation, idx in r2
 * (reorder only, same length). */
/* v2: pointer variables for table-first order */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_0800D9FC(u8 *s);
extern void Sub_08017478(u32 x, u32 y);
extern void Sub_08017464(u32 x);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__attribute__((section(".text.w36b_0801a9f8")))
void Sub_0801A9F8(u8 *s)
{
    u32 *table1 = (u32 *)0x08226644;
    u32 *table2 = (u32 *)0x082243d8;
    u32 *ptr1 = table1 + s[16];
    u8 res = (u8)((u8 (*)(u8 *))*ptr1)(s);
    Sub_0800D9FC(s);
    if (res != 0) {
        u32 *ptr2 = table2 + s[9];
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)ptr2 + 8);
        Sub_08017478(*(u32 *)(s + 44), 7);
        Sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
