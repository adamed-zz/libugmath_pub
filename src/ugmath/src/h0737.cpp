










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


void h0737(const double* a1, const double* a2, int* a3, double* a4)
{
    double v18, v7, v8, v10, v14, v15, v16, v17, v19, v20, v21, v22[1];
    int v9, v11, v13, v23, v24;
    *a3 = 0;
    v7 = a1[1];
    v8 = a1[2];
    v9 = 1;
    v18 = 0.0;
    v10 = *a1;
    v24 = 0;
    for (;;)
    {
        v14 = v10;
        h805(&v14, &v18, &v24, &v23);
        if (v23 == 1)
        {
            v17 = GB(0xE0920);
            v16 = GB(0xE0940);
            v15 = v8 * v8 * GB(0xE0930) / (v7 * v7)
                + GB(0xE0960)
                - v8 * GB(0xE0950) / v7;
            h020(&v17, &v16, &v15, &v21, v22, &v23);
            v11 = v23;
            if (v23)
            {
                a4[2 * *a3] = v21;
                a4[2 * (*a3)++ + 1] = -v8 / v7;
                v11 = v23;
            }
            if (v11 == 2)
            {
                a4[2 * *a3] = v22[0];
                a4[2 * *a3 + 1] = -v8 / v7;
                ++*a3;
            }
        }
        else
        {
            double v12 = v14;
            v17 = v7 * GB(0xE0920) * v7 / (v12 * v12) + GB(0xE0930);
            v16 = GB(0xE0920) * 2.0 * v7 * v8 / (v12 * v12)
                - v7 * GB(0xE0940) / v14 + GB(0xE0950);
            v15 = v8 * GB(0xE0920) * v8 / (v12 * v12)
                - v8 * GB(0xE0940) / v14 + GB(0xE0960);
            h020(&v17, &v16, &v15, &v19, &v20, &v23);
            v13 = v23;
            if (v23)
            {
                a4[2 * *a3] = -(v19 * v7 + v8) / v14;
                a4[2 * (*a3)++ + 1] = v19;
                v13 = v23;
            }
            if (v13 == 2)
            {
                a4[2 * *a3] = -(v20 * v7 + v8) / v14;
                a4[2 * *a3 + 1] = v20;
                ++*a3;
            }
        }
        if (v9 == 2) break;
        v10 = *a2;
        v9 = 2;
        v7 = a2[1];
        v8 = a2[2];
    }
}
