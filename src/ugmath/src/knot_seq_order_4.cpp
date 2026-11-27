






#include <cmath>
#include <cstring>

static const double kTol = 1.0000000000000000e-10;

int knot_seq_order_4(const int* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    *a4 = a1[0] + a1[1] + a1[4] + a1[5];
    a5[0] = 0.0;
    a5[1] = 0.0;
    a5[2] = 0.0;
    for (int i = 0; i < a1[0]; ++i)
        a5[3 + i] = a2[i];
    a5[(long long)a1[0] + 3] = 1.0;
    a5[(long long)a1[0] + 4] = 1.0;
    a5[(long long)a1[0] + 5] = 1.0;

    for (int i = 0; i < a1[4] + a1[5]; ++i, ++a3)
    {
        if (std::fabs(*a3) <= kTol)
            continue;
        if (std::fabs(*a3 - 1.0) <= kTol)
            continue;
        int j = 0;
        while (*a3 > a5[j])
            ++j;
        double* q = a5 + j;
        std::memmove(q + 1, q, (size_t)(*a4 - j - 1) * sizeof(double));
        *q = *a3;
    }

    if (a1[2] != 0)
    {
        const long long k = *a4;
        *a4 = (int)k + 3;
        a5[2] = a5[k - 2] - a5[k - 1];
        a5[1] = (a5[(long long)*a4 - 6] - a5[(long long)*a4 - 5]) + a5[2];
        a5[0] = (a5[(long long)*a4 - 7] - a5[(long long)*a4 - 6]) + a5[1];
        a5[(long long)*a4 - 3] = (a5[4] - a5[3]) + 1.0;
        a5[(long long)*a4 - 2] = (a5[5] - a5[4]) + a5[(long long)*a4 - 3];
        a5[(long long)*a4 - 1] = (a5[6] - a5[5]) + a5[(long long)*a4 - 2];
    }
    return 0;
}
