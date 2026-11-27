







void bc_POLE_set_position(double* const a1, double* const a2)
{
    double w = a1[3];
    a1[0] = w * a2[0];
    a1[1] = w * a2[1];
    a1[2] = w * a2[2];
}
