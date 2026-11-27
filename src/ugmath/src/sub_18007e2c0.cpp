











#include <cstdint>
#include <cstdlib>

typedef std::int64_t i64;

typedef i64 (*Fn91A30)(i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64);

extern "C" i64 sub_18007B930(i64* a1, i64* a2, i64* a3, i64 a4);

extern "C" __int64 sub_180091A30(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64);
extern "C" void sub_18007E2C0_set_callee(void* p);
namespace {
struct DeliveryDepsInit {
    DeliveryDepsInit() {
        sub_18007E2C0_set_callee(reinterpret_cast<void*>(&sub_180091A30));
    }
};
DeliveryDepsInit g_delivery_deps_init;
}

extern "C" Fn91A30 g_sub_180091A30_e2c0 = nullptr;

extern "C" void sub_18007E2C0_set_callee(void* p) {
    g_sub_180091A30_e2c0 = reinterpret_cast<Fn91A30>(p);
}

extern "C" __declspec(noinline) i64 sub_18007E2C0(i64* a1, i64* a2, i64* a3, i64* a4) {
    i64 v16 = *a4;
    i64 v7 = a2[1];
    i64 v8 = a3[2];
    i64 v9 = a2[2];
    if (v7 < v9) v9 = v7;




    i64 ws[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    i64 v15 = v8;
    ws[2] = v7;
    ws[3] = v8;
    ws[4] = v9;
    sub_18007B930(&ws[4], &ws[2], &v15, 1);
    ws[5] = ws[2] * ws[4];
    ws[6] = ws[3] * ws[4];

    i64 r = g_sub_180091A30_e2c0(v7, v8, v9, a2[0], 3, a3[0], a3[1], a1[0], 1, 3,
                                 reinterpret_cast<i64>(&v16),
                                 reinterpret_cast<i64>(&ws[0]));
    std::free(reinterpret_cast<void*>(ws[0]));
    std::free(reinterpret_cast<void*>(ws[1]));
    return r;
}
