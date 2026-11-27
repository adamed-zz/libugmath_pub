











#include <cstdlib>
#include <cstring>

extern "C" __int64 sub_180035060(int* a1, const double* a2, const double* a3,
                                 __int64* a4, double* a5)
{
    int W = a1[3];
    int v6 = a1[4] + a1[5] + a1[6];
    int lim = a1[1] - 1;
    int v9 = a1[7] + 1;
    int nOut = v6 + a1[0];
    if (v9 <= lim)
        lim = v9;
    int nTotal = a1[2] ? nOut + lim : nOut;
    const double* scales = (const double*)a4[7];
    const int* map = (const int*)a4[10];
    int mapn = (a4[10] != a4[11]) ? (int)((a4[11] - a4[10]) >> 2) : 0;
    int nonpos = 0;
    int nz = 0;
    for (int i = 0; i < nOut; ++i)
    {
        double s = scales[i];
        int dst = a1[2] ? (i > (nTotal - 1) / 2 ? 2 * nTotal - 1 - 2 * i : 2 * i) : i;
        int m = 0;
        if (mapn && nz < v6)
            m = map[nz];
        if (s > 0.0)
        {
            double* d = a5 + (__int64)W * dst;
            const double* src = a3 + (__int64)W * m;
            for (int c = 0; c < W; ++c)
                d[c] = src[c] / s;
            ++nz;
        }
        else
        {
            double* d = a5 + (__int64)W * dst;
            const double* src = a2 + (__int64)W * nonpos;
            for (int c = 0; c < W; ++c)
                d[c] = src[c];
            ++nonpos;
        }
    }
    return nz;
}
