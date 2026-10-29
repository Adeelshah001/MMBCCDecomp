/* Wave 36-D v3 (x pinned r1): 0x08017670 — block-scoped ea pins + barrier after adds. */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_080176AC(u8 *s);
__asm__(".set Worker_080176AC, 0x080176ac");
__attribute__((section(".text.w36d_08017670")))
void Sub_08017670(u8 *s)
{
    register u8 idx __asm__("r3");
    {
        register u32 *tbl1 __asm__("r2") = (u32 *)0x082243d8;
        register u32 ea __asm__("r1");
        u32 *ent;
        __asm__ volatile("" : "+r"(tbl1));
        idx = s[9];
        __asm__ volatile("lsl %0, %1, #2" : "=r"(ea) : "r"(idx));
        ea += (u32)tbl1;
        __asm__ volatile("" : "+r"(ea));
        *(u32 *)(s + 12) = 1;
        ent = (u32 *)ea;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 4);
    }
    {
        register u8 x __asm__("r1");
        x = 253;
        x &= s[10];
        x &= 254;
        s[10] = x;
    }
    {
        register u32 *tbl2 __asm__("r2") = (u32 *)0x08226148;
        register u32 ea __asm__("r1");
        __asm__ volatile("" : "+r"(tbl2));
        idx = s[16];
        __asm__ volatile("lsl %0, %1, #2" : "=r"(ea) : "r"(idx));
        ea += (u32)tbl2;
        __asm__ volatile("" : "+r"(ea));
        *(u32 *)(s + 40) = *(u32 *)ea;
    }
    Worker_080176AC(s);
}
