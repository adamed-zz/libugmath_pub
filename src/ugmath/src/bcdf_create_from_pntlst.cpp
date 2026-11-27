

















#include <intrin.h>

struct PNTLST_s;



struct BCDF_s
{
    PNTLST_s* df_points;
    PNTLST_s* weights;
    PNTLST_s* params;
    PNTLST_s* slopes;
    PNTLST_s* slope_pos;
    PNTLST_s* crvatrs;
    PNTLST_s* crvatr_pars;
    PNTLST_s* crvatr_derivs;
    PNTLST_s* crvatr_deriv_pars;
    int*      slope_types;
    int*      crvatr_types;
    int*      crvatr_deriv_types;
    double    tolerance;
    int       pad_68;
    int       order;
    int       periodicity;
    char      pad_74[0x0C];
    int*      constraint_types;
};



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) __declspec(noreturn) void ERROR_raise(const char* a1, int a2, int a3, const char* a4, ...);


extern "C" BCDF_s* sub_180015B80(void);
void BCDF_add_params(BCDF_s* a1, double* a2);
void BCDF_add_weights(BCDF_s* a1);

BCDF_s* __cdecl BCDF_create_from_pntlst(
    int a1, int a2, int a3,
    PNTLST_s* a4, PNTLST_s* a5, PNTLST_s* a6, PNTLST_s* a7, PNTLST_s* a8,
    int* a9, PNTLST_s* a10, PNTLST_s* a11, int* a12,
    PNTLST_s* a13, PNTLST_s* a14, int* a15, int* a16, double a17)
{
    if (MACH__checking_level > 0)
    {
        if (!a4)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
                        1922, 1005304, "The Point List Is NULL");
            __debugbreak();
        }
        if (a7 && !a8)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
                        1925, 1005306, "Slope Position Array Is NULL");
            __debugbreak();
        }
    }

    BCDF_s* v21 = sub_180015B80();
    v21->df_points = a4;
    v21->weights = a6;
    v21->order = a2;
    v21->periodicity = a1;
    v21->params = a5;
    v21->slopes = a7;
    v21->slope_pos = a8;
    v21->slope_types = a9;
    v21->crvatrs = a10;
    v21->crvatr_pars = a11;
    v21->crvatr_types = a12;
    v21->crvatr_derivs = a13;
    v21->crvatr_deriv_pars = a14;
    v21->crvatr_deriv_types = a15;

    if (!a5)
        BCDF_add_params(v21, 0);

    int* v22;
    if (a3 == 1)
    {
        if (!a6)
        {
            BCDF_add_weights(v21);
            v22 = a16;
            v21->tolerance = a17;
        }
        else
        {
            v22 = a16;
            v21->tolerance = a17;
            v21->weights = a6;
        }
    }
    else
    {
        v22 = 0;
        v21->weights = 0;
    }
    v21->constraint_types = v22;
    return v21;
}
