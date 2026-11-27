







#include <math.h>
#include <cstddef>
#ifdef B3_GATE_BUILD
void* SM_alloc(size_t n);
#else
__declspec(dllimport) void* SM_alloc(size_t n);
#endif

void get_unique_reals(double* a1, int a2, double** a3, int* a4) {
    static const double kTol = 1.0e-10;
    int v4 = 0;
    if (!a2) {
        *a4 = 0;
        return;
    }
    double* v11 = (double*)SM_alloc(8 * a2);
    v11[0] = a1[0];
    for (int i = 1; i < a2; ++i) {
        if (!(fabs(a1[i] - a1[i - 1]) <= kTol)) {
            ++v4;
            v11[v4] = a1[i];
        }
    }
    *a4 = v4 + 1;
    *a3 = v11;
}
