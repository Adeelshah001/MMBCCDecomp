void sub_080002DC(void *unused, u32 new_lr, void *new_sp, void **save_sp) {
    *save_sp = __builtin_frame_address(0);
    // Context switch - can't do in pure C
    ((void (*)(void))new_lr)();
}
