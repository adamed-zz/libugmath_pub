













#include <cstddef>
#include <cmath>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);

extern double qword_1800E07C0;
extern double qword_1800E07A8;
extern double qword_1800E07B0;
extern double qword_1800E07B8;
extern __int64 qword_1800E0868;
extern double qword_1800E0880;
extern double qword_1800E0888;
extern __int64 qword_1800E0918;
extern int dword_1800E0910;
extern void (*qword_1800E08D8)(int, int, const char*);
extern const char byte_1800BAD62;

double qword_1800E07C0;
double qword_1800E07A8;
double qword_1800E07B0;
double qword_1800E07B8;
__int64 qword_1800E0868;
double qword_1800E0880;
double qword_1800E0888;
__int64 qword_1800E0918;
int dword_1800E0910;
void (*qword_1800E08D8)(int, int, const char*);
const char byte_1800BAD62 = 0;

extern "C" __int64 sub_18004C8B0(__int64 a1, float* a2, float* a3)
{
    unsigned int* v6;
    __int64 result;
    __int64 v8;
    unsigned __int64* v9;
    __int64 v10;
    double v11;
    double v12;
    double v13;
    double v14;
    float v15;
    double v16;
    float v17;
    float v18;
    float v19;
    double v20;
    double v21;
    double v22;

    if (qword_1800E0868 &&
        (v6 = (unsigned int*)(qword_1800E0868 + 16),
         result = *(unsigned int*)(qword_1800E0868 + 20),
         *(int*)(qword_1800E0868 + 16) < (int)result))
    {
        v8 = qword_1800E0918;
    }
    else
    {
        v9 = (unsigned __int64*)SM_alloc(0x18u);
        if (!v9)
            qword_1800E08D8(2, 3, &byte_1800BAD62);
        v9[1] = qword_1800E0868;
        qword_1800E0868 = (__int64)v9;
        result = (__int64)SM_alloc(0x24540u);
        v8 = result;
        if (!result)
            qword_1800E08D8(2, 3, &byte_1800BAD62);
        v10 = qword_1800E0868;
        *(unsigned __int64*)qword_1800E0868 = (unsigned __int64)v8;
        *(unsigned int*)(v10 + 20) = 3100;
        v6 = (unsigned int*)(v10 + 16);
        *v6 = 0;
    }
    v11 = qword_1800E07C0;
    v12 = qword_1800E07A8;
    v13 = qword_1800E07B0;
    v14 = qword_1800E07B8;
    ++dword_1800E0910;
    v15 = (float)v11;
    *(unsigned __int64*)v8 = (unsigned __int64)a1;
    *(unsigned __int64*)(v8 + 8) = (unsigned __int64)a2;
    *(unsigned __int64*)(v8 + 16) = (unsigned __int64)a3;
    *(unsigned __int64*)(v8 + 40) = 0;
    v16 = fabs(v11) + 1.0;
    *(float*)(v8 + 36) = v15;
    v17 = (float)v12;
    v18 = (float)v13;
    *(float*)(v8 + 24) = v17;
    *(float*)(v8 + 28) = v18;
    v19 = (float)v14;
    *(float*)(v8 + 32) = v19;
    v20 = qword_1800E0880;
    {
        float f21 = (float)((float)((float)((float)(v18 * a2[1]) + (float)(v17 * *a2)) +
                                    (float)(v19 * a2[2])) -
                            v15);
        v21 = fabs((double)f21) / v16 * 1.2;
    }
    if (v21 > qword_1800E0880)
    {
        qword_1800E0880 = v21;
        v20 = v21;
    }
    {
        float f22 = (float)((float)((float)((float)(v18 * a3[1]) + (float)(v17 * *a3)) +
                                    (float)(v19 * a3[2])) -
                            v15);
        v22 = fabs((double)f22) / v16 * 1.2;
    }
    if (v22 > v20)
    {
        qword_1800E0880 = v22;
        v20 = v22;
    }
    ++*v6;
    qword_1800E0918 = v8 + 48;
    qword_1800E0888 = -v20;
    return result;
}
