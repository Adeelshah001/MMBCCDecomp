/* W37-C MATCHED: 0x0804cbcc, 152 B, old_agbcc, pure C, 0 diffs.
 * Magic-guarded key-mask handler. Idioms: keys copied to pinned r3
 * (first statement, ROM prologue order); do-while strided clear loop;
 * t-in-place for the 0xB00000 value (lands in r4); pinned r2 pointer +
 * pinned r1 byte + barrier for the P update order.
 * p = *(u32 **)0x03007ff0; if (*p != 0x68736d53) return; *p += 1;
 * t = k & 0xFF; if (t) p[5] = t & 0x7F;
 * t = k & 0xF00; if (t) { p[6] = t >> 8; clear 12 strided bytes at
 *   p+80 step 64; }
 * t = k & 0xF000; if (t) p[7] = t >> 12;
 * t = k & 0xB00000; if (t) *(u8*)0x04000089 =
 *   (*(u8*)0x04000089 & 0x3F) | ((t & 0x300000) >> 14);
 * t = k & 0xF0000; if (t) { HwSetup_0804CCB8(); Sub_0804CB28(t); }
 * *p = 0x68736d53.
 * Extern callees + addresses: HwSetup_0804CCB8 0x0804ccb8 (MATCHED),
 * Sub_0804CB28 0x0804cb28 (unmatched, file-local .set).
 * Pools (LE): 0x03007ff0, 0x68736d53, 0x04000089.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern void HwSetup_0804CCB8(void);
extern void Sub_0804CB28(u32 t);
__asm__(".set Sub_0804CB28, 0x0804cb28");

__attribute__((section(".text.w37c_0804cbcc")))
void Sub_0804CBCC(u32 keys)
{
    register u32 k __asm__("r3");
    u32 *p;
    u32 t;
    k = keys;
    p = *(u32 **)0x03007ff0;
    if (*p != 0x68736d53)
        return;
    *p += 1;
    t = k & 0xff;
    if (t != 0)
        ((u8 *)p)[5] = t & 0x7f;
    t = k & 0xf00;
    if (t != 0) {
        u8 *q;
        ((u8 *)p)[6] = t >> 8;
        t = 12;
        q = (u8 *)p;
        q += 80;
        do {
            *q = 0;
            t--;
            q += 64;
        } while (t != 0);
    }
    t = k & 0xf000;
    if (t != 0)
        ((u8 *)p)[7] = t >> 12;
    t = k & 0xb00000;
    if (t != 0) {
        register u8 *q __asm__("r2");
        register u8 b __asm__("r1");
        t = (t & 0x300000) >> 14;
        q = (u8 *)0x04000089;
        b = *q;
        __asm__ volatile("" : "+r"(b));
        *q = (b & 0x3f) | t;
    }
    t = k & 0xf0000;
    if (t != 0) {
        HwSetup_0804CCB8();
        Sub_0804CB28(t);
    }
    *p = 0x68736d53;
}
