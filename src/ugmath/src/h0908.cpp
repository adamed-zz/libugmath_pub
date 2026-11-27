











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


static const int kMaxN = 31;

void h0908(const int* a1, const double* a2, const double* a3, const double* a4, double* a5, double* a6)
{
    int n = *a1;
    if (n == 2) { h0902(a2 + 2, a3, a4, a5, a6); return; }
    if (n == 3) { h0903(a2 + 3, a3, a4, a5, a6); return; }
    if (n == 4) { h0904(a2 + 4, a3, a4, a5, a6); return; }
    if (n == 5) { h0905(a2 + 5, a3, a4, a5, a6); return; }

    double buf[4 * (kMaxN + 1)];
    int m = n > kMaxN ? kMaxN : n;
    if (m < 0) m = 0;
    double t = *a4;
    double t0 = a2[n];
    double t1 = a2[n + 1];
    double num = t - t0;
    double s = num / (t1 - t0);

    if (!(t1 - s > s - t0))
    {
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k < 4; ++k) buf[4 * j + k] = a3[4 * (m - j) + k];
        for (int r = 0; r < m; ++r)
            for (int i = 0; i < m - r; ++i)
                for (int k = 0; k < 4; ++k)
                    buf[4 * i + k] = (buf[4 * i + k] - buf[4 * i + 4 + k]) * s + buf[4 * i + 4 + k];
        for (int k = 0; k < 4; ++k) a5[k] = buf[k];
        double d = num / (double)m;
        for (int k = 0; k < 4; ++k) a6[k] = (buf[k] - buf[4 + k]) / d;
    }
    else
    {
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k < 4; ++k) buf[4 * j + k] = a3[4 * j + k];
        for (int r = 0; r < m; ++r)
            for (int i = 0; i < m - r; ++i)
                for (int k = 0; k < 4; ++k)
                    buf[4 * i + k] = (buf[4 * i + 4 + k] - buf[4 * i + k]) * s + buf[4 * i + k];
        for (int k = 0; k < 4; ++k) a5[k] = buf[k];
        double d = (t1 - t) / (double)m;
        for (int k = 0; k < 4; ++k) a6[k] = (buf[4 + k] - buf[k]) / d;
    }
}
