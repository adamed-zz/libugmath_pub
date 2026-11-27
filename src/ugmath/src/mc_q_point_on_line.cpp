






bool MC_q_point_on_line(double * const a1, double * const a2, double * const a3)
{
    double const v7 = *a2 * *a1 + a2[1] * a1[1] + a2[2] * a1[2] - (*a3 * *a2 + a3[1] * a2[1] + a3[2] * a2[2]);
    double const v8 = *a1 - (*a2 * v7 + *a3);
    double const v9 = a1[2] - (a2[2] * v7 + a3[2]);
    return !(v8 * v8 + (a1[1] - (a2[1] * v7 + a3[1])) * (a1[1] - (a2[1] * v7 + a3[1])) + v9 * v9 > 0.00000001);
}
