









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


void h0742(int* a1, double* a2)
{
    int v14 = 0;
    int v15 = 6;
    int v16 = 1;
    int v28 = 0, v29 = 0;
    double v17, v18, v19, v21, v22 = 0.0, v25;
    double v20[2] = {0.0, 0.0};
    double v23[2] = {0.0, 0.0};
    double v24[2] = {0.0, 0.0};
    double v26[6] = {0.0};
    double v27[2] = {0.0, 0.0};
    h0745(&v28, v20);
    switch (v28)
    {
    case -1:
        *a1 = -1;
        return;
    case 0:
        *a1 = 0;
        return;
    case 3:
        *a1 = 1;
        a2[0] = v20[0];
        a2[1] = v20[1];
        return;
    case 4:
        *a1 = 3;
        v17 = GB(0xE0920) * 4.0 * GB(0xE0930) * GB(0xE0960)
            - (GB(0xE0940) * GB(0xE0930) * GB(0xE0940)
             + GB(0xE0950) * GB(0xE0920) * GB(0xE0950));
        h805(&v17, &v22, &v14, &v28);
        if (v28 == 1) { *a1 = -1; return; }
        v17 = GB(0xE0928) * 4.0 * GB(0xE0938) * GB(0xE0968)
            - (GB(0xE0948) * GB(0xE0938) * GB(0xE0948)
             + GB(0xE0958) * GB(0xE0928) * GB(0xE0958));
        h805(&v17, &v22, &v14, &v28);
        if (v28 == 1) { *a1 = -1; return; }
        break;
    default:
        h0732(&v28, v20, v20 + 1, &v21, &v29, v27);
        {
            int v6 = v29;
            *a1 = 0;
            if (v6 == -1) { *a1 = -1; return; }
            if (v6)
            {
                long long v7;
                long long v9;
                if (v28 == 1)
                {
                    movf(&v15, &GB(0xE0970), v26);
                    h201(&GB(0xE0A20), &GB(0xE0A40), &v19);
                    v7 = 1;
                    v23[0] = GB(0xE0A20); v23[1] = GB(0xE0A28);
                    v24[0] = GB(0xE0A40); v24[1] = GB(0xE0A48);
                    v9 = -1;
                }
                else
                {
                    movf(&v15, &GB(0xE09A0), v26);
                    h201(&GB(0xE09F0), &GB(0xE0A10), &v19);
                    v7 = 0;
                    v23[0] = GB(0xE09F0); v23[1] = GB(0xE09F8);
                    v24[0] = GB(0xE0A10); v24[1] = GB(0xE0A18);
                    v9 = 1;
                }
                if (v29 > 0)
                {
                    double* v10 = &a2[v7];
                    double* v11 = v27;
                    int v4 = 0;
                    do
                    {
                        double v12 = *v11;
                        ++*a1;
                        v10[v9] = v12;
                        v20[0] = v12 * v26[0] * v12 + v12 * v26[2] + v26[4];
                        v20[1] = v12 * v26[1] * v12 + v12 * v26[3] + v26[5];
                        h201(v23, v20, &v18);
                        h201(v24, v20, &v25);
                        h807(&v19, &v25, &v16, &v16, &v28);
                        double v13 = v18;
                        if (v28 == 1)
                        {
                            v13 = -v18;
                            v18 = -v18;
                        }
                        ++v4;
                        ++v11;
                        *v10 = v13 / v19;
                        v10 += 2;
                    } while (v4 < v29);
                }
            }
        }
        break;
    }
}
