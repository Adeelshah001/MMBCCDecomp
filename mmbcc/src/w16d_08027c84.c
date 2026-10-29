/* Wave 16-D: RecInit_08027C84 @ 0x08027c84 (48 B: 36 code + 12 pool).
 * Coordinator-landed, 0-diff verified vs ROM (bl immediates are
 * R_ARM_THM_CALL relocs). Compiler: main agbcc.
 * Behavior: v=*(s8*)(p+0x4698); InitRec8_267B4((u8*)0x20070F0,
 * *(u32*)(0x822DD84+v*4)); LoadCallClear_4A328().
 * Idioms: tied-opaque pool anti-folding; divided-syntax
 * "add %0,%0,%1" forces adds r0,r0,r1 operand order; u32-prototype extern
 * forces word ldr when callee takes u8 (ROM does ldr r1,[r0] even though
 * only low byte used). */
typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef unsigned int u32;
void InitRec8_267B4(u8 *p, u32 kind);
void LoadCallClear_4A328(void);
void RecInit_08027C84(u8 *p) __attribute__((section(".text.w16d_08027c84")));
void RecInit_08027C84(u8 *p)
{
    register u8 *q2 __asm__("r2");
    register u8 *q1 __asm__("r1");
    register u32 q3 __asm__("r3");
    __asm__ volatile("" : "=r" (q2) : "0" ((u8 *)0x20070f0));
    __asm__ volatile("" : "=r" (q1) : "0" ((u8 *)0x822dd84));
    __asm__ volatile("" : "=r" (q3) : "0" (0x4698));
    {
        s8 v = *(s8 *)(p + q3);
        int off = v * 4;
        u32 *addr;
        u32 val;
        __asm__ volatile("add %0, %0, %1" : "+r" (off) : "r" (q1));
        addr = (u32 *)off;
        val = *addr;
        InitRec8_267B4(q2, val);
    }
    LoadCallClear_4A328();
}
