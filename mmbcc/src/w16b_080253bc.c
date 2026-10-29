/* Wave 16 worker B: 0x080253BC (60 B).
 * Fill_0802520C(s+12, *(s+8), 249); then for i=0..248, if *(u8*)(*(s+4)+i)
 * append 0 via Append_0802526C(s+12, 0).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;


extern int Append_0802526C(void *s, u8 v);
extern void Fill_0802520C(void *s, u8 *ptr, u16 n);
void Fill_0802520C(void *s, u8 *ptr, u16 n);
int Append_0802526C(void *s, u8 v);

void Fill_253BC(u8 *s) __attribute__((section(".text.w16b_080253bc")));
void Fill_253BC(u8 *s)
{
    Fill_0802520C(s + 12, *(u8 **)(s + 8), 249);
    {
        u16 t = 0;
        s16 i;
        do {
            i = (s16)t;
            if (*(u8 *)(*(u8 **)(s + 4) + i))
                Append_0802526C(s + 12, (u8)t);
            t = (u16)(i + 1);
        } while ((s16)t <= 248);
    }
}

