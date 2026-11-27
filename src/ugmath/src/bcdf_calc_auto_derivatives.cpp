







struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
int BCDF_return_num_of_points(struct BCDF_s*);
int BCDF_return_periodicity(struct BCDF_s*);

extern "C" {
void sub_180012B30(struct BCDF_s*, int, double*);
void sub_1800131F0(struct BCDF_s*, int, int, double*);
void sub_1800134C0(struct BCDF_s*, int, double*);
void sub_1800137C0(struct BCDF_s*, int, double*);
}

void BCDF_CALC_auto_derivatives(struct BCDF_s* a, int pos, int a3, double* out)
{
    int n = BCDF_return_num_of_points(a);
    int v6 = n - 1;
    if (MACH__checking_level > 0 && (pos > v6 || pos < 0))
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c",
                    145, 1005315,
                    "An Invalid Point Position Was Given By Calling Routine");
        __debugbreak();
        __assume(0);
    }
    if (pos == 0)
    {
        if ((unsigned int)BCDF_return_periodicity(a) == 1)
            sub_1800134C0(a, a3, out);
        else
            sub_1800137C0(a, a3, out);
    }
    else if (pos == v6)
    {
        sub_180012B30(a, a3, out);
    }
    else
    {
        sub_1800131F0(a, pos, a3, out);
    }
}
