










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


void h0905(const double* a1, const double* a2, const double* a3, double* a4, double* a5)
{
    double t0 = *a1;
    double t1 = a1[1];
    double t = (*a3 - t0) / (t1 - t0);
    double q0[4], q1[4], q2[4], q3[4], q4[4];
    double r0[4], r1[4], r2[4], r3[4];
    double s0[4], s1[4], s2[4];
    double u0[4], u1[4];
    for (int k = 0; k < 4; ++k)
    {
        q0[k] = (a2[4 + k] - a2[k]) * t + a2[k];
        q1[k] = (a2[8 + k] - a2[4 + k]) * t + a2[4 + k];
        q2[k] = (a2[12 + k] - a2[8 + k]) * t + a2[8 + k];
        q3[k] = (a2[16 + k] - a2[12 + k]) * t + a2[12 + k];
        q4[k] = (a2[20 + k] - a2[16 + k]) * t + a2[16 + k];
    }
    for (int k = 0; k < 4; ++k)
    {
        r0[k] = (q1[k] - q0[k]) * t + q0[k];
        r1[k] = (q2[k] - q1[k]) * t + q1[k];
        r2[k] = (q3[k] - q2[k]) * t + q2[k];
        r3[k] = (q4[k] - q3[k]) * t + q3[k];
    }
    for (int k = 0; k < 4; ++k)
    {
        s0[k] = (r1[k] - r0[k]) * t + r0[k];
        s1[k] = (r2[k] - r1[k]) * t + r1[k];
        s2[k] = (r3[k] - r2[k]) * t + r2[k];
    }
    for (int k = 0; k < 4; ++k)
    {
        u0[k] = (s1[k] - s0[k]) * t + s0[k];
        u1[k] = (s2[k] - s1[k]) * t + s1[k];
    }
    for (int k = 0; k < 4; ++k) a4[k] = (u1[k] - u0[k]) * t + u0[k];
    if (t1 - *a3 <= *a3 - t0)
    {
        double s = 5.0 / (*a3 - t0);
        for (int k = 0; k < 4; ++k) a5[k] = (a4[k] - u0[k]) * s;
    }
    else
    {
        double s = 5.0 / (t1 - *a3);
        for (int k = 0; k < 4; ++k) a5[k] = (u1[k] - a4[k]) * s;
    }
}
