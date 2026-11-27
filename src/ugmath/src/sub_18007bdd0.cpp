

























#include <cstdint>
#include <cmath>

typedef std::int64_t i64;
typedef std::uint64_t u64;

typedef double (*FnSq)(void*, void*, void*);
typedef i64 (*FnSlice)(void*, i64, i64);

extern "C" __m128d sub_18007F580(const void*, const void*, const void*);
extern "C" void sub_180080E70(long long**, long long, long long);
extern "C" void sub_180080DE0(long long**, long long, long long);
extern "C" void sub_18007BDD0_set_deps(void* sq, void* div, void* fill);
namespace {
struct DeliveryDepsInit {
    DeliveryDepsInit() {
        sub_18007BDD0_set_deps(reinterpret_cast<void*>(&sub_18007F580),
                               reinterpret_cast<void*>(&sub_180080E70),
                               reinterpret_cast<void*>(&sub_180080DE0));
    }
};
DeliveryDepsInit g_delivery_deps_init;
}

extern "C" FnSq g_sq_bdd0 = nullptr;
extern "C" FnSlice g_div_bdd0 = nullptr;
extern "C" FnSlice g_fill_bdd0 = nullptr;

extern "C" void sub_18007BDD0_set_deps(void* sq, void* div, void* fill) {
    g_sq_bdd0 = reinterpret_cast<FnSq>(sq);
    g_div_bdd0 = reinterpret_cast<FnSlice>(div);
    g_fill_bdd0 = reinterpret_cast<FnSlice>(fill);
}

extern "C" __declspec(noinline) i64 sub_18007BDD0(i64* a1, u64* a2, double* a3, double* a4) {
    const i64 v4 = a1[0];
    const i64 v5 = a1[1];
    double* x = reinterpret_cast<double*>(v4);



    i64 d0[2] = {0, reinterpret_cast<i64>(x + 1)};
    i64 d2[3] = {0, 0, v5 - 1};
    double v15;
    if (v5 == 1)
        v15 = 0.0;
    else
        v15 = g_sq_bdd0(d0, nullptr, d2);

    const double v16 = *x;
    const double kMin = 2.2250738585072014e-308;
    if (!(v15 <= kMin)) {
        double v24 = std::sqrt(v16 * v16 + v15);
        *a4 = v24;



        if (v16 >= 0.0) {
            v24 = -v24;
            *a4 = v24;
        }
        const u64 v25 = a2[0];
        const i64 v26 = static_cast<i64>(a2[1]);
        double* dst = reinterpret_cast<double*>(v25);


        struct Pair {
            double dummy;
            double* src;
            void* pad;
            double divisor;
        } pr;
        pr.dummy = 0.0;
        pr.src = x + 1;
        pr.pad = nullptr;
        pr.divisor = v16 - v24;
        double* dstp = dst;
        void* ctx[4] = {&dstp, &pr, nullptr, nullptr};

        i64 v27 = v26;
        if ((v25 & 7) == 0) {
            const i64 v28 = static_cast<i64>((-static_cast<int>(v25 >> 3)) & 1);
            if (v28 < v26) v27 = v28;
        }
        const i64 v29 = v27 + 2 * ((v26 - v27) / 2);
        g_div_bdd0(ctx, 0, v27);
        for (i64 i = v27; i < v29; i += 2) {
            dst[i] = pr.src[i] / pr.divisor;
            dst[i + 1] = pr.src[i + 1] / pr.divisor;
        }
        const i64 r = g_div_bdd0(ctx, v29, v26);
        *a3 = (*a4 - v16) / *a4;
        return r;
    }

    *a3 = 0.0;
    const u64 v17 = a2[0];
    const i64 v18 = static_cast<i64>(a2[1]);
    double* dst = reinterpret_cast<double*>(v17);


    struct Pair {
        double fillv;
        void* pad;
    } pf;
    pf.fillv = 0.0;
    pf.pad = nullptr;
    double* dstp = dst;
    void* ctx[4] = {&dstp, &pf, nullptr, nullptr};

    *a4 = v16;
    i64 v19 = v18;
    if ((v17 & 7) == 0) {
        const i64 v20 = static_cast<i64>((-static_cast<int>(v17 >> 3)) & 1);
        if (v20 < v18) v19 = v20;
    }
    const i64 v21 = v19 + 2 * ((v18 - v19) / 2);
    g_fill_bdd0(ctx, 0, v19);
    for (i64 i = v19; i < v21; i += 2) {
        dst[i] = 0.0;
        dst[i + 1] = 0.0;
    }
    return g_fill_bdd0(ctx, v21, v18);
}
