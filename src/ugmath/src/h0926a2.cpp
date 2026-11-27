













#include <cmath>
#include <cstring>
#include <cstddef>

namespace UGS { namespace Memory {
struct __declspec(dllimport) CppMemory {
    static void __cdecl free(void* p);
};
}}
struct Vec { char* begin; char* end; char* cap; };
extern "C" void sub_1800353B0(int n, const unsigned __int64* keys, const unsigned int* ranks,
                              Vec* out);

int  h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int  h0917(double a1, const double* a2, int a3, double a4);
int  h0918(double* a1, const double* a2, int a3, int a4);

void h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
             const double* a5, const int* a6, const double* a7, double** a8, double* a9)
{
    int K = a1[1];
    int flag = a1[2];
    int W = a1[3];
    int lim = K - 1;
    if (a1[7] + 1 <= K - 1)
        lim = a1[7] + 1;
    int nCons = a1[4] + a1[5] + a1[6];
    int nRow = nCons + a1[0];
    int nTot = flag ? lim + nRow : nRow;
    int nKnot = nTot + K;
    double last = a3[nTot];
    int band = (flag == 1) ? 2 * K - 2 : K - 1;
    Vec order = { 0, 0, 0 };
    if (nCons > 0)
        sub_1800353B0((unsigned)nCons, (const unsigned __int64*)a5,
                      (const unsigned int*)a6, &order);

    int half = (nTot - 1) / 2;
    if (nRow > 0)
    {
        int vData = 0;
        int vCons = 0;
        for (int i = 0; i < nRow; ++i)
        {
            int span = 0;
            int cRow = flag ? ((i > half) ? 2 * (nTot - i) - 1 : 2 * i) : i;
            int csel = 0;
            int isCons = 0;
            double x = a4[vData];
            if (vCons < nCons)
            {
                csel = *(const int*)(order.begin + 4 * vCons);
                if (x >= a5[csel])
                {
                    isCons = 1;
                    x = a5[csel];
                    span = a6[csel];
                }
            }
            double xq = (x == last) ? x - 5.0e-13 : x;
            double xr = xq;
            int interval = isCons ? h0918(&xr, a3, nKnot, K)
                                  : h0917(xq, a3, nKnot, 0.00001);
            double basis[64];
            double maxB = 0.0;
            int start = interval - (K - 1);
            int ok = 1;
            for (int q = 0; q < K; ++q)
            {
                double scratch[64];
                if (h0916(nKnot, a3, start + q, K, x, span, scratch))
                {
                    ok = 0;
                    break;
                }
                double val = scratch[span];
                basis[q] = val;
                if (isCons && std::fabs(val) > maxB)
                    maxB = val;
            }
            if (!ok)
            {
                if (order.begin)
                    UGS::Memory::CppMemory::free(order.begin);
                return;
            }
            for (int q = 0; q < K; ++q)
            {
                int g = start + q;
                int cg = flag ? ((g > half) ? 2 * (nTot - g) - 1 : 2 * g) : g;
                int col = band + cg - cRow;
                if (col >= 0 && col <= 2 * band)
                {
                    double val = basis[q];
                    if (isCons)
                        val = val / maxB;
                    a8[cRow][col] = val;
                }
            }
            if (isCons)
            {
                for (int c = 0; c < W; ++c)
                    a9[cRow * W + c] = a7[csel * W + c] / maxB;
            }
            else
            {
                for (int c = 0; c < W; ++c)
                    a9[cRow * W + c] = a2[vData * W + c];
            }
            if (isCons)
                ++vCons;
            else
                ++vData;
        }
    }
    if (!flag)
    {
        if (order.begin)
            UGS::Memory::CppMemory::free(order.begin);
        return;
    }
    for (int k = 0; k < lim; ++k)
    {
        int i = nRow + k;
        int ci = (i > half) ? 2 * (nTot - i) - 1 : 2 * i;
        int ck = (k > half) ? 2 * (nTot - k) - 1 : 2 * k;
        int col = band + ck - ci;
        double* row = a8[ci];
        if (col >= 0 && col <= 2 * band)
            row[col] = 9.0;
        row[band] = -9.0;
    }
    if (order.begin)
        UGS::Memory::CppMemory::free(order.begin);
}
