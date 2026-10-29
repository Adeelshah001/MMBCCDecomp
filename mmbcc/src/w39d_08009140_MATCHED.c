/* W39-D v1: 0x08009140, TRUE extent 248 B (0x08009140-0x08009238).
 * Decode (Thumb, force-thumb disasm):
 *  base=0x02003670 in r5, p=base+4 in r4.
 *  Sub_2300(0x0830b37c, 150<<7);
 *  Memset16(0x1111, *(u32*)(p+4)+(200<<3), 32);
 *  Memcpy16(0x0806bce0, *(u32*)(p+4)+(204<<3), 32);
 *  Memset16(0x3333, *(u32*)(p+4)+(208<<3), 32);
 *  Sub_2300(0x0830b3e0, 0x46a0);
 *  Memcpy16(0x08063fd4, *(u32*)(p+4)+(190<<5), 192<<1);
 *  Sub_2300(0x0830b78c, 0x5b20); Sub_2300(0x0830b3cc, 0x5a40);
 *  r=0x0805c95c; Copy7bec(r,11); (r+32,12); (r+64,13); r+=96; (r,14);
 *  Copy7bec(0x0806eea0, 10);
 *  gate: base+=0x11ae (barrier idiom from W37-A 09238 twin); if
 *  ((base[0] & 248) != 16) Copy7bec(0x0806b560, 7);
 *  Code ends bx at 0x91f4, pad 0000 at 0x91f6, pool 0x91f8-0x9237 (16 words).
 * Intended landing section: .text.w39d_08009140 (coordinator adds).
 * Callee notes: Memcpy16 0x08000758 MATCHED (build global, strip .set at
 * landing); Sub_08007BEC is an alias for Copy_08007BEC (no build-global
 * collision, keep as in W37-A 09238); Sub_08002300 + Memset16 BLOCKED
 * (keep .set).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_08002300(u32 a, u32 b);
extern void Memset16(u16 v, void *dst, u32 n);
extern void Memcpy16(void *src, void *dst, u32 n);
extern void Sub_08007BEC(u32 a, u32 b);

__attribute__((section(".text.w39d_08009140")))
void Sub_08009140(void)
{
    u8 *base = (u8 *)0x02003670;
    u8 *p;
    __asm__ volatile("" : "+r"(base));
    p = base + 4;
    Sub_08002300(0x0830b37c, 150 << 7);
    Memset16(0x1111, (void *)(*(u32 *)(p + 4) + (200 << 3)), 32);
    Memcpy16((void *)0x0806bce0, (void *)(*(u32 *)(p + 4) + (204 << 3)), 32);
    Memset16(0x3333, (void *)(*(u32 *)(p + 4) + (208 << 3)), 32);
    Sub_08002300(0x0830b3e0, 0x46a0);
    Memcpy16((void *)0x08063fd4, (void *)(*(u32 *)(p + 4) + (190 << 5)), 192 << 1);
    Sub_08002300(0x0830b78c, 0x5b20);
    Sub_08002300(0x0830b3cc, 0x5a40);
    {
        u8 *r = (u8 *)0x0805c95c;
        Sub_08007BEC((u32)r, 11);
        Sub_08007BEC((u32)r + 32, 12);
        Sub_08007BEC((u32)r + 64, 13);
        r += 96;
        Sub_08007BEC((u32)r, 14);
    }
    Sub_08007BEC(0x0806eea0, 10);
    __asm__ volatile("" : "+r"(base));
    base += 0x11ae;
    if ((*base & 248) != 16)
        Sub_08007BEC(0x0806b560, 7);
}

__asm__(".set Sub_08002300, 0x08002300");
__asm__(".set Memset16, 0x080006dc");
__asm__(".set Sub_08007BEC, 0x08007bec");
