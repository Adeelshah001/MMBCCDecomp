/* W39-A: 0x0803895c, 376 B (TSV; next 0x08038ad4).
 * Scripted sequence (73d4 = CondRectFill, 6a54 = Blit):
 * 73d4(s[289]?3:0, 27, 2, 1, 0); Blit(*A, 4, 1, 2, 2); Blit(*B, 5, 1, 13, 2);
 * if (s[20] > 1) { 73d4(s[301]?3:0, 28, 2, 3, 0); Blit(*A, 4, 3, 1, 2);
 *   Blit(*C, 5, 3, 12, 2); } else Blit(*A, 2, 3, 15, 2);
 * f = s[313]?3:0; if (s[20] > 5) { 73d4(f, 29, 2, 5, 0);
 *   Blit(*A, 4, 5, 1, 2); Blit(*D, 5, 5, 12, 2); } else Blit(*A, 2, 5, 15, 2);
 * f = s[325]?3:0; if (s[20] > 8) { 73d4(f, 30, 2, 7, 0);
 *   Blit(*A, 4, 7, 1, 2); Blit(*E, 5, 7, 12, 2); } else Blit(*A, 2, 7, 15, 2);
 * A=*(int*)0x08230174, B=*(int*)0x0823012c, C=*(int*)0x08230134,
 * D=*(int*)0x0823013c, E=*(int*)0x08230144.
 * pA is a kept pointer variable (ROM loads it once into r6).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void CondRectFill_080073D4(int code, int flag, int c, int d, int e);
extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);

__attribute__((section(".text.w39a_0803895c")))
void Sub_0803895C(u8 *s)
{
    int *pA;

    {
        u8 f = 0;
        if (s[289])
            f = 3;
        CondRectFill_080073D4(27, f, 2, 1, 0);
    }
    pA = (int *)0x08230174;
    Gfx_BlitRequest(*pA, 4, 1, 2, 2);
    Gfx_BlitRequest(*(int *)0x0823012c, 5, 1, 13, 2);
    if (s[20] > 1) {
        CondRectFill_080073D4(28, s[301] ? 3 : 0, 2, 3, 0);
        Gfx_BlitRequest(*pA, 4, 3, 1, 2);
        Gfx_BlitRequest(*(int *)0x08230134, 5, 3, 12, 2);
    } else {
        Gfx_BlitRequest(*pA, 2, 3, 15, 2);
    }
    {
        u8 f = s[313] ? 3 : 0;
        if (s[20] > 5) {
            CondRectFill_080073D4(29, f, 2, 5, 0);
            Gfx_BlitRequest(*(int *)0x08230174, 4, 5, 1, 2);
            Gfx_BlitRequest(*(int *)0x0823013c, 5, 5, 12, 2);
        } else {
            Gfx_BlitRequest(*(int *)0x08230174, 2, 5, 15, 2);
        }
    }
    {
        u8 f = s[325] ? 3 : 0;
        if (s[20] > 8) {
            CondRectFill_080073D4(30, f, 2, 7, 0);
            Gfx_BlitRequest(*(int *)0x08230174, 4, 7, 1, 2);
            Gfx_BlitRequest(*(int *)0x08230144, 5, 7, 12, 2);
        } else {
            Gfx_BlitRequest(*(int *)0x08230174, 2, 7, 15, 2);
        }
    }
}

