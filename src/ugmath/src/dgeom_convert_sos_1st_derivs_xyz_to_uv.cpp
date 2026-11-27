









bool __cdecl DGEOM_convert_SOS_1st_derivs_xyz_to_uv(
    const double* const a1,
    const double* const a2,
    const double* const a3,
    const double* const a4,
    const double* const a5,
    double* const a6,
    double* const a7)
{
    *a6 = *a1 * *a4 + *a2 * a4[1] + *a3 * a4[2];
    *a7 = *a2 * a5[1] + *a1 * *a5 + *a3 * a5[2];
    a6[1] = *a4 * a1[1] + a4[1] * a2[1] + a3[1] * a4[2];
    a7[1] = *a5 * a1[1] + a5[1] * a2[1] + a5[2] * a3[1];
    a6[2] = a4[1] * a2[2] + *a4 * a1[2] + a3[2] * a4[2];
    a7[2] = *a5 * a1[2] + a2[2] * a5[1] + a3[2] * a5[2];
    return true;
}
