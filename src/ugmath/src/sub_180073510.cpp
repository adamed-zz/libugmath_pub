







#include <cstddef>
#include <cstdint>

namespace {

struct MatD {
    double* data;
    std::int64_t rows;
    std::int64_t cols;
};

inline void swap2(double& a, double& b) {
    double t = a;
    a = b;
    b = t;
}

}

extern "C" void __fastcall sub_180073510(MatD* self) {
    double* d = self->data;
    const std::int64_t n = self->rows;
    const std::int64_t m = self->cols;

    int i = 0;
    for (; i + 2 <= n; i += 2) {
        for (std::int64_t j = i; j + 2 <= m; j += 2) {
            if (i == j) {
                swap2(d[i * n + j + 1], d[(i + 1) * n + j]);
            } else {
                double p0 = d[i * n + j];
                double p1 = d[i * n + j + 1];
                double q0 = d[j * n + i];
                double q1 = d[j * n + i + 1];
                double r0 = d[(i + 1) * n + j];
                double r1 = d[(i + 1) * n + j + 1];
                double s0 = d[(j + 1) * n + i];
                double s1 = d[(j + 1) * n + i + 1];
                d[i * n + j] = q0;
                d[i * n + j + 1] = s0;
                d[j * n + i] = p0;
                d[j * n + i + 1] = r0;
                d[(i + 1) * n + j] = q1;
                d[(i + 1) * n + j + 1] = s1;
                d[(j + 1) * n + i] = p1;
                d[(j + 1) * n + i + 1] = r1;
            }
        }
    }
    for (; i < n; ++i) {
        double* row = d + i * n;
        double* col = d + i;
        for (std::int64_t j = 0; j < i; ++j)
            swap2(row[j], col[j * n]);
    }
}
