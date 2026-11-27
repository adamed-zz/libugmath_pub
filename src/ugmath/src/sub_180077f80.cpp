





extern "C" double* sub_180077F80(double* base, long long i, long long j, const double* cs) {
    const double c = cs[0];
    const double s = cs[1];
    double* pi = base + i;
    double* pj = base + j;
    if (c != 1.0 || s != 0.0) {
        double t0 = pj[0] * c - pi[0] * s;
        pi[0] = pi[0] * c + pj[0] * s;
        pj[0] = t0;
        double t1 = pj[2] * c - pi[2] * s;
        pi[2] = pi[2] * c + pj[2] * s;
        pj[2] = t1;
    }
    return pj;
}
