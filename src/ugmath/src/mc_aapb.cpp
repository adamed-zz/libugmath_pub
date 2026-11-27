







void MC_aApB(double s, double* const a, double* const b, double* const out)
{
    out[0] = s * a[0] + b[0];
    out[1] = s * a[1] + b[1];
    out[2] = s * a[2] + b[2];
}
