/* Wave 13 worker B: 3 Task_3AFFC callees, all main agbcc.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave13_B.md, docs/wave13_B_results.tsv.
 *
 * NOTE: the .set aliases the worker used are stripped here — all four
 * callees are landed in the build with real symbols (GetByte1_25A08 in
 * wave3_e.o, GetU8_0 in wave3_c.o, GetByte1_26554/GetByte0_265B0 in
 * wave11_B_old.o). Declarations below are kept byte-exact as verified;
 * the linker resolves them to the real symbols.
 * Tail pads: BEE0/241F8 sections get "\t.align\t2, 0" appended in the
 * Makefile rule so GAS emits 00 00 (not 46c0). 24384 (174 B) is emitted
 * via BYTE() in ldscript.ld (GAS pads the C section to 176 with c046).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u8 GetByte1_25A08(u8 *p);
u8 GetU8_0(u8 *s);
u8 GetByte1_26554(void *ctx, u32 idx);
u8 GetByte0_265B0(void *ctx, u32 idx);

/* Logical signature: (u16 a, u8 b). Prologue as v12 (byte-exact).
 * Body: pinned r0 accumulator; mask var is the AND/OR target.
 * `m |= 128`: the compiler substitutes any register known to hold 128
 * (b3, via the branch) for the constant, emitting `orr r0,r0,r3`.
 * Materialize 128 into pinned r1 with inline asm so the OR is forced to
 * `movs r1,#128; orrs r0,r1` as in ROM. Dead prologue var v (r6) is
 * reused for the two loads ROM does into r6. */
__attribute__((section(".text.w12a_0800bee0")))
void SyncObjFlagBits_BEE0(u32 a, u32 b)
{
    u32 a32;
    register u8 b3 __asm__("r3");
    register u8 b5 __asm__("r5");
    register u16 aa __asm__("r4");
    register u8 *base __asm__("r2");
    register u16 v __asm__("r6");
    register u32 vs __asm__("r1");
    a32 = a << 16;
    b3 = (u8)((b << 24) >> 24);
    b5 = b3;
    base = (u8 *)0x02004F40;
    aa = (u16)(a32 >> 16);
    v = *(u16 *)(base + 20);
    vs = (u32)v << 16;
    if (vs == a32)
        return;
    *(u16 *)(base + 6) = aa;
    if (b3 == 128) {
        register int m __asm__("r0");
        register int o __asm__("r1");
        m = 3;
        m &= base[9];
        __asm__ volatile ("mov %0, #128" : "=r" (o));
        m |= o;
        base[9] = (u8)m;
        m = -7;
        v = base[10];
        m &= v;
        base[10] = (u8)m;
    } else {
        register int m __asm__("r0");
        if (b5 > 128) {
            m = 8;
            m |= base[10];
        } else {
            m = -9;
            v = base[10];
            m &= v;
        }
        base[10] = (u8)m;
        m = -7;
        m &= base[10];
        m |= 4;
        base[10] = (u8)m;
    }
}

/* u8(u16). Prologue: aa pinned r0 forces in-place (u16) truncation;
 * idx pinned r1 forces `lsrs r1,r0,#12`. Switch is signed (bgt).
 * Cases 1/2: p pinned r0; temps pinned r1 (432/idx), r2 (p+432),
 * r3 (p[432]). Case 3: base ldr forced before mask ldr via barrier.
 * Case 4: barrier keeps pool at 0x020070CC with ldrb [r0,#1]. */
__attribute__((section(".text.w12a_080241f8")))
u8 TblGetByte_241F8(u16 a)
{
    register u32 aa __asm__("r0") = a;
    register u32 idx __asm__("r1");
    aa = (aa << 16) >> 16;
    if (aa == 0)
        return 200;
    idx = aa >> 12;
    switch ((int)idx) {
    case 1: {
        register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
        register u32 k __asm__("r1") = 216;
        register u8 *q __asm__("r2");
        register u32 x __asm__("r3");
        k <<= 1;
        q = p + k;
        x = *q;
        k = (x << 3) + x;
        k <<= 4;
        p += k;
        return (u8)GetByte1_25A08(p);
    }
    case 2: {
        register u32 m __asm__("r1");
        m = 0xFFF;
        m &= aa;
        if (m == 0) {
            register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
            register u32 k __asm__("r1") = 216;
            register u8 *q __asm__("r2");
            register u32 x __asm__("r3");
            k <<= 1;
            q = p + k;
            x = *q;
            k = (x << 3) + x;
            k <<= 4;
            p += k;
            return (u8)GetByte1_25A08(p);
        }
        return (u8)GetByte1_26554((void *)0x020070A8, m);
    }
    case 3: {
        register u32 base __asm__("r2") = 0x082298F0;
        register u32 m __asm__("r1");
        register u32 t __asm__("r0");
        __asm__("" : "+r" (base));
        m = 0xFFF;
        m &= aa;
        t = (m << 2) + m;
        t <<= 2;
        t += base;
        return *(u8 *)(t + 1);
    }
    case 4: {
        register u8 *q __asm__("r0") = (u8 *)0x020070CC;
        __asm__("" : "+r" (q));
        return q[1];
    }
    default:
        return 200;
    }
}

/* u8(u16). Twin of sub_080241F8. Differences: callees 0x08025A0C /
 * 0x080265B0, cases 3/4 use ldrb [r0,#0], default returns 50.
 * Prologue: aa pinned r0 (in-place truncation); idx pinned r1
 * (`lsrs r1,r0,#12`). Switch signed (bgt). */
__attribute__((section(".text.w12a_08024384")))
u8 TblGetByte_24384(u16 a)
{
    register u32 aa __asm__("r0") = a;
    register u32 idx __asm__("r1");
    aa = (aa << 16) >> 16;
    if (aa == 0)
        return 50;
    idx = aa >> 12;
    switch ((int)idx) {
    case 1: {
        register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
        register u32 k __asm__("r1") = 216;
        register u8 *q __asm__("r2");
        register u32 x __asm__("r3");
        k <<= 1;
        q = p + k;
        x = *q;
        k = (x << 3) + x;
        k <<= 4;
        p += k;
        return (u8)GetU8_0(p);
    }
    case 2: {
        register u32 m __asm__("r1");
        m = 0xFFF;
        m &= aa;
        if (m == 0) {
            register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
            register u32 k __asm__("r1") = 216;
            register u8 *q __asm__("r2");
            register u32 x __asm__("r3");
            k <<= 1;
            q = p + k;
            x = *q;
            k = (x << 3) + x;
            k <<= 4;
            p += k;
            return (u8)GetU8_0(p);
        }
        return (u8)GetByte0_265B0((void *)0x020070A8, m);
    }
    case 3: {
        register u32 base __asm__("r2") = 0x082298F0;
        register u32 m __asm__("r1");
        register u32 t __asm__("r0");
        __asm__("" : "+r" (base));
        m = 0xFFF;
        m &= aa;
        t = (m << 2) + m;
        t <<= 2;
        t += base;
        return *(u8 *)t;
    }
    case 4: {
        register u8 *q __asm__("r0") = (u8 *)0x020070CC;
        return *q;
    }
    default:
        return 50;
    }
}
