









void MC_proj_point_onto_line(double* const a1, double* const a2, double* const a3, double* const a4)
{
    double v1 = a2[1] * a1[1] + a2[0] * a1[0] + a2[2] * a1[2];
    double v2 = a3[0] * a2[0] + a2[1] * a3[1] + a2[2] * a3[2];
    double v = v1 - v2;
    a4[0] = a2[0] * v + a3[0];
    a4[1] = v * a2[1] + a3[1];
    a4[2] = v * a2[2] + a3[2];
}
