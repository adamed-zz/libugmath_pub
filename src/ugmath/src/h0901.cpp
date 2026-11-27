









#include <emmintrin.h>




#pragma once
#include <math.h>

namespace UGS { namespace Math {
struct Vector2 { double x; double y; };
} }
using UGS::Math::Vector2;




extern __declspec(align(16)) unsigned char b05_glob[0x138];

inline double& GB(unsigned rva) { return *reinterpret_cast<double*>(b05_glob + (rva - 0xE0920)); }
inline const int* IB(unsigned rva) { return reinterpret_cast<const int*>(b05_glob + (rva - 0xE0920)); }


extern void* libugmath_dev_tol_instance;
extern void* libugmath_dev_acom_instance;

extern "C" void b05_get_state(unsigned char* dst);
extern "C" void b05_set_state(const unsigned char* src);


double EQ_ask_number_tolerance();
double EQ_ask_length_tolerance();
double EQ_ask_length_squared_tolerance();


void movf(const int* count, const double* src, double* dst);


void em0200(const double* a1, const double* a2, double* a3, double* a4, double* a5);
int eqz(const double* a1, const double* a2, int* a3);
void h020(const double* a1, const double* a2, const double* a3, double* a4, double* a5, int* a6);
void h0700(const double* a1, const double* a2, const double* a3, const double* a4,
           double* a5, double* a6, double* a7);
void h0710(const double* a1, const double* a2, const double* a3, double* a4);
void h0720(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);
void h0721(const double* a1, const double* a2, const double* a3, double* a4);
void h0722(const double* a1, const double* a2, const double* a3, const double* a4, int* a5, double* a6);
void h07313(const int* a1, int* a2, const double* a3, double* a4, double* a5);
void h07314(const int* a1, int* a2, const double* a3, double* a4, double* a5);
void h0732(const int* a1, const double* a2, double* a3, const double* a4, int* a5, double* a6);
void h0733();
void h0734(double* a1, int* a2);
void h0735(const double* a1, int* a2, double* a3, double* a4, int* a5);
void h0736(const double* a1, double* a2);
void h0737(const double* a1, const double* a2, int* a3, double* a4);
void h081(const double* a1, const double* a2, const double* a3, int* a4);
void h082(const double* a1, const double* a2, const double* a3, const double* a4, int* a5);
void h083(const double* a1, const double* a2, int* a3);
void h200(const double* a1, const double* a2, double* a3);
void h201(const double* a1, const double* a2, double* a3);
void h006(double* a1, const double* a2, const double* a3, const int* a4, const double* a5, int* a6, int* a7);
void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
void h016(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
void h018(double* a1, int* a2, double* a3);
void h600a(const double* a1, const double* a2, const double* a3, const double* a4, int* a5, double* a6);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h807(double* a1, double* a2, const int* a3, const int* a4, int* a5);
void m4029(double* a1, double* a2, double* a3, int* a4);
void m4045(double* a1, double* a2, int* a3, double* a4, int* a5, int* a6);
int VEC2_unitize(const Vector2* a1, double a2, double* a3, Vector2* a4);
void vunt2(const double* a1, int* a2, double* a3);


void h07362(const double* a1, const double* a2, double* a3);
void h07363(const int* a1, const int* a2, const double* a3, const double* a4,
            const double* a5, int* a6, int* a7);
void h07366(const int* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0739(const int* a1, double* a2);
void h0740(const double* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, double* a7, double* a8);
void h0741(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);
void h0747(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);
void h07600(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);
void h0742(int* a1, double* a2);
void h0745(int* a1, double* a2);
void h090(const double* a1, const double* a2, int* a3);
void h0900(const int* a1, const double* a2, const double* a3, const double* a4, double* a5);
void h0901(const int* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0902(const double* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0903(const double* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0904(const double* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0905(const double* a1, const double* a2, const double* a3, double* a4, double* a5);
void h0908(const int* a1, const double* a2, const double* a3, const double* a4, double* a5, double* a6);
void h0909(const int* a1, const double* a2, const double* a3, const double* a4, const int* a5, double* a6);


void h0901(const int* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    int n = *a1;
    double t = *a4;
    double A[24] = {0.0};
    double B[24] = {0.0};

    int filled = 0;
    if (n >= 4)
    {
        int groups = (n - 4) / 4 + 1;
        for (int k = 0; k < groups; ++k)
        {
            int j = 4 * k;
            A[j]     = a2[n + 1 + j] - t;
            A[j + 1] = a2[n + 2 + j] - t;
            A[j + 2] = a2[n + 3 + j] - t;
            A[j + 3] = a2[n + 4 + j] - t;
            B[j]     = t - a2[j + 1];
            B[j + 1] = t - a2[j + 2];
            B[j + 2] = t - a2[j + 3];
            B[j + 3] = t - a2[j + 4];
        }
        filled = 4 * groups;
    }
    for (int m = filled; m < n; ++m)
    {
        A[m] = a2[n + 1 + m] - t;
        B[m] = t - a2[m + 1];
    }

    double P[4 * 24];

    if (!(a2[n + 1] - t > t - a2[n]))
    {
        for (int j = 0; j <= n; ++j)
            for (int c = 0; c < 4; ++c) P[4 * j + c] = a3[4 * (n - j) + c];
        for (int r = 0; r < n; ++r)
        {
            for (int i = 0; i <= n - 1 - r; ++i)
            {
                double av = A[n - 1 - r - i];
                double bv = B[n - 1 - i];
                double sum = av + bv;
                __m128d va = _mm_unpacklo_pd(_mm_set_sd(av), _mm_set_sd(av));
                __m128d vb = _mm_unpacklo_pd(_mm_set_sd(bv), _mm_set_sd(bv));
                __m128d vs = _mm_unpacklo_pd(_mm_set_sd(sum), _mm_set_sd(sum));
                for (int c = 0; c < 4; c += 2)
                {
                    __m128d hi = _mm_loadu_pd(&P[4 * (i + 1) + c]);
                    __m128d lo = _mm_loadu_pd(&P[4 * i + c]);
                    _mm_storeu_pd(&P[4 * i + c], _mm_div_pd(_mm_add_pd(_mm_mul_pd(hi, va), _mm_mul_pd(lo, vb)), vs));
                }
            }
        }
    }
    else
    {
        for (int j = 0; j <= n; ++j)
            for (int c = 0; c < 4; ++c) P[4 * j + c] = a3[4 * j + c];
        for (int r = 0; r < n; ++r)
        {
            for (int i = 0; i <= n - 1 - r; ++i)
            {
                double av = A[i];
                double bv = B[i + r];
                double sum = av + bv;
                __m128d va = _mm_unpacklo_pd(_mm_set_sd(av), _mm_set_sd(av));
                __m128d vb = _mm_unpacklo_pd(_mm_set_sd(bv), _mm_set_sd(bv));
                __m128d vs = _mm_unpacklo_pd(_mm_set_sd(sum), _mm_set_sd(sum));
                for (int c = 0; c < 4; c += 2)
                {
                    __m128d hi = _mm_loadu_pd(&P[4 * (i + 1) + c]);
                    __m128d lo = _mm_loadu_pd(&P[4 * i + c]);
                    _mm_storeu_pd(&P[4 * i + c], _mm_div_pd(_mm_add_pd(_mm_mul_pd(hi, vb), _mm_mul_pd(lo, va)), vs));
                }
            }
        }
    }
    for (int c = 0; c < 4; ++c) a5[c] = P[c];
}
