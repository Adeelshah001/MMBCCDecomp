void _call_via_r0(void (*fn)(void)) { fn(); }
void _call_via_r1(int a, void (*fn)(void)) { fn(); }
void _call_via_r2(int a, int b, void (*fn)(void)) { fn(); }
void _call_via_r3(int a, int b, int c, void (*fn)(void)) { fn(); }
