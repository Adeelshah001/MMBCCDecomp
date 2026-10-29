/* 0x0801E77C: ChipFxTick2_0801E77C (256 B incl pools + pad). Wave 31-A.
 * old_agbcc, pure C (no .s patch). 0 diffs vs baserom.
 * Chip-FX state machine (sibling of ChipFxTick_0801C428): p[14] states 0-3,
 * 60-tick timer at p+120, per-type table 0x020051C8 + p[16]*12.
 * Key idioms: pool-const pinned to target reg (block scope), two-movs
 * zeroing via pinned z0/z1, ldrsh/ldrh via inline asm, memory-barrier to
 * force store-before-load order in case 3, zero-fill section tail. */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern u8 gAddrZero[];
void ChipSlot_IncUse(u8 *s, u8 idx);
void NewNode_0801D278(u8 *p, u8 *q, void *sp);
s16 SelBlob_Ret(u16 v);
void Set_08004E24(u8 x);
int Cmp_08004E0C(u8 x);
void Fwd_10BA0(void);

__attribute__((section(".text.w31a_0801e77c")))
void ChipFxTick2_0801E77C(u8 *p) {
    register u32 off __asm__("r0") = p[16] * 12;
    register u8 *tbl __asm__("r2");
    u32 sp0, sp1;
    u8 st;
    { register u32 base __asm__("r1") = (u32)&gAddrZero[0x20051c8];
      tbl = (u8 *)(off + base); }
    { register u32 z0 __asm__("r0") = 0;
      register u32 z1 __asm__("r1") = 0;
      sp0 = z0; sp1 = z1; }
    __asm__ volatile("" :: "m"(sp0), "m"(sp1));
    st = p[14];

    switch (st) {
    case 0:
        ChipSlot_IncUse(p, 8);
        p[14]++;
        p[19] = st;
        *(u16 *)(p + 120) = 60;
        NewNode_0801D278(p, p + 19, &sp0);
        /* fallthrough */
    case 1: {
        register u8 *hp __asm__("r1") = p + 120;
        u16 v = *(u16 *)hp;
        s32 sv;
        __asm__ volatile("movs r3, #0\n\tldrsh %0, [%1, r3]"
                         : "=r"(sv) : "r"(hp) : "r3");
        if (sv != 0) {
            int nv = v - 1;
            *(u16 *)hp = nv;
            if ((nv << 16) == 0)
                SelBlob_Ret(110);
        }
        if ((u8)(p[119] - 3) > 1)
            break;
        p[14]++;
        Set_08004E24(1);
        break;
    }
    case 2:
        if ((s8)Cmp_08004E0C(3) == 0)
            break;
        p[14]++;
        { register u16 *g __asm__("r2") = (u16 *)&gAddrZero[0x20031e0];
          register u32 v __asm__("r0") = 0xEDFF;
          register u32 t __asm__("r1");
          __asm__("ldrh %0, [%1]" : "=r"(t) : "r"(g));
          v &= t;
          { register u32 m __asm__("r1") = 0xDBFF;
            v &= m; }
          *g = (u16)v; }
        Fwd_10BA0();
        break;
    case 3: {
        u8 t = tbl[6];
        if (t != 0) {
            register u32 *tbase __asm__("r1") = (u32 *)&gAddrZero[0x82243d8];
            u8 idx = p[9];
            u32 e = (idx << 2) + (u32)tbase;
            *(u32 *)(p + 12) = 2;
            __asm__ volatile("" : "+r"(e) :: "memory");
            *(u32 *)(p + 20) = *(u32 *)(*(u32 *)e + 8);
        } else {
            p[13] = t;
            p[15] = t;
            p[14] = t;
        }
        tbl[1] = 0;
        break;
    }
    }
}

__asm__(".set gAddrZero, 0x0");  /* w21a precedent: .globl stripped, real build A symbol */

/* Force zero-fill (not 0x46c0 nop) for section-end alignment padding */
__asm__(".section .text.w31a_0801e77c\n.align 2, 0\n.previous");
