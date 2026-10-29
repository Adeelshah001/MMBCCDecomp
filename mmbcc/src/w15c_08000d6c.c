/* Wave 15-C: TaskScan_08000D6C @ 0x08000d6c (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_030023C8[];
void SetTaskField0_030023C8(int i);

void TaskScan_08000D6C(void) __attribute__((section(".text.w15c1_08000D6C")));
void TaskScan_08000D6C(void)
{
    u8 *p = g_030023C8;
    int i = 0;
    do
    {
        if (*p != 1)
            SetTaskField0_030023C8(i);
        i++;
        p += 24;
    } while (i <= 2);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl g_030023C8\n"
    ".set g_030023C8, 0x030023C8\n"
);
