void _call_via_r4(void) {
    void (*func)(void) = (void(*)(void))0;
    func();
}
