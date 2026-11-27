














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
    PNTLST_s* points;
    void*     field_08;
    char      pad_10[0x60];
    int       periodic;
    char      pad_74[0x18];
    int       field_8C;
};


extern __declspec(dllimport) int MACH__checking_level;
extern __declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line, const char* msg, ...);


void PNTLST_copy_single_point(PNTLST_s* list, int pos, double* dst);
void PNTLST_concat_one_point(PNTLST_s* list, double* pt);
void PNTLST_remove_points(PNTLST_s* list, int start, int num);
void BCDF_add_params(BCDF_s* a1, double* params);

void BCDF_toggle_periodicity(BCDF_s* a1)
{
    if (a1->field_8C <= 1 && MACH__checking_level > 0 && a1->field_08 != 0 && a1->periodic == 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 2177,
                       "Periodic Least Squares Curves Are Not Allowed");
        __debugbreak();
    }

    PNTLST_s* list = a1->points;
    if (a1->periodic == 0)
    {
        double v5[3];
        PNTLST_copy_single_point(list, 0, v5);
        PNTLST_concat_one_point(list, v5);
        BCDF_add_params(a1, 0);
        a1->periodic = 1;
    }
    else
    {
        PNTLST_remove_points(list, list->num - 1, 1);
        BCDF_add_params(a1, 0);
        a1->periodic = 0;
    }
}
