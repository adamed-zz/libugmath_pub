









void bc_POLE_translate_pole(double* const a1, double* const a2, double* const a3)
{
    a3[0] = (a1[0] / a1[3] + a2[0]) * a1[3];
    a3[1] = (a1[1] / a1[3] + a2[1]) * a1[3];
    a3[2] = (a1[2] / a1[3] + a2[2]) * a1[3];
    a3[3] = a1[3];
}
