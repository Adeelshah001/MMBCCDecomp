/* Wave 37-B MATCHED: 0x080402e0, 132 B, old_agbcc, C (inline-asm ldrsb, sv as int) + .s patch (w37b_080402e0_patch.py: initial base register swap + final-store byte register r2->r3). Extent to 0x08040364. Symdefs: Sub_08040834=0x08040834, Sub_08040CC4=0x08040cc4, Sub_08042998=0x08042998, Sub_080429BC=0x080429bc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
extern void Sub_08040834(u8 *o);
extern void Sub_08040CC4(u8 *o);
extern void Sub_08042998(u8 *o);
extern void Sub_080429BC(u8 *o);
__asm__(".set Sub_08040834, 0x08040834");
__asm__(".set Sub_08040CC4, 0x08040cc4");
__asm__(".set Sub_080429BC, 0x080429bc");
__attribute__((section(".text.w37b_080402e0")))
void Sub_080402E0(u8 *o)
{
    u8 x = o[0x46af];
    u8 *b0 = (u8 *)0x02003670;
    register s8 *base __asm__("r2");
    int sv;
    __asm__ volatile("" : "+r"(b0));
    base = (s8 *)(b0 + 0x11ac);
    __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(sv) : "r"(base));
    if (x == sv) {
        if (o[0x46ac] == 10) {
            Sub_08040834(o);
            Sub_08040CC4(o);
        }
        return;
    }
    {
        int d = x - sv;
        int delta;
        if (d < 0) {
            delta = 0xffff;
            if (base[0] == 14)
                Sub_08042998(o);
        } else {
            delta = 1;
            if (base[0] == 14)
                Sub_080429BC(o);
        }
        {
            u8 *f0 = (u8 *)0x02003670;
            u8 *fb;
            __asm__ volatile("" : "+r"(f0));
            fb = f0 + 0x11ac;
            *fb += delta;
        }
    }
}
