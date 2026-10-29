/* Wave 35-C v4: 0x08022f48 — copy-shift temp off, off-first add */
typedef unsigned char u8;
typedef unsigned int u32;
extern int Worker_08026D94(void);
extern void Worker_0800D9FC(u8 *s);
__asm__(".set Worker_08026D94, 0x08026d94");
__asm__(".set Worker_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w35c_08022f48")))
void Sub_08022F48(u8 *s)
{
    if ((--s[18] << 24) == 0)
        goto TABLE;
    if (((Worker_08026D94() << 24) >> 24) <= 2)
        goto FINAL;
TABLE:
    {
        register u32 *tbl __asm__("r1") = (u32 *)0x08226ef0;
        register u8 idx __asm__("r2") = s[9];
        register u32 off __asm__("r0");
        u32 *ent;
        __asm__ volatile("" : "+r"(tbl));
        off = idx << 2;
        ent = (u32 *)(off + (u32)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
    }
FINAL:
    Worker_0800D9FC(s);
}
