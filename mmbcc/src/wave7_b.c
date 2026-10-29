/* Wave 7 batch B (coordinator-verified, old_agbcc).
   Task_367E0: 9-mode task state machine on p[5]. 564B.
   Evidence: docs/match_notes_wave7_b.md. */
/* Task_367E0 @ 0x080367e0 (564 B) — Wave 7 worker B, MATCHED (0 diffs).
 * old_agbcc -O2 -mthumb-interwork. 9-mode task state machine.
 * Key idioms: block-scope register pinning, opaque movs via inline asm,
 * (call()<<24) for s8 test without copy, split check_r0/inc_p5 labels,
 * u32-mask pattern to defeat 0xFC3F constant folding.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

/* matched callees (real names) */
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
extern void Task_37598(u8 *p);
extern s32 Text_SelectBlobIdx(u32 idx);

/* data symbols */
extern u8 gEwram_02004F80[];
extern u8 gEwram_02004CE0[];
extern u8 gEwram_02004E40[];
extern u8 gEwram_02002F50[];
extern u8 gByteTbl_0822FCA4[];

/* unmatched callees -> .set at end of file */
void sub_08004E44(void);
void sub_08004DFC(u32 a);
void sub_0800BEE0(u32 a, u32 b);
void sub_08005A9C(u32 a);
void sub_080374B8(u8 *p);
void sub_0800800C(u32 a, u32 b);
u32 sub_0800B148(u32 a, u32 b, u32 c);
u32 sub_0800B2D8(void);
u32 sub_08037600(u8 *p);
u32 sub_0800B308(void);
u32 sub_0800B368(u32 fn, u32 a, u32 b, u32 c);

