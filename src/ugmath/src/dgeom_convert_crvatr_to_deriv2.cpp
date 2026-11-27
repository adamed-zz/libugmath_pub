












void DGEOM_convert_crvatr_to_deriv2(double* const a1, double* const a2, double* const a3)
{
    const double s = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
    a3[0] = s * a2[0];
    a3[1] = s * a2[1];
    a3[2] = s * a2[2];
}
