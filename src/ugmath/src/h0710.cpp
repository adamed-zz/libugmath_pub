










void h0710(const double* a1, const double* a2, const double* a3, double* a4)
{
    double t = (*a3 - *a1) / (*a2 - *a1);
    double t2 = t * t;
    double two_t = t + t;
    a4[2] = t2 + t2 - t;
    a4[1] = (t - t2) * 4.0;
    *a4 = a4[2] - two_t + 1.0;
}
