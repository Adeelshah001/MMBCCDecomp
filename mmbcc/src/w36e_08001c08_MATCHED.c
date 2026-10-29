/* Wave 36-E MATCHED: 0x08001c08 (68 B, main agbcc, 0 diffs).
 * v7: volatile reload `*(volatile u16 *)reg` for rv forces the fresh
 * ldrh r0 (ROM) instead of ldrh r1; rest as W35-C v5 (temp t, dummy
 * ldrb r0 loads). Callees via .set: 0x08001800, 0x08001ae4
 * (no MATCHED rows -- keep .set). */
typedef unsigned char u8;
typedef unsigned short u16;
extern int Worker_08001800(int v);
extern void Worker_08001AE4(int v);
__asm__(".set Worker_08001800, 0x08001800");
__asm__(".set Worker_08001AE4, 0x08001ae4");
__attribute__((section(".text.w36e_08001c08")))
void Sub_08001C08(void)
{
    register u16 *reg __asm__("r3") = (u16 *)0x04000128;
    u8 *p;
    u16 v;
    if ((*reg & 64) != 0)
        return;
    p = (u8 *)0x02002ee0;
    if (p[4] == 0) {
        u16 rv = *(volatile u16 *)reg;
        u16 t = (rv & 48) >> 4;
        __asm__ volatile("ldrb r0, [%0, #4]" :: "r"(p) : "r0");
        p[4] = t;
    }
    __asm__ volatile("ldrb r0, [%0, #5]" :: "r"(p) : "r0");
    p[5] = 1;
    v = *(u16 *)(p + 2);
    if (v != 0)
        Worker_08001AE4(Worker_08001800(v));
}
