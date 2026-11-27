
































#include <intrin.h>

struct BCDF_s
{
    void* unk_00;
    void* unk_08;
};

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);

int BCDF_return_order(struct BCDF_s* a1);
int BCDF_return_num_of_slopes(struct BCDF_s* a1);
int BCDF_return_num_of_crvatrs(struct BCDF_s* a1);
int* BCDF_return_constraint_type_array(struct BCDF_s* a1, int* count);

int BCDF_ask_min_npoles_for_fit(struct BCDF_s* a1)
{
    int v3 = BCDF_return_order(a1);
    int v2 = 0;
    if (MACH__checking_level > 0 && !a1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    if (a1->unk_08)
    {
        int v4 = BCDF_return_num_of_slopes(a1);
        int v6 = BCDF_return_num_of_crvatrs(a1);
        int v23 = 0;
        int* v7 = BCDF_return_constraint_type_array(a1, &v23);
        if (v7)
        {
            int i = 0;
            if (v23 > 0)
            {
                for (; i < v23; ++i)
                {
                    if (v7[i] == 1)
                        ++v2;
                }
            }
        }
        if (v2 < 2)
            v2 = 2;
        int v21 = v4 + v2 + v6;
        if (v21 < v3)
            v21 = v3;
        v2 = v21;
    }
    return v2;
}
