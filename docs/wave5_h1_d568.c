typedef unsigned char u8;
typedef unsigned int u32;
extern void InitLinkedNode(u8 *s);
void __attribute__((section(".text.pd568b"))) PD568b(u8 *s) {
    u8 *p;
    u8 *end;
    InitLinkedNode(s);
    p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
    *(u8 **)(s + 0xc) = p;
    if (p != s + 0x14) {
        end = s + 0x14;
        do {
            ((void (*)(u8 *))*(u32 *)(p + 0x14))(p);
            p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
            *(u8 **)(s + 0xc) = p;
        } while (p != end);
    }
}
__asm__(
".thumb\n"
".set InitLinkedNode, 0x0800440C\n"
".set _call_via_r1, 0x0804DCD0\n"
);
