/* 0x08002A1C: sub_08002A1C (224 B). v3.
   - e2 declared before e1 (flip prologue computation order -> r6=r9+16, r7=r6)
   - s16 scnt variable: in-place sign-extension in r3, reused for muls AND mode
     (mode = scnt & 0x1FFFFF no longer folds since scnt is signed)
   - no named f12 (inline e->f12) to encourage ip->r0 + spill pattern */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u8 pad0;
    u8 b1;
    u8 b2;
    u8 pad3;
} Sub;

typedef struct {
    Sub *sub;   /* +0 */
    u32 unk4;   /* +4 */
    u32 *ip;    /* +8 */
    u8 f12;     /* +12 */
    s8 f13;     /* +13 */
    u8 pad14[2];
    u32 f16;    /* +16 */
} Entry;        /* 20 bytes */

extern void CpuSet(const void *src, void *dest, u32 mode);

__attribute__((section(".text.w29c_08002a1c")))
void sub_08002A1C(void) {
    int i;
    u32 flag;
    Entry *e1, *e2;
    i = 0;
    flag = 0x02003090;
    e1 = (Entry *)(flag + 16);
    __asm__ volatile("" ::: "memory");
    e2 = e1;

    for (; i < 16; i++) {
        if (*(u8 *)(i + flag)) {
            Sub *s = e1->sub;
            u8 b1 = s->b1;
            u16 cnt = (s->b2 - b1 + 1);
            u32 f16 = e1->f16;
            if ((f16 & 0x1FF) == 0) {
                register u32 *ip __asm__("ip") = e1->ip;
                u32 *t = (u32 *)((e1->f12 << 2) + (u32)ip);
                int sb;
                u32 tv;
                s16 scnt;
                __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=l"(sb) : "r"(e1));
                tv = *t;
                {
                    u8 *p = (u8 *)((sb << 1) + tv);
                    scnt = (s16)cnt;
                    CpuSet((u8 *)s + 4 + (((*p) * scnt) << 1),
                       (void *)((b1 << 1) + f16 + 0x03002420),
                       scnt & 0x1FFFFF);
                }
            } else {
                register u32 *ip __asm__("ip") = e2->ip;
                u32 *t = (u32 *)((e2->f12 << 2) + (u32)ip);
                int sb;
                u32 tv;
                s16 scnt;
                __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=l"(sb) : "r"(e2));
                tv = *t;
                {
                    u8 *p = (u8 *)((sb << 1) + tv);
                    scnt = (s16)cnt;
                    CpuSet((u8 *)s + 4 + (((*p) * scnt) << 1),
                       (void *)((((b1 << 1) + f16) & 0x3FF) + 0x03002420),
                       scnt & 0x1FFFFF);
                }
            }
        }
        e1++;
        e2++;
    }
}
