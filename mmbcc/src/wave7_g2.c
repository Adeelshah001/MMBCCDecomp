/* Wave 7 batch G2 (6 matched, coordinator-verified, main agbcc).
   Evidence: docs/match_notes_wave7_g2.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;



/* 0x08000c9c: ClearWord_02002ED4 (12B, coordinator-verified). */
extern unsigned int g_02002ed4;
__attribute__((section(".text.w7g2_08000c9c")))
void ClearWord_02002ED4(void)
{
    *(unsigned int *)&g_02002ed4 = 0;
}

/* 0x08001d88: ClearByte0_Half2_02002F80 (16B, coordinator-verified). */
extern unsigned char g_02002f80[];
__attribute__((section(".text.w7g2_08001d88")))
void ClearByte0_Half2_02002F80(unsigned int dummy)
{
    unsigned char *p = g_02002f80;
    unsigned int zero = 0;
    p[0] = zero;
    *(unsigned short *)(p + 2) = zero;
}

/* 0x08002e44: ClearHalf_02003220 (12B, coordinator-verified). */
extern unsigned short g_02003220;
__attribute__((section(".text.w7g2_08002e44")))
void ClearHalf_02003220(void)
{
    *(unsigned short *)&g_02003220 = 0;
}

/* 0x08002e70: ClearHalf0_SetByte14_02003230 (16B, coordinator-verified). */
extern unsigned char g_02003230[];
__attribute__((section(".text.w7g2_08002e70")))
void ClearHalf0_SetByte14_02003230(void)
{
    unsigned char *p = g_02003230;
    *(unsigned short *)p = 0;
    p[14] = 0xff;
}

/* 0x08002ed4: ClearHalf_02003240 (12B, coordinator-verified). */
extern unsigned short g_02003240;
__attribute__((section(".text.w7g2_08002ed4")))
void ClearHalf_02003240(void)
{
    *(unsigned short *)&g_02003240 = 0;
}

/* 0x0800e1f0: SetByte20_Clear21to23_02005130 (20B, coordinator-verified). */
extern unsigned char g_02005130[];
__attribute__((section(".text.w7g2_0800e1f0")))
void SetByte20_Clear21to23_02005130(unsigned char v)
{
    unsigned char *p = g_02005130;
    unsigned char zero = 0;
    p[20] = v;
    p[21] = zero;
    p[22] = zero;
    p[23] = zero;
}

__asm__(
    ".thumb_func\n"
    ".set g_02002ed4, 0x02002ed4\n"
    ".thumb_func\n"
    ".set g_02002f80, 0x02002f80\n"
    ".thumb_func\n"
    ".set g_02003090, 0x02003090\n"
    ".thumb_func\n"
    ".set g_02003220, 0x02003220\n"
    ".thumb_func\n"
    ".set g_02003230, 0x02003230\n"
    ".thumb_func\n"
    ".set g_02003240, 0x02003240\n"
    ".thumb_func\n"
    ".set g_02003674, 0x02003674\n"
    ".thumb_func\n"
    ".set g_02004830, 0x02004830\n"
    ".thumb_func\n"
    ".set g_02004e18, 0x02004e18\n"
    ".thumb_func\n"
    ".set g_02004e40, 0x02004e40\n"
    ".thumb_func\n"
    ".set g_02005160, 0x02005160\n"
    ".thumb_func\n"
    ".set g_02005168, 0x02005168\n"
    ".thumb_func\n"
    ".set g_0200517c, 0x0200517c\n"
    ".thumb_func\n"
    ".set g_020051b0, 0x020051b0\n"
    ".thumb_func\n"
    ".set g_0200b7e0, 0x0200b7e0\n"
    ".thumb_func\n"
    ".set g_0200bce8, 0x0200bce8\n"
    ".thumb_func\n"
    ".set g_0200bd20, 0x0200bd20\n"
    ".thumb_func\n"
    ".set g_030023c8, 0x030023c8\n"
    ".thumb_func\n"
    ".set g_04000052, 0x04000052\n"
    ".thumb_func\n"
    ".set g_08173fac, 0x08173fac\n"
    ".thumb_func\n"
    ".set g_082240b8, 0x082240b8\n"
    ".thumb_func\n"
    ".set g_08229828, 0x08229828\n"
    ".thumb_func\n"
    ".set g_082344cc, 0x082344cc\n"
);
