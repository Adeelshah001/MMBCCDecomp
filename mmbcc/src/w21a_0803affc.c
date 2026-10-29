/* Wave 21 Worker A: Task_3AFFC @ 0x0803AFFC (932 B incl. trailing pool).
 * MATCHED with old_agbcc, 928/928 zero-diff vs ROM (pool word at +0x3A0
 * verified separately). 16-case switch on p[0x469d]; prologue p->r4, ret->r5.
 *
 * Idioms (cumulative W17-W21):
 * - tail-sharing via mid-switch tail_c label + function-scope u8 z
 *   deferred-zero + explicit u8 *q ordering (W17); goto-to-late-label for
 *   case-13 layout (W19); split-shift interleave via explicit r0 + dual
 *   empty-asm barriers for cases 2/4 lsls;ldr;lsrs (W20); scoped r1-denial
 *   for case-9 g8-in-r2 + early-zero u8 z (W20).
 * - W21 clobber-reservation (NEW): to steer the 0x469d pool-load register
 *   without pinning (pinning poisons global alloc), birth the constant as a
 *   named u32 pseudo BEFORE a volatile asm that CLOBBERS the unwanted
 *   register(s); the pseudo stays live across the asm so the allocator must
 *   avoid the clobbered reg(s). Case 14: clobber "r2" -> ldr r0. Store6:
 *   clobber "r0","r1" -> ldr r2. A second empty volatile asm using the pseudo
 *   AFTER the address add keeps it live past the add (kills dest-reg
 *   coalescing) then lets it die before the byte load/store, preserving the
 *   shared strb tail-merge. Zero emitted bytes; no global perturbation.
 * Evidence: docs/match_notes_wave21_A.md. Staging: staging/wave21_A/.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

__asm__(
    ".set sub_0800BEE0, 0x0800BEE0\n"
    ".set sub_080241F8, 0x080241F8\n"
    ".set sub_0800B148, 0x0800B148\n"
    ".set sub_08024384, 0x08024384\n"
    ".set sub_0800B368, 0x0800B368\n"
    ".set sub_08024514, 0x08024514\n"
    ".set sub_0800B308, 0x0800B308\n"
    ".set EntryMgr_Teardown, 0x08004F18\n"
    ".set EntryMgr_Setup, 0x08004F80\n"
    ".set Text_SelectBlobIdx, 0x0804A378\n"
    ".set gEwram_02004E40, 0x02004E40\n"
    ".set gEwram_02002F50, 0x02002F50\n"
);

extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
extern u16 Text_SelectBlobIdx(u16 idx);
extern u8 gEwram_02004E40[];
extern u8 gEwram_02002F50[];

void sub_0800BEE0(u16 a, u8 b);
u8 sub_080241F8(u16 a);
u8 sub_0800B148(u8 a, s16 b, u8 c);
u8 sub_08024384(u16 a);
u8 sub_0800B368(u32 a, u32 b, u32 c, u32 d);
u16 sub_08024514(u8 v);
u8 sub_0800B308(void);

__attribute__((section(".text.w21a_0803affc")))
u32 Task_3AFFC(u8 *p)
{
    u32 ret = 0;
    u8 mode;
    u8 z;
    u32 off6;
    u8 *q6;
    EntryMgr_Teardown();
    {
        register u8 *gp __asm__("r0") = gEwram_02004E40;
        gp[0x14] |= 1;
    }
    mode = p[0x469d];
    if (mode > 15)
        goto epi;
    switch (mode) {
    case 0:
        sub_0800BEE0(0x40, 0x80);
        p[0x469d]++;
        /* fallthrough */
    case 1: {
        u16 w;
        w = sub_08024514((u8)sub_080241F8(0x1000));
        if ((s8)sub_0800B148(1, (s16)w, 4) != 0) {
            p[0x469d]++;
        }
        break;
    }
    case 2: {
        u32 t;
        u32 *tbl;
        u32 fn;
        register u32 r __asm__("r0");
        sub_08024384(0x1000);
        r -= 50;
        __asm__("" : "+r" (r));
        t = r << 24;
        tbl = (u32 *)0x08232128;
        __asm__ volatile ("" : "+r" (t), "+r" (tbl));
        t >>= 22;
        fn = *(u32 *)((u8 *)t + (u32)tbl);
        if ((s8)sub_0800B368(fn, *(u32 *)0x08231918, *(u32 *)0x08231920, 0) != 0) {
            p[0x469d]++;
        }
        break;
    }
    case 3: {
        u8 g8;
        if ((s8)sub_0800B308() == 0)
            break;
        g8 = gEwram_02004E40[8];
        if (g8 == 0) {
            p[0x469d] = 4;
        } else if (g8 == 1) {
            p[0x469d] = 8;
        } else {
            Text_SelectBlobIdx(0x68);
            {
                u8 *q = p + 0x469c;
                z = 0;
                *q = 9;
                goto tail_c;
            }
        }
        break;
    }
    case 4: {
        u32 t;
        u32 *tbl;
        u32 fn;
        register u32 r __asm__("r0");
        sub_08024384(0x1000);
        r -= 50;
        __asm__("" : "+r" (r));
        t = r << 24;
        tbl = (u32 *)0x08232140;
        __asm__ volatile ("" : "+r" (t), "+r" (tbl));
        t >>= 22;
        fn = *(u32 *)((u8 *)t + (u32)tbl);
        if ((s8)sub_0800B368(fn, 0, 0, 0) != 0) {
            p[0x469d]++;
        }
        break;
    }
    case 5:
        if ((s8)sub_0800B308() != 0)
            p[0x469d] = 8;
        break;
    case 6:
        sub_0800BEE0(0x40, 0x80);
        p[0x469d]++;
        /* fallthrough */
    case 7: {
        u16 w;
        w = sub_08024514((u8)sub_080241F8(0x1000));
        if ((s8)sub_0800B148(1, (s16)w, 4) == 0)
            break;
        {
            p[0x469d]++;
        }
        break;
    }
    case 8:
        if ((s8)sub_0800B368(0x08231928, *(u32 *)0x08231930, *(u32 *)0x08231938, 0) != 0) {
            p[0x469d]++;
        }
        break;
    case 9: {
        u8 g8;
        if ((s8)sub_0800B308() != 0) {
            {
                register u32 hold __asm__("r1");
                __asm__ volatile ("" : "=r" (hold));
                g8 = gEwram_02004E40[8];
                __asm__ volatile ("" : "+r" (hold));
            }
            if (g8 == 0) {
                p[0x469d] = 12;
            } else if (g8 == 1) {
                u8 *q = p + 0x469c;
                u8 z = 0;
                *q = g8;
                p[0x469d] = z;
                ret = 1;
            } else {
                u8 *q = p + 0x469c;
                u8 w = 0;
                *q = 2;
                p[0x469d] = w;
            }
        } else {
            u8 *b = gEwram_02002F50;
            u16 v = *(u16 *)(b + 4);
            if ((v & 2) == 0)
                break;
            Text_SelectBlobIdx(0x68);
            p[0x469d] = 2;
        }
        break;
    }
    case 10:
        sub_0800BEE0(0x40, 0);
        p[0x469d]++;
        /* fallthrough */
    case 11: {
        u16 w;
        w = sub_08024514((u8)sub_080241F8(0x1000));
        if ((s8)sub_0800B148(1, (s16)w, 4) == 0)
            break;
        {
            p[0x469d]++;
        }
        break;
    }
    case 12:
        if ((s8)sub_0800B368(0x08231940, *(u32 *)0x08231948, *(u32 *)0x08231950, 0) != 0) {
            p[0x469d]++;
        }
        break;
    case 13: {
        u8 g8;
        if ((s8)sub_0800B308() == 0)
            break;
        g8 = gEwram_02004E40[8];
        if (g8 == 0) {
            p[0x469c] = 6;
            p[0x469d] = 0;
            ret = 1;
        } else if (g8 == 1) {
            u8 *q = p + 0x469c;
            z = 0;
            *q = 7;
            goto tail_c;
        } else {
            goto c13_else;
        }
        break;
    tail_c:
        p[0x469d] = z;
        ret = 1;
        goto epi;
    c13_else:
        Text_SelectBlobIdx(0x68);
        goto store6;
    }
    case 14:
        if ((s8)sub_0800B368(0x0823190C, 0, 0, 0) != 0) {
            u32 off = 0x469d;
            u8 *q;
            u8 v;
            __asm__ volatile ("" : : "r" (off) : "r2");
            q = p + off;
            __asm__ volatile ("" : : "r" (off));
            v = *q;
            *q = v + 1;
        }
        break;
    case 15:
        if ((s8)sub_0800B308() != 0) {
        store6:
            off6 = 0x469d;
            __asm__ volatile ("" : : "r" (off6) : "r0", "r1");
            q6 = p + off6;
            __asm__ volatile ("" : : "r" (off6));
            *q6 = 6;
        }
        break;
    }
epi:
    EntryMgr_Setup();
    return ret;
}
