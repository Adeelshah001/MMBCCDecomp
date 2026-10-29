/* MMBCCDecomp — BIOS call veneers (Wave 0).
 * ROM 0x0804DB24-0x0804DB38. Each compiles to `svc #n; bx lr`.
 * Calibrated: this exact idiom is byte-identical to the baserom. */

__attribute__((section(".text.bios")))
void CpuFastSet(void *src, void *dst, unsigned mode)
{
    __asm__ volatile("svc #0x0c");
}

__attribute__((section(".text.bios")))
void CpuSet(void *src, void *dst, unsigned mode)
{
    __asm__ volatile("svc #0x0b");
}

__attribute__((section(".text.bios")))
void LZ77UnCompVram(void *src, void *dst)
{
    __asm__ volatile("svc #0x12");
}

__attribute__((section(".text.bios")))
void LZ77UnCompWram(void *src, void *dst)
{
    __asm__ volatile("svc #0x11");
}

__attribute__((section(".text.bios")))
void RLUnCompVram(void *src, void *dst)
{
    __asm__ volatile("svc #0x15");
}
