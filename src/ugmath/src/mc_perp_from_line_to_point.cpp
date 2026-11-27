










void MC_v_unit(double* const a4);

void MC_perp_from_line_to_point(double* const a1, double* const a2, double* const a3, double* const a4)
{
    double v6 = a2[0] * a1[0] + a2[1] * a1[1] + a2[2] * a1[2] - (a3[0] * a2[0] + a3[1] * a2[1] + a3[2] * a2[2]);
    double v7 = a2[1] * v6 + a3[1];
    double v8 = a2[2] * v6 + a3[2];
    a4[0] = a1[0] - (a2[0] * v6 + a3[0]);
    a4[1] = a1[1] - v7;
    a4[2] = a1[2] - v8;
    MC_v_unit(a4);
}
