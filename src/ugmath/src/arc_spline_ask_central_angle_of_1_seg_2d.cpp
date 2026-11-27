



























struct ARC_SPLINE_1_seg_2d_s
{
    int    field_00;
    int    nsegs;
    double field_08;
    double field_10;
    double start;
    double end;
};




#ifdef ARC_SELFCHECK_STUBS

extern int MACH__checking_level;
void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);
#endif



double ARC_SPLINE_ask_central_angle_of_1_seg_2d(ARC_SPLINE_1_seg_2d_s* segment_ptr);





#define MACH_ASSERT(expr)                                     \
    if (MACH__checking_level && !(expr))                      \
        ERROR_assertion_failed(__FILE__, __LINE__, "%s", #expr)

double ARC_SPLINE_ask_central_angle_of_1_seg_2d(ARC_SPLINE_1_seg_2d_s* segment_ptr)
{
#line 6051 "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c"
    MACH_ASSERT(segment_ptr);
#line 28 "arc_spline_ask_central_angle_of_1_seg_2d_reimpl"

    double result = (segment_ptr->end - segment_ptr->start) * (double)segment_ptr->nsegs;
    if (result < 0.0)
    {
        result = result + 360.0;
        segment_ptr->end = (double)segment_ptr->nsegs * result + segment_ptr->start;
    }
    return result;
}
