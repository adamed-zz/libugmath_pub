












#include <cstdint>

extern "C" double sub_18007EE70_cppref(void* ws, void* unused, void* cfg);

namespace {



struct SrcA1 {
    double* data;
    std::int64_t rows;
    std::int64_t count;
    std::int64_t q3;
    std::int64_t q4;
    std::int64_t q5;
    std::int64_t q6;
};


struct SrcA2 {
    double* xsrc;
    std::int64_t n;
    std::int64_t pad[6];
};


struct DotWs {
    void* pad0;
    const double* x;
    void* pad2;
    const double* y;
};

struct DotCfg {
    unsigned char pad[120];
    std::int64_t n;
};

inline double dot(const double* x, const double* y, std::int64_t n) {
    DotWs ws = { nullptr, x, nullptr, y };
    DotCfg cfg;
    cfg.n = n;
    return sub_18007EE70_cppref(&ws, nullptr, &cfg);
}

}

extern "C" void sub_180073910(SrcA1* a1, SrcA2* a2, double* a3, double* a4) {
    const double scale = *a3;
    if (a1->rows == 1) {

        const double f = 1.0 - scale;
        for (std::int64_t i = 0; i < a1->count; ++i)
            a1->data[i * 3] *= f;
        return;
    }
    if (scale == 0.0) return;
    const std::int64_t m = a1->rows - 1;
    const double* xsrc = a2->xsrc;

    for (std::int64_t i = 0; i < a1->count; ++i)
        a4[i] = (m != 0) ? dot(xsrc, a1->data + i * 3 + 1, m) : 0.0;

    for (std::int64_t i = 0; i < a1->count; ++i)
        a4[i] += a1->data[i * 3];

    for (std::int64_t i = 0; i < a1->count; ++i)
        a1->data[i * 3] -= scale * a4[i];

    for (std::int64_t i = 0; i < a1->count; ++i) {
        const double t = a4[i];
        for (std::int64_t j = 0; j < m; ++j)
            a1->data[i * 3 + 1 + j] -= (xsrc[j] * scale) * t;
    }
}
