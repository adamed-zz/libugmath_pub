






extern bool DGEOM_convert_1st_derivs_uv_to_xy(const double *const,
                                              const double *const,
                                              double *const);
extern int SOLVE_solve_3equations(double (*const)[3], double *const,
                                  double *const);

bool DGEOM_convert_2nd_derivs_uv_to_xy(const double *const a1,
                                       const double *const a2,
                                       const double *const a3,
                                       const double *const a4,
                                       const double *const a5,
                                       double *const a6)
{
    double t[3];
    if (!DGEOM_convert_1st_derivs_uv_to_xy(a1, a2, t))
        return false;

    double m[3][3];
    m[0][0] = a1[0] * a1[0];
    m[0][1] = 2.0 * a1[0] * a1[1];
    m[0][2] = a1[1] * a1[1];
    m[1][0] = a2[0] * a1[0];
    m[1][1] = a2[0] * a1[1] + a2[1] * a1[0];
    m[1][2] = a2[1] * a1[1];
    m[2][0] = a2[0] * a2[0];
    m[2][1] = 2.0 * a2[0] * a2[1];
    m[2][2] = a2[1] * a2[1];

    const double t0 = t[0];
    const double t1 = t[1];
    t[0] = a3[2] - t0 * a3[0] - t1 * a3[1];
    t[1] = a4[2] - t0 * a4[0] - t1 * a4[1];
    t[2] = a5[2] - t0 * a5[0] - t1 * a5[1];

    if (SOLVE_solve_3equations(m, t, a6))
        return false;
    return true;
}
