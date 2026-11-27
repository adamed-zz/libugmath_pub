

















struct ARC_SPLINE_1_seg_2d_s {
    int    type;
    int    sense;
    double x;
    double y;
    double pad18[4];
    double dx;
    double dy;
    double parm;
};

namespace UGS {
namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
}
}


void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2& end,
                                const UGS::Math::Point2& strt,
                                const UGS::Math::Vector2& rev,
                                struct ARC_SPLINE_1_seg_2d_s* seg);

void ARC_SPLINE_reverse_parm_of_strt_2d(struct ARC_SPLINE_1_seg_2d_s* a)
{


    UGS::Math::Point2  strt;
    UGS::Math::Point2  end;
    UGS::Math::Vector2 rev;

    strt.x = a->x;
    strt.y = a->y;
    end.x = a->x + a->dx * a->parm;
    end.y = a->y + a->dy * a->parm;
    rev.x = -a->dx;
    rev.y = -a->dy;

    ARC_SPLINE_cre_strt_seg_2d(end, strt, rev, a);
}
