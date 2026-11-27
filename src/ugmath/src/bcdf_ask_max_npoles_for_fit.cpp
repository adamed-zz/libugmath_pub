

























#include <intrin.h>

struct BCDF_s
{
    void* unk_00;
    void* unk_08;
};

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);

int BCDF_return_num_of_points(struct BCDF_s* a1);
int BCDF_return_num_of_slopes(struct BCDF_s* a1);
int BCDF_return_periodicity(struct BCDF_s* a1);

int BCDF_ask_max_npoles_for_fit(struct BCDF_s* a1)
{
    int v1 = 0;
    if (MACH__checking_level > 0 && !a1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    if (a1->unk_08)
    {
        v1 = BCDF_return_num_of_points(a1);
        BCDF_return_num_of_slopes(a1);
        if (static_cast<unsigned int>(BCDF_return_periodicity(a1)) == 1)
            --v1;
    }
    return v1;
}
