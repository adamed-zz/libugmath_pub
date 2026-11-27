



void h430(const double* a1, const double* a2, const double* a3, double* a4);

void bc_POLE_project_to_line(double* const a1, double* const a2, double* const a3, double* const a4)
{
    double p[3];
    p[0] = a1[0] / a1[3];
    p[1] = a1[1] / a1[3];
    p[2] = a1[2] / a1[3];
    double q[3];
    q[0] = a2[0] / a2[3];
    q[1] = a2[1] / a2[3];
    q[2] = a2[2] / a2[3];
    double r[3];
    r[0] = a3[0] / a3[3];
    r[1] = a3[1] / a3[3];
    r[2] = a3[2] / a3[3];
    double out[3];
    h430(q, r, p, out);
    a4[0] = out[0] * a1[3];
    a4[1] = out[1] * a1[3];
    a4[2] = out[2] * a1[3];
    a4[3] = a1[3];
}
