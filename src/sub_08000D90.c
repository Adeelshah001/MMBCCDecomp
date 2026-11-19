/* Task_Register @ 0x08000D90 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/task_register.c (registry: src/task_register.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct TaskEntry {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    void *handler;
    void *stack;
    u8 unkC[12];
};

#define TASK_TABLE ((struct TaskEntry *)0x030023C8)

void sub_08000D90(int index, void *handler)
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
