/* Wave 8 batch M: main-agbcc matches. Evidence: docs/match_notes_wave8_M.md */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Wave 8 worker M (TAG=M).
 * 0x08002568 (92 B): appends a 12-byte entry to the list at 0x02002FB0.
 * n = *(u32*)base; if (n > 15) return -1. Entry e = off + base, off=n*12:
 *   e[4] = (e[4] & -4) | 1            (byte op)
 *   *(u32*)(e+4) = (*(u32*)(e+4) & 3) | (a2 << 2)   (word op, clears hi bytes)
 *   *(u32*)(off + (base+8)) = a1
 *   *(u32*)(off + (base+12)) = a0
 * then *(u32*)base = n + 1; return 0.
 * Twin 0x080025c4 differs only in the byte-or constant (|2 vs |1).
 * Idioms: base pinned to r5 (forces a2->r4); -4 mask via opaque asm
 * (movs#4;neg) + m&=b to defeat &0xFC fold; "add %0,%1,%2" asm to force
 * operand order (gcc canonicalizes to the wrong order otherwise). */

extern u8 gEntList_02002FB0[];

__attribute__((section(".text.w8m_08002568")))
int EntList_Add1(u32 a0, u32 a1, u32 a2)
{
    register u8 *base __asm__("r5") = gEntList_02002FB0;
    int n = *(u32 *)base;
    u32 off;
    u8 *e;

    int result;

    if (n > 15) {
        result = -1;
    } else {
        off = n * 12;
        __asm__ volatile("add %0, %1, %2" : "=r" (e) : "r" (off), "r" (base));
        {
            register u32 m __asm__("r0");
            u32 b;
            __asm__ volatile("movs %0, #4\n\tneg %0, %0" : "=r" (m));
            b = e[4];
            m &= b;
            e[4] = m | 1;
        }
        a2 <<= 2;
    *(u32 *)(e + 4) = (*(u32 *)(e + 4) & 3) | a2;
        {
            u8 *p = base;
            u32 addr;
            p += 8;
            __asm__ volatile("add %0, %1, %2" : "=r" (addr) : "r" (off), "r" (p));
            *(u32 *)addr = a1;
        }
        {
            u8 *p = base;
            p += 12;
            off += (u32)p;
            *(u32 *)off = a0;
        }
        *(u32 *)base = *(u32 *)base + 1;
        result = 0;
    }
    return result;
}

__asm__(
    ".globl gEntList_02002FB0\n.set gEntList_02002FB0, 0x02002FB0\n"
);

/* Wave 8 worker M (TAG=M).
 * 0x080025c4 (92 B): appends a 12-byte entry to the list at 0x02002FB0.
 * n = *(u32*)base; if (n > 15) return -1. Entry e = off + base, off=n*12:
 *   e[4] = (e[4] & -4) | 1            (byte op)
 *   *(u32*)(e+4) = (*(u32*)(e+4) & 3) | (a2 << 2)   (word op, clears hi bytes)
 *   *(u32*)(off + (base+8)) = a1
 *   *(u32*)(off + (base+12)) = a0
 * then *(u32*)base = n + 1; return 0.
 * Twin 0x080025c4 differs only in the byte-or constant (|2 vs |1).
 * Idioms: base pinned to r5 (forces a2->r4); -4 mask via opaque asm
 * (movs#4;neg) + m&=b to defeat &0xFC fold; "add %0,%1,%2" asm to force
 * operand order (gcc canonicalizes to the wrong order otherwise). */

extern u8 gEntList_02002FB0[];

__attribute__((section(".text.w8m_080025c4")))
int EntList_Add2(u32 a0, u32 a1, u32 a2)
{
    register u8 *base __asm__("r5") = gEntList_02002FB0;
    int n = *(u32 *)base;
    u32 off;
    u8 *e;

    int result;

    if (n > 15) {
        result = -1;
    } else {
        off = n * 12;
        __asm__ volatile("add %0, %1, %2" : "=r" (e) : "r" (off), "r" (base));
        {
            register u32 m __asm__("r0");
            u32 b;
            __asm__ volatile("movs %0, #4\n\tneg %0, %0" : "=r" (m));
            b = e[4];
            m &= b;
            e[4] = m | 2;
        }
        a2 <<= 2;
    *(u32 *)(e + 4) = (*(u32 *)(e + 4) & 3) | a2;
        {
            u8 *p = base;
            u32 addr;
            p += 8;
            __asm__ volatile("add %0, %1, %2" : "=r" (addr) : "r" (off), "r" (p));
            *(u32 *)addr = a1;
        }
        {
            u8 *p = base;
            p += 12;
            off += (u32)p;
            *(u32 *)off = a0;
        }
        *(u32 *)base = *(u32 *)base + 1;
        result = 0;
    }
    return result;
}

__asm__(
    ".globl gEntList_02002FB0\n.set gEntList_02002FB0, 0x02002FB0\n"
);
