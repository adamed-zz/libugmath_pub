



















#include <cstdint>
#include <cstring>

typedef std::int64_t i64;

typedef i64 (*Fn91A30)(i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64);

extern "C" __int64 sub_180091A30(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64);
extern "C" void sub_18007E200_set_callee(void* p);
namespace {
struct DeliveryDepsInit {
    DeliveryDepsInit() {
        sub_18007E200_set_callee(reinterpret_cast<void*>(&sub_180091A30));
    }
};
DeliveryDepsInit g_delivery_deps_init;
}

extern "C" Fn91A30 g_sub_180091A30_e200 = nullptr;

extern "C" void sub_18007E200_set_callee(void* p) {
    g_sub_180091A30_e200 = reinterpret_cast<Fn91A30>(p);
}

extern "C" __declspec(noinline) i64 sub_18007E200(i64* a1, i64* a2, i64 a3, i64* a4) {
    i64 v4 = a2[1];
    i64 v7 = a2[2];
    i64 v8 = a2[0];
    i64 v10 = *reinterpret_cast<i64*>(a3 + 56);
    if (v4 < v7) v7 = v4;
    i64 v17 = *a4;



    double buf0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double buf1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    i64 ws[5];
    ws[0] = reinterpret_cast<i64>(buf0);
    ws[1] = reinterpret_cast<i64>(buf1);
    ws[2] = 3;
    ws[3] = 3;
    ws[4] = 2;
    return g_sub_180091A30_e200(v4, v10, v7, v8, 3, a3, *reinterpret_cast<i64*>(a3 + 48),
                                a1[0], 1, 3, reinterpret_cast<i64>(&v17),
                                reinterpret_cast<i64>(ws));
}
