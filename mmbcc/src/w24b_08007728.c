/* Wave 24-B: 0x08007728 (84 B) MATCHED.
   Checks/sets bytes at EWRAM 0x02004830+620..622; calls NodeInit_08022FB0.
   Idiom: extern array prevents offset folding into pool word. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u8 *NodeInit_08022FB0(u32 x);
extern u8 g_02004830[];

__attribute__((section(".text.w24b_08007728")))
void F_08007728(u8 a, u8 b, u8 c)
{
    u32 off622 = 622;
    s8 v = (s8)g_02004830[620];

    if (v == -1 && (s8)a != v)
        NodeInit_08022FB0((s8)a);
    g_02004830[620] = a;
    g_02004830[621] = b;
    g_02004830[off622] = c;
}

/* TU-local absolute symbol (build's other defs are local .set per TU;
   external U refs don't resolve to them — convention is per-TU .set). */
__asm__(
    ".set g_02004830, 0x02004830\n"
);
