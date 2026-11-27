










#include <cmath>

int DGEOM_srf_curvatures(double *a1, double *a2, double *a3, double *a4,
                         double *a5, int a6, double *const a7)
{
    double E = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
    double F = a2[0] * a1[0] + a2[1] * a1[1] + a2[2] * a1[2];
    double G = a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2];
    double den = G * E - F * F;
    if (1.0e-10 > den)
        return 1;

    double cx = a1[1] * a2[2] - a1[2] * a2[1];
    double cy = a1[2] * a2[0] - a1[0] * a2[2];
    double cz = a1[0] * a2[1] - a1[1] * a2[0];

    double len = sqrt(cx * cx + cy * cy + cz * cz);
    double nx = cx / len;
    double ny = cy / len;
    double nz = cz / len;

    double L = a3[0] * nx + a3[1] * ny + a3[2] * nz;
    double M = a4[0] * nx + a4[1] * ny + a4[2] * nz;
    double N = a5[0] * nx + a5[1] * ny + a5[2] * nz;

    double K = (N * L - M * M) / den;
    a7[0] = K;

    double H = ((2.0 * F) * M - N * E - L * G) * 0.5 / den;
    a7[1] = H;

    if (a6)
    {
        double d = H * H - K;
        double s = 0.0;
        if (!(1.0e-10 >= fabs(d)))
            s = sqrt(d);

        double k1 = H - s;
        double k2 = H + s;
        a7[3] = k2;
        a7[2] = k1;
        a7[5] = -L / E;
        a7[6] = -N / G;
        a7[4] = (fabs(k2) + fabs(k1)) * 0.5;
    }
    return 0;
}
