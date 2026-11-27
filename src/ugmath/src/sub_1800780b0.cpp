





extern "C" long long sub_1800780B0(double* base, long long i, long long j, const double* cs) {
    const double c = cs[0];
    const double s = -cs[1];
    double* pi = base + 3 * i;
    double* pj = base + 3 * j;
    if (c != 1.0 || s != 0.0) {
        double t0 = pj[0] * c - pi[0] * s;
        pi[0] = pj[0] * s + pi[0] * c;
        pj[0] = t0;
        double t1 = pj[1] * c - pi[1] * s;
        pi[1] = pj[1] * s + pi[1] * c;
        pj[1] = t1;
        double t2 = pj[2] * c - pi[2] * s;
        pi[2] = pj[2] * s + pi[2] * c;
        pj[2] = t2;
    }
    return 3 * j;
}
