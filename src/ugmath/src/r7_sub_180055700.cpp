





extern "C" int MTX3_init_z(const double* zaxis, double* mtx);

struct V3 {
    double v[3];
};
struct M3x3 {
    double v[9];
};

extern "C" long long sub_180055700(int n, double* pts, double* origin, double* zaxis,
                                   double* out2d, double* out) {
    M3x3 m = {{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
    MTX3_init_z(zaxis, m.v);
    *reinterpret_cast<V3*>(out) = *reinterpret_cast<const V3*>(origin);
    *reinterpret_cast<M3x3*>(out + 3) = m;
    long long cnt = n;
    if (cnt > 0) {
        const double* p = pts;
        double* q = out2d;
        do {
            const double dx = p[0] - out[0];
            const double dy = p[1] - out[1];
            const double dz = p[2] - out[2];
            const double a = dx * out[3] + dy * out[4] + dz * out[5];
            const double b = dx * out[6] + dy * out[7] + dz * out[8];
            q[1] = b;
            q[0] = a;
            p += 3;
            q += 2;
        } while (--cnt);
    }
    return reinterpret_cast<long long>(out);
}
