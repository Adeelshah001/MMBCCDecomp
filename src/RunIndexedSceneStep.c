typedef u8 (*SceneStep3AED0)(u8 *);

extern u8 D_02004F80[];
extern SceneStep3AED0 const D_08232344[];
extern void sub_08004E44(void);
extern void sub_08004DFC(u8);

void RunIndexedSceneStep(u8 *state)
{
    const SceneStep3AED0 *steps;
    u8 result;

    switch (state[2]) {
    case 0:
        sub_08004E44();
        sub_08004DFC(D_02004F80[2]);
        state[2]++;
        /* fall through */
    case 1:
        steps = D_08232344;
        result = steps[state[0x469C]](state);
        if (result == 1) {
            u8 reset = 0;
            state[1] = 3;
            state[2] = reset;
            state[3] = reset;
        } else if (result == 2) {
            u8 reset = 0;
            state[1] = result;
            state[2] = reset;
            state[3] = reset;
        }
        break;
    }
}
