/* Task_Register @0x08000D90 (Wave 1) — MATCHED 2026-10-20.
 * Registers (index, handler) into the 24-byte task table @0x030023C8.
 * [e+0]=2 (byte), [e+1]=0 (byte), [e+2]=0 (half), [e+4]=handler,
 * [e+8]=stack top = 0x03000FA0 + index*2560 (each task gets a 2560-byte
 * stack in IWRAM just below the table). Called at boot for tasks #1/#2:
 * Task_Register(1, 0x08000419) and Task_Register(2, 0x080004FD).
 * NOTE: the stack base is emitted as (tableBaseReg - 0x1428); the u32
 * baseAddr temp (modified by -=) is what keeps the compiler from folding
 * it to the 0x03000FA0 constant. Flags: -O2 -mthumb-interwork. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct TaskEntry {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    void *handler;
    void *stack;
    u8 unkC[12];
};

#define TASK_TABLE ((struct TaskEntry *)0x030023C8)

__attribute__((section(".text.task_register")))
void Task_Register(int index, void *handler)
{
    struct TaskEntry *e = &TASK_TABLE[index];
    u32 baseAddr = 0x030023C8;
    u32 stackOff;

    e->handler = handler;
    stackOff = index * 2560;
    baseAddr -= 0x1428;
    e->stack = (void *)(stackOff + baseAddr);
    e->unk2 = 0;
    e->unk1 = 0;
    e->unk0 = 2;
}
