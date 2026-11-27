



extern "C" int sub_1800B4DA0(const double* u, double tol, double* len_out,
                             double* out);

extern "C" char sub_1800A8730(int a1, int a2, int a3, const double* a4) {
    double u[2] = {a4[2 * a2] - a4[2 * a1],
                   a4[2 * a2 + 1] - a4[2 * a1 + 1]};
    double len;
    sub_1800B4DA0(u, 1.0e-10, &len, u);
    const double ux = u[0];
    const double uy = u[1];
    const double nuy = -uy;
    if (a3 <= 0) return 0;
    const double ax = a4[2 * a1];
    const double ay = a4[2 * a1 + 1];
    int i = 0;
    long long v11 = 0;
    const double* it = a4;
    for (;;) {
        const int v13 = i + 1;
        const int v14 = (i + 1) % a3;
        if (v11 != a1 && v11 != a2 && v14 != a1 && v14 != a2) {
            const double t15 = it[1] - ay;
            const double t16 = it[0] - ax;
            const double t17 = a4[2 * v14 + 1] - ay;
            const double t18 = a4[2 * v14] - ax;
            const double v19 = t15 * uy + t16 * ux;
            const double v20 = t17 * uy + t18 * ux;

            if (!(1.0e-10 > v19) || !(1.0e-10 > v20)) {
                if (!(v19 > len - 1.0e-10) || !(v20 > len + 1.0e-10)) {
                    const double v21 = t15 * ux + t16 * nuy;
                    const double v22 = t18 * nuy + t17 * ux;
                    if (!(1.0e-10 > v21) || !(1.0e-10 > v22)) {
                        if (!(v21 > -1.0e-10) || !(v22 > 1.0e-10)) {
                            const double den = v19 - v20;
                            const double q = (v21 - v22) / den;
                            const double v23 = -(v21 - q * v19) / q;
                            if (!(1.0e-10 > v23)) {
                                if (!(v23 > len - 1.0e-10)) return 1;
                            }
                        }
                    }
                }
            }
        }
        ++v11;
        ++i;
        if (v13 >= a3) return 0;
        it += 2;
    }
}
