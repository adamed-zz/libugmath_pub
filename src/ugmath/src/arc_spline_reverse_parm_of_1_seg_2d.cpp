







#include <intrin.h>

struct ARC_SPLINE_1_seg_2d_s;


void ARC_SPLINE_reverse_parm_of_arc_2d(struct ARC_SPLINE_1_seg_2d_s*);
void ARC_SPLINE_reverse_parm_of_strt_2d(struct ARC_SPLINE_1_seg_2d_s*);


__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

void ARC_SPLINE_reverse_parm_of_1_seg_2d(struct ARC_SPLINE_1_seg_2d_s* a1)
{
    unsigned int v1 = *(unsigned int*)a1;
    if (v1 == 0)
    {
        ARC_SPLINE_reverse_parm_of_strt_2d(a1);
    }
    else if (v1 == 1)
    {
        ARC_SPLINE_reverse_parm_of_arc_2d(a1);
    }
    else
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            14323,
            "This segment type is not currently handled.");
        __debugbreak();
        __assume(0);
    }
}
