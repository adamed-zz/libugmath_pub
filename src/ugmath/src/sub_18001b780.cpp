







extern "C" unsigned b2x_state_1B780 = 0x0001A3C8u;

extern "C" unsigned sub_18001B780(void)
{
    unsigned v = (b2x_state_1B780 & 0xFFFFD2FFu) | 0x1200u;
    b2x_state_1B780 = v;
    return v;
}
