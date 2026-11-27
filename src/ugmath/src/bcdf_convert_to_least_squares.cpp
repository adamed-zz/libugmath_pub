










#include <intrin.h>

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

struct BCDF_s
{
    PNTLST_s* pts;
    void*     field_08;
    char      pad_10[0x50];
    double    tolerance;
    int       field_68;
    char      pad_6C[0x04];
    int       periodicity;
    char      pad_74[0x18];
    int       field_8c;
};




#ifdef BCDF_SMOKE

extern int MACH__checking_level;
void ERROR_internal(const char* file, int line, const char* msg, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line,
                                          const char* msg, ...);
#endif


void BCDF_convert_4d_to_3d(BCDF_s* a);
void BCDF_add_params(BCDF_s* a, double* params);
void BCDF_add_weights(BCDF_s* a);
void BCDF_remove_interior_slopes(BCDF_s* a);
void BCDF_make_least_squares_slopes(BCDF_s* a);
int  BCDF_return_num_of_crvatrs(BCDF_s* a);
void BCDF_remove_curvatures(BCDF_s* a, int start, int count);

void BCDF_convert_to_least_squares(BCDF_s* a, double tol)
{
    if (MACH__checking_level > 0 && !a)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    if (!a->field_08)
    {
        int dim = a->pts->dim;
        if (dim == 4)
        {
            BCDF_convert_4d_to_3d(a);
            BCDF_add_params(a, 0);
        }
        else if (MACH__checking_level > 0 && dim != 3)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3327,
                           "Points Are An Invalid Dimension");
            __debugbreak();
            __assume(0);
        }
        BCDF_add_weights(a);
        if (a->field_8c == 0)
        {
            BCDF_make_least_squares_slopes(a);
            int nc = BCDF_return_num_of_crvatrs(a);
            BCDF_remove_curvatures(a, 0, nc);
        }
        else
        {
            BCDF_remove_interior_slopes(a);
        }
        if (a->field_8c < 2)
        {
            a->tolerance = tol;
            a->field_68 = 0;
            a->periodicity = 0;
        }
    }
}
