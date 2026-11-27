









void MC_AxB(double* const a, double* const b, double* const out)
{
    out[0] = b[2] * a[1] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - b[0] * a[1];
}
