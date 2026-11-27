













#include <cmath>
#include <cstddef>

struct Solver_data_s
{
    int version;
    int m_size;
    double** dense;
    double** lu;
    int band_m;
    int pad1c;
    double** banded;
    double** al;
    int* indx;
    double* scalesBeg;
    double* scalesEnd;
    double* scalesCap;
    int* orderBeg;
    int* orderEnd;
    int* orderCap;
    int method;
};

struct Vec8 { unsigned __int64* begin; unsigned __int64* end; unsigned __int64* cap; };
extern "C" unsigned __int64* sub_180032B10(Vec8* self, unsigned __int64* whereptr,
                                          const unsigned __int64* val);
struct Vec { char* begin; char* end; char* cap; };
extern "C" void sub_1800353B0(int n, const unsigned __int64* keys, const unsigned int* ranks,
                              Vec* out);

int  h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int  h0917(double a1, const double* a2, int a3, double a4);
int  h0918(double* a1, const double* a2, int a3, int a4);

extern "C" void sub_180034540(int* a1, const double* a2, const double* a3,
                              const double* a4, const int* a5, Solver_data_s* a6)
{
    int K = a1[1];
    int flag = a1[2];
    int lim = K - 1;
    if (a1[7] + 1 <= K - 1)
        lim = a1[7] + 1;
    int band = (flag == 1) ? 2 * K - 2 : K - 1;
    int nCons = a1[4] + a1[5] + a1[6];
    int nRow = nCons + a1[0];
    int nTot = flag ? lim + nRow : nRow;
    int nKnot = nTot + K;
    double last = a2[nTot];
    if (nCons > 0)
        sub_1800353B0((unsigned)nCons, (const unsigned __int64*)a4,
                      (const unsigned int*)a5, (Vec*)((char*)a6 + 0x50));

    if (nRow > 0)
    {
        int vData = 0;
        int vCons = 0;
        for (int i = 0; i < nRow; ++i)
        {
            int cRow = flag ? ((i > (nTot - 1) / 2) ? 2 * (nTot - i) - 1 : 2 * i) : i;
            int csel = 0;
            int isCons = 0;
            int span = 0;
            double x = a3[vData];
            if (vCons < nCons)
            {
                csel = a6->orderBeg[vCons];
                if (x >= a4[csel])
                {
                    isCons = 1;
                    x = a4[csel];
                    span = a5[csel];
                }
            }
            double xq = (x == last) ? x - 5.0e-13 : x;
            double xr = xq;
            int interval = isCons ? h0918(&xr, a2, nKnot, K)
                                  : h0917(xq, a2, nKnot, 0.00001);
            double basis[64];
            double maxB = -1.0;
            double maxStore = -1.0;
            int start = interval - (K - 1);
            for (int q = 0; q < K; ++q)
            {
                double scratch[34];
                if (h0916(nKnot, a2, start + q, K, x, span, scratch))
                    return;
                double val = scratch[span];
                basis[q] = val;
                if (isCons && std::fabs(val) > maxB)
                {
                    maxStore = val;
                    maxB = val;
                }
            }
            {
                unsigned __int64 raw;
                std::memcpy(&raw, &maxB, 8);
                if (a6->scalesEnd == a6->scalesCap)
                {
                    Vec8 v = { (unsigned __int64*)a6->scalesBeg, (unsigned __int64*)a6->scalesEnd,
                               (unsigned __int64*)a6->scalesCap };
                    sub_180032B10(&v, (unsigned __int64*)a6->scalesEnd, &raw);
                    a6->scalesBeg = (double*)v.begin;
                    a6->scalesEnd = (double*)v.end;
                    a6->scalesCap = (double*)v.cap;
                }
                else
                {
                    std::memcpy(a6->scalesEnd, &raw, 8);
                    a6->scalesEnd += 1;
                }
            }
            for (int q = 0; q < K; ++q)
            {
                int g = start + q;
                int cg = flag ? ((g > (nTot - 1) / 2) ? 2 * (nTot - g) - 1 : 2 * g) : g;
                int col = band + cg - cRow;
                if (col >= 0 && col <= 2 * band)
                {
                    double val = basis[q];
                    if (isCons)
                        val = val / maxB;
                    a6->banded[cRow][col] = val;
                }
            }
            if (isCons)
                ++vCons;
            else
                ++vData;
        }
    }
    if (!flag)
        return;
    for (int k = 0; k < lim; ++k)
    {
        int i = nRow + k;
        int ci = (i > (nTot - 1) / 2) ? 2 * (nTot - i) - 1 : 2 * i;
        int ck = (k > (nTot - 1) / 2) ? 2 * (nTot - k) - 1 : 2 * k;
        int col = band + ck - ci;
        double* row = a6->banded[ci];
        if (col >= 0 && col <= 2 * band)
            row[col] = 9.0;
        row[band] = -9.0;
    }
}
