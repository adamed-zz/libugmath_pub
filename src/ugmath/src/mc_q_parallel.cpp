







bool MC_q_parallel(double* const a, double* const b)
{
    double v2 = b[2] * a[1] - b[1] * a[2];
    double v4 = b[0] * a[2] - a[0] * b[2];
    double v3 = a[0] * b[1] - b[0] * a[1];
    return v4 * v4 + v2 * v2 + v3 * v3 < 1.7453292519943296e-05;
}
