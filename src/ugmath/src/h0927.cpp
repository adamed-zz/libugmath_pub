









#include <cstdlib>
#include <cstring>

void h0927(const int* a1, const double* a2, const double* a3, double* const a4)
{
    int W = a1[3];
    int lim = a1[1] - 1;
    if (a1[7] + 1 <= lim)
        lim = a1[7] + 1;
    int n2 = a1[4] + a1[6] + a1[5];
    int n1 = a1[0];
    for (int i = 0; i < n1; ++i)
        for (int c = 0; c < W; ++c)
            a4[(__int64)i * W + c] = a2[(__int64)i * W + c];
    for (int j = 0; j < n2; ++j)
        for (int c = 0; c < W; ++c)
            a4[(__int64)(n1 + j) * W + c] = a3[(__int64)j * W + c];
    if (a1[2] && lim > 0)
    {
        for (int k = 0; k < lim; ++k)
            for (int c = 0; c < W; ++c)
                a4[(__int64)(n1 + n2 + k) * W + c] = 0.0;
    }
}
