/* Wave 24-B: 0x08026184 (132 B). p3. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct { u8 *p; u16 a; u16 b; } Buf;

extern void Fill_0802520C(Buf *s, u8 *ptr, u16 n);
extern int Append_0802526C(Buf *s, u8 v);

__attribute__((section(".text.w24b_08026184")))
void F_08026184(u8 *a1, u16 *a2)
{
    u16 i;
    u32 t;

    Fill_0802520C((Buf *)(a1 + 8), *(u8 **)a1 + 0xE00, 0x82);
    Fill_0802520C((Buf *)(a1 + 16), *(u8 **)a1 + 0xE82, 0x82);
    Append_0802526C((Buf *)(a1 + 16), 0);
    ((u16 *)*(u8 *volatile *)(a1 + 4))[7] = a2[0];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[8] = a2[1];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[9] = a2[2];
    ((u16 *)*(u8 *volatile *)(a1 + 4))[10] = a2[3];
    {
        u16 *pw = (u16 *)*(u8 *volatile *)(a1 + 4);
        pw[11] = 0x8000;
    }
    (*(u8 *volatile *)(a1 + 4))[24] = 1;
    (*(u8 *volatile *)(a1 + 4))[25] = 1;
    i = 1;
    do {
        Append_0802526C((Buf *)(a1 + 8), (u8)i);
        t = ((u32)i << 16) + 0x10000;
        i = (u16)(t >> 16);
    } while ((s16)(t >> 16) <= 127);
}
