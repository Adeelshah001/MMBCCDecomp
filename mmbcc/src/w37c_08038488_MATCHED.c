/* W37-C MATCHED: 0x08038488, 152 B, main agbcc (old_agbcc also 0 diffs),
 * pure C, 0 diffs. Task step on struct *s, flag in r8.
 * flag=0; if (Dispatch4_R3(s, *(u16*)(s+0x469a), s[0x469f]) != 0) {
 *   save = g[7] (g = 0x0200b810); s[0x46a0] = flag;
 *   Sub28880(4096, *(u16*)(s+0x469a), s[0x469f], 8, s[0x46a1], flag);
 *   g[7] = save; LoadCallClear_4A328(); s[0x469c] = 4;
 *   s[0x469d] = flag; flag = 1; } return flag.
 * Extern callees + addresses: Dispatch4_R3 0x080400d0 (MATCHED),
 * Sub_08028880 0x08028880 (BLOCKED, file-local .set),
 * LoadCallClear_4A328 0x0804a328 (MATCHED).
 * Pools (LE): 0x469a, 0x469f, 0x0200b810, 0x46a0, 0x46a1, 0x469c, 0x469d.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Dispatch4_R3(u8 *s, u32 b, u32 c);
extern void Sub_08028880(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
__asm__(".set Sub_08028880, 0x08028880");
extern void LoadCallClear_4A328(void);

__attribute__((section(".text.w37c_08038488")))
int Sub_08038488(u8 *s)
{
    int flag = 0;
    if (Dispatch4_R3(s, *(u16 *)(s + 0x469a), s[0x469f]) != 0) {
        u8 *g = (u8 *)0x0200b810;
        u8 save = g[7];
        s[0x46a0] = flag;
        Sub_08028880(4096, *(u16 *)(s + 0x469a), s[0x469f], 8,
                     *(u8 *)(s + 0x46a1), flag);
        g[7] = save;
        LoadCallClear_4A328();
        s[0x469c] = 4;
        s[0x469d] = flag;
        flag = 1;
    }
    return flag;
}
