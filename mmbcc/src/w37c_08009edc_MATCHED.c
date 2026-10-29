/* W37-C MATCHED: 0x08009edc, 156 B, old_agbcc, pure C, 0 diffs.
 * Tile-table blit loop on (u8 a, u16 b). Idioms: base1 pinned r2 +
 * barriers force pool-load order; reversed additions land sums in r0;
 * do-while with s16 counter (lsls/adds-65536/lsrs/asrs idiom).
 * idx = TblGet_f0E(b); p = 0x0832b6c0 + idx*20;
 * t1 = *(u16*)(0x08172140 + a*2); t2 = *(u16*)(0x0817386c + t1*2);
 * vr = 0x06010000 + t2*32; dst = p + *(u32*)p;
 * s16 i = 0; do { Memcpy16(dst, vr, 256); dst += 256; vr += 1024;
 *   i++; } while (i <= 6);
 * Memset16(0, vr, 256); Sub_08009F78(a, b).
 * Extern callees + addresses: TblGet_f0E 0x08024670 (MATCHED),
 * Memcpy16 0x08000758 (MATCHED), Memset16 0x080006dc (BLOCKED, .set),
 * Sub_08009F78 0x08009f78 (BLOCKED, .set).
 * Pools (LE): 0x0832b6c0, 0x08172140, 0x0817386c, 0x06010000.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

extern u16 TblGet_f0E(u16 v);
extern void Memcpy16(void *dst, void *src, u32 n);
extern void Memset16(u16 v, void *dst, u32 n);
__asm__(".set Memset16, 0x080006dc");
extern void Sub_08009F78(u8 a, u16 b);
__asm__(".set Sub_08009F78, 0x08009f78");

__attribute__((section(".text.w37c_08009edc")))
void Sub_08009EDC(u8 a, u16 b)
{
    u16 idx;
    u8 *p;
    register u8 *base1 __asm__("r2");
    u8 *base2;
    u16 *p1;
    u16 t1;
    u16 t2;
    u8 *vr;
    u8 *dst;
    s16 i;
    idx = TblGet_f0E(b);
    p = (u8 *)0x0832b6c0 + idx * 20;
    base1 = (u8 *)0x08172140;
    __asm__ volatile("" : "+r"(base1));
    p1 = (u16 *)(a * 2 + (u32)base1);
    base2 = (u8 *)0x0817386c;
    __asm__ volatile("" : "+r"(base2));
    t1 = *p1;
    t2 = *(u16 *)(t1 * 2 + (u32)base2);
    vr = (u8 *)0x06010000 + t2 * 32;
    dst = p + *(u32 *)p;
    i = 0;
    do {
        Memcpy16(dst, vr, 256);
        dst += 256;
        vr += 1024;
        i++;
    } while (i <= 6);
    Memset16(0, vr, 256);
    Sub_08009F78(a, b);
}
