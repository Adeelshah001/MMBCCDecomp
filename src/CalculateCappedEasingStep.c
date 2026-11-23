typedef short s16;

s16 CalculateCappedEasingStep(u16 target, u16 current, s16 maxStep)
{
    int cap = maxStep;
    u16 magnitude;
    u16 step;
    int delta;
    int targetValue, currentValue;

    if (cap < 0)
        cap = -cap;
    magnitude = cap;
    targetValue = (s16)target;
    currentValue = (s16)current;
    step = targetValue - currentValue;
    delta = (u32)step << 16;
    if (delta != 0) {
        int scaled;
        int absStep;
        int capBits;

        step = delta >> 18;
        scaled = (s16)step;
        absStep = scaled;
        if (scaled < 0)
            absStep = -scaled;
        capBits = (u32)magnitude << 16;
        if (absStep >= (capBits >> 16))
            step = scaled <= 0 ? (u16)-(capBits >> 16) : (u32)capBits >> 16;
        else if (scaled == 0)
            step = 1;
    }
    return (s16)step;
}
