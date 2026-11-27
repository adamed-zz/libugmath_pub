







#include <math.h>
#include <cstring>
#include <cstddef>
#ifdef B3_GATE_BUILD
void* SM_alloc(size_t n);
void SM_free(void* p);
void ERROR_internal(const char* a1, int a2, const char* a3, ...);
#else
__declspec(dllimport) void* SM_alloc(size_t n);
__declspec(dllimport) void SM_free(void* p);
__declspec(dllimport) void ERROR_internal(const char* a1, int a2, const char* a3, ...);
#endif
int find_closest_reals(int a1, double* a2, int a3, int a4, double a5);

int match_sorted_reals(int a1, double* a2, int a3, double* a4, int* a5) {
    int v5 = 0;
    __int64 v6 = a3;
    double* v7 = a4;
    __int64 v8 = a1;
    double* v9 = a2;
    unsigned int matched = 0;
    if (a3 > 0) {
        for (int i = 0; i < a3; ++i) a5[i] = -1;
    }
    if ((int)v8 == (int)v6) {
        if ((int)v6 > 0) {
            for (int i = 0; i < (int)v6; ++i) a5[i] = i;
            return matched;
        }
        return 0;
    }
    if ((int)v8 <= (int)v6) {
        int* v28 = (int*)SM_alloc(4 * v8);
        matched = match_sorted_reals(v6, a4, v8, a2, v28);
        if (!matched && (int)v8 > 0) {
            int* v29 = v28;
            do {
                int v30 = *v29++;
                a5[v30] = v5++;
            } while (v5 < (int)v8);
        }
        SM_free(v28);
        return matched;
    }
    int v17 = (int)v6 / 2 - 1;
    if ((v6 & 1) != 0) v17 = (int)v6 / 2;
    int v31 = v17;
    if ((int)v6 <= 0) goto LABEL_30;
    {
        __int64 v18 = v17;
        __int64 v19 = 0;
        __int64 v20 = v17;
        int v34 = v17;
        int v21 = v17;
        while (1) {
            int v22;
            __int64 v23;
            if (v5 < 0 || v19 > v18) {
                v22 = v5;
                v23 = v19;
            } else {
                v22 = v21;
                v23 = v20;
            }
            int v24 = (int)(v8 + v22 - v6);
            if (v23 >= v18) {
                if (v22 >= v17 + 1 && v22 <= a5[v23 - 1] + 1) v22 = a5[v23 - 1] + 1;
            } else {
                int v25 = a5[v23 + 1] - 1;
                if (v24 < v25) v25 = (int)(v8 + v22 - v6);
                v24 = v25;
            }
            if (v24 < v22) return 1;
            int closest_reals = find_closest_reals((int)v8, v9, v22, v24, v7[v23]);
            v17 = v31;
            ++v5;
            v7 = a4;
            ++v19;
            v9 = a2;
            --v20;
            a5[v23] = closest_reals;
            v21 = --v34;
            if (v5 >= (int)v6) goto LABEL_30;
        }
    }
LABEL_30:
    if (v6 > 1) {
        for (__int64 i = 1; i < v6; ++i) {
            if (a5[i] <= a5[i - 1]) {
                ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\get_unique_reals.c",
                               216, "match sorted reals are not in the right order");
                __debugbreak();
            }
        }
    }
    return matched;
}
