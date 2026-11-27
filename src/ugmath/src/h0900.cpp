












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


void h0900(const int* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    unsigned n = *(const unsigned*)a1;
    int m = (int)n;
    double t = *a4;
    double t0 = a2[m];
    double t1 = a2[m + 1];
    double s = (t - t0) / (t1 - t0);

    switch (m)
    {
    case 2:
    {
        double d0[4], d1[4], tmp[4];
        for (int c = 0; c < 4; ++c)
        {
            d0[c] = a3[4 + c] - a3[c];
            d1[c] = a3[8 + c] - a3[4 + c];
        }
        for (int c = 0; c < 4; ++c) tmp[c] = (d1[c] - d0[c]) * s + d0[c];
        a5[0] = (tmp[0] + d0[0]) * s + a3[0];
        a5[1] = (d0[1] + tmp[1]) * s + a3[1];
        a5[2] = (d0[2] + tmp[2]) * s + a3[2];
        a5[3] = (d0[3] + tmp[3]) * s + a3[3];
        break;
    }
    case 3:
    {
        double s3 = s * s * s;
        double b2 = s * s + s * s + s * s - s3;
        double b1 = s + s + s - b2;
        double b2b = b2 - s3;
        for (int c = 0; c < 4; ++c)
        {
            double d0 = a3[4 + c] - a3[c];
            double d1 = a3[8 + c] - a3[4 + c];
            double d2 = a3[12 + c] - a3[8 + c];
            a5[c] = d0 * b1 + a3[c] + d1 * b2b + d2 * s3;
        }
        break;
    }
    case 4:
    {
        double scratch[4];
        h0904(a2 + 4, a3, a4, a5, scratch);
        break;
    }
    case 5:
    {
        double scratch[4];
        h0905(a2 + 5, a3, a4, a5, scratch);
        break;
    }
    default:
    {
        double buf[4 * 32];

        if (!(t1 - s > s - t0))
        {
            for (int j = 0; j <= m; ++j)
                for (int c = 0; c < 4; ++c) buf[4 * j + c] = a3[4 * (m - j) + c];
            for (int r = m; r >= 1; --r)
                for (int i = 0; i < r; ++i)
                    for (int c = 0; c < 4; ++c)
                        buf[4 * i + c] = (buf[4 * i + c] - buf[4 * i + 4 + c]) * s + buf[4 * i + 4 + c];
        }
        else
        {
            for (int j = 0; j <= m; ++j)
                for (int c = 0; c < 4; ++c) buf[4 * j + c] = a3[4 * j + c];
            for (int r = m; r >= 1; --r)
                for (int i = 0; i < r; ++i)
                    for (int c = 0; c < 4; ++c)
                        buf[4 * i + c] = (buf[4 * i + 4 + c] - buf[4 * i + c]) * s + buf[4 * i + c];
        }
        for (int c = 0; c < 4; ++c) a5[c] = buf[c];
        break;
    }
    }
}
