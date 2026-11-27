










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


void h0740(const double* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, double* a7, double* a8)
{
    double v42[4];


    double v38[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double v43[8] = {0.0};
    int v36 = 0, v35 = 0;
    h0741(a2, a3, a5, a6, v42);

    int count = (int)(long long)a8;
    h016(v42, v38, v43, &v36, &v35, &count);

    double v33 = 0.0, v34 = 0.0;
    int v12 = 0;
    int v13 = 1;
    int scanned = 0;
    if (count > 0)
    {
        long long v15 = count;
        long long v14 = 1;
        if (v15 < 4)
        {
            long long v17 = 0;
            double* v23 = &v38[2] + v17;
            long long v24 = v15 - v14 + 1;
            double* v25 = &v38[v14 - 1];
            do
            {
                double v26 = *v25;
                if (v26 >= 0.0 && v26 <= 1.0)
                {
                    ++v12;
                    ++v23;
                    *v23 = (*a4 - *a1) * v26 + *a1;
                }
                ++v25;
                --v24;
            } while (v24);
            scanned = 1;
        }
        else
        {

            long long v16 = v15 - 3;
            long long v17 = 0;
            double* v18 = &v38[2];
            do
            {
                double v19 = v38[v14 - 1];
                if (v19 >= 0.0 && v19 <= 1.0) { ++v12; ++v17; ++v18; *v18 = (*a4 - *a1) * v19 + *a1; }
                double v20 = v38[v14];
                if (v20 >= 0.0 && v20 <= 1.0) { ++v12; ++v17; ++v18; *v18 = (*a4 - *a1) * v20 + *a1; }
                double v21 = v38[v14 + 1];
                if (v21 >= 0.0 && v21 <= 1.0) { ++v12; ++v17; ++v18; *v18 = (*a4 - *a1) * v21 + *a1; }
                double v22 = v38[3 + v14 - 1];
                if (v22 >= 0.0 && v22 <= 1.0) { ++v12; ++v17; ++v18; *v18 = (*a4 - *a1) * v22 + *a1; }
                v14 += 4;
            } while (v14 <= v16);
            if (v14 <= v15)
            {
                double* v23 = &v38[2] + v17;
                long long v24 = v15 - v14 + 1;
                double* v25 = &v38[v14 - 1];
                do
                {
                    double v26 = *v25;
                    if (v26 >= 0.0 && v26 <= 1.0)
                    {
                        ++v12;
                        ++v23;
                        *v23 = (*a4 - *a1) * v26 + *a1;
                    }
                    ++v25;
                    --v24;
                } while (v24);
            }
            scanned = 1;
        }
    }
    if (!scanned) goto DEFAULT_LABEL;
    if (v12 <= 0) goto DEFAULT_LABEL;
    a7[0] = v38[3];
    h0700(a1, a2, a3, a4, (double*)a5, a7, a8);
    if (v12 > 1)
    {
        h200(a6, a8, &v33);
        long long v27 = v12;
        if (v12 >= 2)
        {
            double* v28 = &v38[4];
            long long v29 = v27 - 1;
            do
            {
                double v37[2];
                h0700(a1, a2, a3, a4, (double*)a5, &v38[3] + v13, v37);
                h200(a6, v37, &v34);
                double v30 = v34;
                if (v33 > v34)
                {
                    a7[0] = *v28;
                    a8[0] = v37[0];
                    a8[1] = v37[1];
                    v33 = v30;
                }
                ++v13;
                ++v28;
                --v29;
            } while (v29);
        }
    }
    return;
DEFAULT_LABEL:
    h200(a2, a6, &v33);
    h200(a5, a6, &v34);
    if (!(v34 > v33))
    {
        a7[0] = a4[0];
        a8[0] = a5[0];
        a8[1] = a5[1];
    }
    else
    {
        a7[0] = a1[0];
        a8[0] = a2[0];
        a8[1] = a2[1];
    }
}
