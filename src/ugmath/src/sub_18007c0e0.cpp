













#include <cstdint>
#include <cmath>

typedef std::int64_t i64;
typedef std::uint64_t u64;

typedef double (*FnSq)(void*, void*, void*);
typedef i64 (*FnSlice)(void*, i64, i64);




extern "C" __m128d sub_18007F580(const void* a, const void* unused, const void* s);
extern "C" void sub_18007C0E0_set_deps(void* sq, void* div, void* fill);
extern "C" void sub_180080E70(long long** a1, long long first, long long last);
extern "C" void sub_180080DE0(long long** a1, long long first, long long last);

namespace {
struct C0E0DepsInit {
    C0E0DepsInit() {
        sub_18007C0E0_set_deps(reinterpret_cast<void*>(&sub_18007F580),
                               reinterpret_cast<void*>(&sub_180080E70),
                               reinterpret_cast<void*>(&sub_180080DE0));
    }
};
C0E0DepsInit g_c0e0_deps_init;
}

extern "C" FnSq g_sq_c0e0 = nullptr;
extern "C" FnSlice g_div_c0e0 = nullptr;
extern "C" FnSlice g_fill_c0e0 = nullptr;

extern "C" void sub_18007C0E0_set_deps(void* sq, void* div, void* fill) {
    g_sq_c0e0 = reinterpret_cast<FnSq>(sq);
    g_div_c0e0 = reinterpret_cast<FnSlice>(div);
    g_fill_c0e0 = reinterpret_cast<FnSlice>(fill);
}

extern "C" __declspec(noinline) i64 sub_18007C0E0(i64* a1, u64* a2, double* a3, double* a4) {
    const i64 v5 = a1[1];
    double* x = reinterpret_cast<double*>(a1[0]);
    const i64 v12 = a1[6];
    const i64 v14_8 = *reinterpret_cast<i64*>(v12 + 8);

    i64 d0[2] = {0, reinterpret_cast<i64>(x + 1)};
    i64 d2[3] = {0, 0, v5 - 1};
    double v17;
    if (v5 == 1)
        v17 = 0.0;
    else
        v17 = g_sq_c0e0(d0, nullptr, d2);

    const double v18 = *x;
    const double kMin = 2.2250738585072014e-308;
    if (!(v17 <= kMin)) {
        double v28 = std::sqrt(v18 * v18 + v17);
        *a4 = v28;
        if (!(v18 < 0.0)) {
            v28 = -v28;
            *a4 = v28;
        }
        const u64 v29 = a2[0];
        const i64 v32 = static_cast<i64>(a2[1]);
        const i64 v30 = a2[9];
        const i64 v31 = *reinterpret_cast<i64*>(v30 + 8);
        double* dst = reinterpret_cast<double*>(v29);



        struct Pair {
            void* pad0;
            double* src;
            i64 mid;
            void* pad1;
            double divisor;
        } pr;
        pr.pad0 = nullptr;
        pr.src = x + 1;
        pr.mid = v14_8;
        pr.pad1 = nullptr;
        pr.divisor = v18 - v28;
        double* dstp = dst;
        void* ctx[4] = {&dstp, &pr, nullptr, nullptr};

        i64 v33 = v32;
        if ((v29 & 7) == 0) {
            const i64 v34 = static_cast<i64>((-static_cast<int>(v29 >> 3)) & 1);
            if (v34 < v32) v33 = v34;
        }
        const i64 v35 = v33 + 2 * ((v32 - v33) / 2);
        g_div_c0e0(ctx, 0, v33);
        for (i64 i = v33; i < v35; i += 2) {
            dst[i] = pr.src[i] / pr.divisor;
            dst[i + 1] = pr.src[i + 1] / pr.divisor;
        }
        const i64 r = g_div_c0e0(ctx, v35, v32);
        *a3 = (*a4 - v18) / *a4;
        (void)v31;
        return r;
    }

    *a3 = 0.0;
    *a4 = v18;
    const u64 v20 = a2[0];
    const i64 v21 = static_cast<i64>(a2[1]);
    double* dst = reinterpret_cast<double*>(v20);

    struct Pair {
        double fillv;
        void* pad;
    } pf;
    pf.fillv = 0.0;
    pf.pad = nullptr;
    double* dstp = dst;
    void* ctx[4] = {&dstp, &pf, nullptr, nullptr};

    i64 v23 = v21;
    if ((v20 & 7) == 0) {
        const i64 v24 = static_cast<i64>((-static_cast<int>(v20 >> 3)) & 1);
        if (v24 < v21) v23 = v24;
    }
    const i64 v25 = v23 + 2 * ((v21 - v23) / 2);
    g_fill_c0e0(ctx, 0, v23);
    for (i64 i = v23; i < v25; i += 2) {
        dst[i] = 0.0;
        dst[i + 1] = 0.0;
    }
    return g_fill_c0e0(ctx, v25, v21);
}