__attribute__((section(".text.w7b_080367e0")))
u32 Task_367E0(u8 *p)
{
    register u32 ret __asm__("r5") = 0;
    u32 *ftbl;

    EntryMgr_Teardown();

    switch (p[5]) {
    case 0: {
        u8 *base;
        u8 *q;
        register u32 v __asm__("r2");
        sub_08004E44();
        sub_08004DFC(gEwram_02004F80[2]);
        sub_0800BEE0(65, 128);
        sub_08005A9C(6);
        sub_080374B8(p);
        Task_37598(p);
        base = gEwram_02004CE0;
        q = base + 44;
        __asm__ volatile("movs %0, #1" : "=l"(v));
        v |= *q;
        *(u16 *)(base + 40) = 16;
        *(u16 *)(base + 42) = (s8)p[0x4698] + 8;
        v &= -31;
        v &= -33;
        *q = v;
        {
            u16 *p44 = (u16 *)(base + 44);
            u32 w = *p44;
            w &= 0xfffffc3f;
            *p44 = (u16)w;
        }
        sub_0800800C((u32)base, 0);
        p[5]++;
        /* fallthrough */
    }
    case 1: {
        register u8 *tbl __asm__("r0") = gByteTbl_0822FCA4;
        sub_0800B148(1, tbl[p[0x469f]], 4);
        goto check_r0;
    }
    case 2: {
        register u32 m __asm__("r0");
        m = sub_0800B2D8() << 24;
        if (m != 0)
            goto m2_cont;
        goto epi;
    }
    m2_cont: {
        u32 f;
        {
            register u32 addr __asm__("r0");
            register u32 off __asm__("r1") = 0x469f;
            addr = (u32)p + off;
            f = *(u8 *)addr;
        }
        if (f != 0)
            goto m2_c1;
        {
            register u32 m __asm__("r0");
            register u8 t __asm__("r2");
            __asm__ volatile("movs %0, #1" : "=l"(m));
            t = p[0x17];
            m &= t;
            if (m == 0)
                goto m2_set7;
        }
    m2_c1:
        if (f != 1)
            goto m2_c2;
        {
            register u32 m __asm__("r0");
            register u8 t __asm__("r6");
            __asm__ volatile("movs %0, #2" : "=l"(m));
            t = p[0x17];
            m &= t;
            if (m == 0)
                goto m2_set7;
        }
    m2_c2:
        if (f != 2)
            goto inc_p5;
        {
            register u32 m __asm__("r0");
            register u8 t __asm__("r1");
            __asm__ volatile("movs %0, #4" : "=l"(m));
            t = p[0x17];
            m &= t;
            if (m != 0)
                goto inc_p5;
        }
    }
    m2_set7:
        p[5] = 7;
        goto epi;
    case 3:
        ftbl = (u32 *)0x082300A4;
        goto fn_dispatch;
    case 4: {
        u8 *g = gEwram_02004E40;
        u8 sv;
        {
            register u32 one __asm__("r1");
            __asm__ volatile("movs %0, #1" : "=l"(one));
            {
                register u8 t __asm__("r6") = g[0x14];
                one |= t;
                g[0x14] = (u8)one;
            }
        }
        sv = sub_08037600(p);
        if (sv == 1)
            goto m4_l1;
        if (sv == 2)
            goto m4_l2;
        goto epi;
    m4_l1:
        Text_SelectBlobIdx(103);
        {
            register u8 t __asm__("r2");
            register u32 off __asm__("r1") = 0x4698;
            u8 *q2;
            u8 z;
            __asm__ volatile("" : "+l"(off));
            {
                register u8 *q1 __asm__("r0");
                q1 = p + off;
                t = *q1 + 2;
            }
            q2 = p + 0x4699;
            z = 0;
            *q2 = t;
            p[5] = z;
        }
        goto epi;
    m4_l2:
        Text_SelectBlobIdx(104);
        goto inc_p5;
    }
    case 5:
        ftbl = (u32 *)0x082300B0;
        goto fn_dispatch;
    case 6: {
        u8 *g = gEwram_02004E40;
        {
            register u32 one __asm__("r1");
            __asm__ volatile("movs %0, #1" : "=l"(one));
            {
                register u8 t __asm__("r6") = g[0x14];
                one |= t;
                g[0x14] = (u8)one;
            }
        }
        if ((s8)sub_0800B308() != 0)
            goto m6_set;
        {
            u8 *b250 = gEwram_02002F50;
            if ((*(u16 *)(b250 + 4) & 2) == 0)
                goto epi;
        }
    m6_set:
        ret = 1;
        goto epi;
    }
    case 7:
        ftbl = (u32 *)0x08230098;
    fn_dispatch:
        sub_0800B368(ftbl[p[0x469f]], 0, 0, 0);
    check_r0: {
        register u32 rv __asm__("r0");
        __asm__ volatile("" : "+l"(rv));
        if ((s8)rv == 0)
            goto epi;
    }
    inc_p5:
        p[5]++;
        goto epi;
    case 8: {
        u8 *q;
        if ((s8)sub_0800B308() == 0)
            goto epi;
        {
            register u32 off __asm__("r6") = 0x469f;
            q = p + off;
        }
        if (*q != 0)
            goto m8_c1;
        p[0x17] |= 1;
    m8_c1:
        if (*q != 1)
            goto m8_c2;
        p[0x17] |= 2;
    m8_c2:
        if (*q != 2)
            goto m8_c3;
        p[0x17] |= 4;
    m8_c3: {
        u8 *q2 = p + 0x4699;
        u8 z = 0;
        *q2 = 1;
        p[5] = z;
    }
        /* fallthrough to epi */
    }
    default:
        break;
    }
epi:
    EntryMgr_Setup();
    return ret;
}

__asm__(
    ".set gEwram_02004F80,0x02004F80\n\t"
    ".set gEwram_02004CE0,0x02004CE0\n\t"
    ".set gEwram_02004E40,0x02004E40\n\t"
    ".set gEwram_02002F50,0x02002F50\n\t"
    ".set gByteTbl_0822FCA4,0x0822FCA4\n\t"
".thumb_func\n"
    ".set sub_080374B8,0x080374B8\n\t"
".thumb_func\n"
    ".set sub_0800B2D8,0x0800B2D8\n\t"
    ".thumb_func\n"
    ".set sub_08037600,0x08037600\n\t"
    ".thumb_func\n"
    ".set sub_0800B308,0x0800B308\n\t"
    ".thumb_func\n"
    ".set sub_0800B368,0x0800B368\n\t"
    ".thumb_func\n"
    ".set sub_08004E44,0x08004E44\n\t"
    ".thumb_func\n"
    ".set sub_0800BEE0,0x0800BEE0\n\t"
    ".thumb_func\n"
    ".set sub_08005A9C,0x08005A9C\n\t"
    ".thumb_func\n"
    ".set sub_0800800C,0x0800800C\n\t"
);
