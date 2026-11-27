











#include <cstdint>
#include <cstring>

typedef std::int64_t i64;
typedef unsigned long long u64;


extern "C" void sub_180080DE0(const i64* view, i64 first, i64 last);
extern "C" i64 sub_18007D300(const i64* a1, const i64* a2, const i64* a3);
extern "C" double sub_18007E510(void* ws, void* unused, void* cfg);
extern "C" i64 sub_180080A00(const i64* a1, const i64* a2, const i64* a3, const i64* a4);

namespace {


struct Desc {
    double* ptr;
    i64 len1;
    i64 len2;
    i64 base;
    i64 off1;
    i64 off2;
    i64 stride;
};


struct Mat {
    double* ptr;
    i64 n;
    i64 m;
    i64 base;
    i64 f4;
    i64 f5;
    i64 f6;
};

struct Vec7 {
    i64 q[7];
};


__forceinline void FillZero(double* dst, i64 first, i64 last, i64* zeroSlot) {
    i64 view[2];
    view[0] = reinterpret_cast<i64>(&dst);
    view[1] = reinterpret_cast<i64>(zeroSlot);
    sub_180080DE0(view, first, last);
}

}

extern "C" void sub_1800743E0(const Mat* a1, const Desc* a2, const double* a3, double* a4) {
    const i64 n = a1->n;
    if (n == 1) {

        const double f = 1.0 - a3[0];
        double* data = a1->ptr;
        const i64 stride = *reinterpret_cast<const i64*>(reinterpret_cast<const char*>(a1->base) + 8);
        for (i64 r = 0; r < a1->m; ++r) {
            double* row = data + r * stride;
            for (i64 c = 0; c < a1->n; ++c) row[c] *= f;
        }
        return;
    }
    if (a3[0] == 0.0) {

        return;
    }


    const i64 m = a1->m;
    const i64 stride = *reinterpret_cast<const i64*>(reinterpret_cast<const char*>(a1->base) + 8);
    double* data = a1->ptr;


    i64 pre = m;
    if ((reinterpret_cast<u64>(a4) & 7) == 0) {
        const i64 par = static_cast<i64>((-static_cast<i64>(reinterpret_cast<u64>(a4) >> 3)) & 1);
        if (par < m) pre = par;
    }
    i64 zero = 0;
    FillZero(a4, 0, pre, &zero);
    const i64 mid = pre + 2 * ((m - pre) / 2);
    for (i64 i = pre; i < mid; i += 2) {
        a4[i] = 0.0;
        a4[i + 1] = 0.0;
    }
    FillZero(a4, mid, m, &zero);


    double v30 = 0.0;
    if (m == 1) {



        Vec7 v108{};
        v108.q[0] = a1->f6;
        double v117 = 1.0;
        i64 ws[4] = {reinterpret_cast<i64>(&v117), reinterpret_cast<i64>(&v108),
                     reinterpret_cast<i64>(&v117), reinterpret_cast<i64>(&v117)};
        Vec7 cfg{};
        cfg.q[0] = reinterpret_cast<i64>(a2);
        cfg.q[1] = reinterpret_cast<i64>(a2) + 8;
        cfg.q[2] = reinterpret_cast<i64>(a2) + 16;
        cfg.q[3] = reinterpret_cast<i64>(a2) + 24;
        cfg.q[4] = reinterpret_cast<i64>(a2) + 32;
        cfg.q[5] = reinterpret_cast<i64>(a2) + 40;
        cfg.q[6] = a2->stride;
        v30 = sub_18007E510(ws, &v117, &cfg);
    } else {

        i64 v83[4] = {reinterpret_cast<i64>(a4), reinterpret_cast<i64>(&zero), 0, 0};
        i64 v92[8] = {0};
        v92[0] = reinterpret_cast<i64>(a2);
        v92[1] = reinterpret_cast<i64>(a2) + 8;
        v92[2] = reinterpret_cast<i64>(a2) + 16;
        v92[3] = reinterpret_cast<i64>(a2) + 24;
        v92[4] = reinterpret_cast<i64>(a2) + 32;
        v92[5] = reinterpret_cast<i64>(a2) + 40;
        v92[6] = a2->stride;
        v92[7] = 0;
        i64 v117 = 0;
        sub_180080A00(v83, v92, v83, &v117);
    }


    a4[0] += v30;


    for (i64 i = 0; i < m; ++i) a4[i] += data[i * stride];


    const double t = a3[0];
    for (i64 i = 0; i < m; ++i) data[i * stride] -= t * a4[i];


    Desc d1{};
    d1.ptr = data + 8;
    d1.len1 = n - 1;
    d1.len2 = m;
    d1.base = a1->base;
    d1.off1 = a1->f4;
    d1.off2 = a1->f5;
    d1.stride = a1->f6;
    i64 d2[7];
    d2[0] = reinterpret_cast<i64>(data + 8);
    d2[1] = n - 1;
    d2[2] = reinterpret_cast<i64>(a2);
    d2[3] = 0;
    d2[4] = 0x3FF0000000000000LL;
    d2[5] = reinterpret_cast<i64>(data + 8);
    d2[6] = n - 1;
    i64 d3[8] = {0};
    d3[0] = reinterpret_cast<i64>(a4);
    sub_18007D300(reinterpret_cast<const i64*>(&d1), d2, d3);
}
