





extern "C" double* sub_180078010(double* base, long long i, long long j, const double* cs) {
    const double c = cs[0];
    const double s = -cs[1];
    double* pi = base + 2 * i;
    double* pj = base + 2 * j;
    if (c != 1.0 || s != 0.0) {
        double t0 = pj[0] * c - pi[0] * s;
        pi[0] = pj[0] * s + pi[0] * c;
        pj[0] = t0;
        double t1 = pj[1] * c - pi[1] * s;
        pi[1] = pj[1] * s + pi[1] * c;
        pj[1] = t1;
    }
    return pj;
}
