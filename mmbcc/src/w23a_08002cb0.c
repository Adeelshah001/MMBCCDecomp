/* Wave 23-A: sub_08002CB0 (112 B) — main agbcc + sed fixups. DMA3 setup:
 * *p=(u16*)0x020031E0: *p=(*p&0xFFF8)|0x1300; q=(vu32*)0x040000D4:
 * q[0]=&spv(zero word), q[1]=p+4, q[2]=0x8500000E; p[2..5]=C008/4205/4406/4807;
 * bl DispCntRestore_Dma3. v=(*p&m)|0x1300 single-expr gives sibling-&= load
 * order (ldr r2/r0, ldrh r1, ands r0,r1). Scheduler will NOT split spv zero
 * (movs r3,#0 hoisted after ands / str late) nor put 0x1300 mat in r4, so
 * sed: push{r4,lr}; insert mov r3,#0 after and; mat r3->r4; drop mov r0,#0;
 * str r3,[sp]; pool ldr r3->r4 (x2); pop{r4}+pop{r0}. Fits
 * 0x08002c74(+60B)..0x08002D20 exactly. */
/* p10: u32 m local + v = (*p & m) | 0x1300 single expression.
 * Hope: ldr r2(p); ldr r0(m); ldrh r1(v); ands r0,r1 (sibling &= order). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void DispCntRestore_Dma3(void);
__attribute__((section(".text.w23a_08002CB0")))
void sub_08002CB0(void)
{
    u16 *p = (u16 *)0x020031E0;
    u32 m = 0xFFF8;
    volatile u32 *q;
    u16 v;
    u32 spv;
    v = (*p & m) | 0x1300;
    *p = v;
    spv = 0;
    q = (volatile u32 *)0x040000D4;
    q[0] = (u32)&spv;
    q[1] = (u32)((u8 *)p + 4);
    q[2] = 0x8500000E;
    (void)q[2];
    p[2] = 0xC008;
    p[3] = 0x4205;
    p[4] = 0x4406;
    p[5] = 0x4807;
    DispCntRestore_Dma3();
}
