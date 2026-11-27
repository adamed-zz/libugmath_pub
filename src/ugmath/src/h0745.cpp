









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


void h0745(int* a1, double* a2)
{
    double vv[3] = {0.0, 0.0, 0.0};
    double v21[3] = {0.0, 0.0, 0.0};
    double v20[3] = {0.0, 0.0, 0.0};
    int v28 = 0, v29 = 0;
    double v3 = GB(0xE0A00);
    double v5 = GB(0xE0A08);
    double v6 = GB(0xE09F0);
    double v7 = GB(0xE09F8);
    v21[0] = GB(0xE0A10) - GB(0xE09F0);
    v21[1] = GB(0xE0A18) - GB(0xE09F8);
    vunt2(v21, &v28, v21);
    vv[0] = v3 - v6;
    vv[1] = v5 - v7;
    vunt2(vv, &v28, vv);
    h090(v21, vv, &v28);
    double v8 = GB(0xE0A20);
    double v9 = GB(0xE0A28);
    double v10 = GB(0xE0A30);
    double v11 = GB(0xE0A38);
    v20[0] = GB(0xE0A40) - GB(0xE0A20);
    v20[1] = GB(0xE0A48) - GB(0xE0A28);
    vunt2(v20, &v29, v20);
    vv[0] = v10 - v8;
    vv[1] = v11 - v9;
    vunt2(vv, &v29, vv);
    h090(v20, vv, &v29);
    if (v28 == 2)
    {
        if (v29 == 2) { *a1 = 4; return; }
        if (v29 == 1)
        {
            *a1 = 1;
            em0200(&GB(0xE0A20), &GB(0xE0A40), a2, a2 + 1, a2 + 2);
            return;
        }
    }
    else if (v28 == 1 && v29 == 2)
    {
        *a1 = 2;
        em0200(&GB(0xE09F0), &GB(0xE0A10), a2, a2 + 1, a2 + 2);
        return;
    }
    h090(v21, v20, &v28);
    if (v28 != 2)
    {
        double v22, v23, v24;
        em0200(&GB(0xE09F0), &GB(0xE0A10), &v22, &v23, &v24);
        double v14 = v22 * GB(0xE0A20) + v23 * GB(0xE0A28) + v24;
        int v18[2];
        v18[1] = 0;
        double v25 = 0.0;
        h805(&v14, &v25, &v18[1], &v28);
        if (v28)
        {
            m4029(&GB(0xE0A20), &GB(0xE09F0), &GB(0xE0A10), &v28);
            m4029(&GB(0xE0A40), &GB(0xE09F0), &GB(0xE0A10), &v29);
            int v13;
            if (v28 == 1) v13 = (v29 == 1);
            else
            {
                if (v28 != 5) { *a1 = -1; return; }
                v13 = (v29 == 5);
            }
            if (!v13) { *a1 = -1; return; }
        }
        *a1 = 0;
        return;
    }
    *a1 = 3;
    {
        double v27[9] = {0.0};
        double v26[9] = {0.0};
        v27[0] = GB(0xE09F0);
        v27[1] = GB(0xE09F8);
        v27[3] = GB(0xE0A10);
        v27[4] = GB(0xE0A18);
        v26[0] = GB(0xE0A20);
        v26[1] = GB(0xE0A28);
        v26[3] = GB(0xE0A40);
        v26[4] = GB(0xE0A48);
        double v15;
        int v18b[2];
        v18b[0] = 0;
        v18b[1] = 0;
        m4045(v27, v26, v18b, &v15, &v28, &v29);
        if (v18b[0] == 1) { *a1 = 0; return; }
        if (((v28 - 1) & 0xFFFFFFFB) == 0) { *a1 = 0; return; }
        if (((v29 - 1) & 0xFFFFFFFB) == 0) { *a1 = 0; return; }
        double v19, v14;
        switch (v28)
        {
        case 2: *a2 = 0.0; break;
        case 4: *a2 = 1.0; break;
        case 3:
            h201(&GB(0xE09F0), &GB(0xE0A10), &v19);
            h201(&GB(0xE09F0), &v15, &v14);
            *a2 = v14 / v19;
            break;
        }
        switch (v29)
        {
        case 2: a2[1] = 0.0; break;
        case 4: a2[1] = 1.0; break;
        case 3:
            h201(&GB(0xE0A20), &GB(0xE0A40), &v19);
            h201(&GB(0xE0A20), &v15, &v14);
            a2[1] = v14 / v19;
            break;
        }
    }
    *a1 = 0;
}
