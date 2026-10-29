/* 0x08049560: GfxSetup_08049560 (328 B incl pool). v7.
   Prologue attack:
   - u16 zero=0 + volatile store -> movs r1,#0; add r0,sp,#4; strh r1,[r0]
   - real-copy asm "adds %0,%1,#0" (2 bytes, exactly ROM's bytes) forces
     ldr r0,[pc]; adds r1,r0,#0, then volatile store recomputes addr
     (r0 was clobbered by the pool load): add r0,sp,#4; strh r1,[r0] */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 F_080247C4(u8 idx);
extern void Gfx_BlitRequest(u32 a, u16 b, u16 c, u8 d, u8 e);
extern u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d);

__attribute__((section(".text.w29c_08049560")))
void GfxSetup_08049560(u8 *p) {
    u16 local;
    u16 zero = 0;
    u32 v, w;
    u16 sum;
    u8 i;
    u16 v1;
    u16 *p2;
    u16 *ew;

    *(volatile u16 *)&local = zero;
    v = 0xFFFF8000;
    __asm__ volatile("movs %0, %1" : "=r"(w) : "r"(v));
    *(volatile u16 *)&local = w;
    sum = 0;
    for (i = 1; i <= 248; i++)
        sum += F_080247C4(i);

    Gfx_BlitRequest(*(u32 *)0x08233CCC, 2, 1, 11, 2);
    Gfx_BlitRequest(*(u32 *)0x08233CD4, 2, 3, 11, 2);
    Gfx_BlitRequest(*(u32 *)0x08233CDC, 2, 5, 11, 2);
    Gfx_BlitRequest((u32)&local, 2, 7, 11, 2);
    Gfx_BlitRequest(*(u32 *)0x08233CE4, 16, 1, 8, 0);
    Gfx_BlitRequest(*(u32 *)0x08233CEC, 25, 3, 1, 0);
    GatedDispatch((void *)(u32)sum, 21, 3, 4, 0);
    Gfx_BlitRequest(*(u32 *)0x08233CF4, 16, 5, 8, 0);

    p2 = (u16 *)(p + (222 << 2));
    v1 = *(u16 *)(p + 0x37A);
    GatedDispatch((void *)(u32)(v1 + *p2), 16, 7, 4, 0);

    Gfx_BlitRequest(*(u32 *)0x08233CFC, 20, 7, 1, 0);
    GatedDispatch((void *)(u32)*p2, 21, 7, 4, 0);
    Gfx_BlitRequest(*(u32 *)0x08233D04, 25, 7, 1, 0);

    ew = (u16 *)0x02004CE0;
    ew[20] = 16;
    ew[21] = (((signed char)p[0x46A6] << 4) + 8);
}
