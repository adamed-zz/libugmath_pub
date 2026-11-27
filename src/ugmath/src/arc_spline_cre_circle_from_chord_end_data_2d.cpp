


















#include <cmath>
#include <cstdint>
#include <emmintrin.h>

namespace UGS {
namespace Math {
struct alignas(16) Point2 { double x, y; };
struct alignas(16) Vector2 { double x, y; };
}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;

struct ARC_SPLINE_1_seg_2d_s {
    int    tag;
    int    sense;
    double base_x;
    double base_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double d38;
    double d40;
    double radius1;
    double radius2;
};



__declspec(noinline) int VEC2_unitize(const Vector2* u, double tol,
                                      double* len_out, Vector2* out);
__declspec(noinline) void ARC_SPLINE_inter_line_line_2d(
    const double* const tol, const Point2* p1, const Point2* p2, int unitized,
    Vector2* d1, Vector2* d2, Point2* out_pt, double* params, double* dot,
    int* status);
__declspec(noinline) void h053(const double* y, const double* x, double* ang);
__declspec(noinline) double
ARC_SPLINE_ask_inclination_angle_from_tan_2d(const Vector2* v);


static_assert(std::bit_cast<std::uint64_t>(57.29577951308235)
                  == 0x404CA5DC1A63C1FCull,
              "rad2deg constant must match raw bit pattern");

void ARC_SPLINE_cre_circle_from_chord_end_data_2d(
    const Point2* p1, const Vector2* t1, const Point2* p2, const Vector2* t2,
    int sense, double* tol, ARC_SPLINE_1_seg_2d_s* seg, int* status)
{
    Point2 X = {0.0, 0.0};
    const double tolv = *tol;


    unsigned long long* q = reinterpret_cast<unsigned long long*>(seg);
    for (int i = 0; i < 11; ++i) q[i] = 0;
    *status = 0;

    const __m128d tv = _mm_set1_pd(tolv);

    int abssense = sense;
    if (abssense < 0) abssense = -abssense;
    if (abssense != 1)
    {
        *status = 1;
        return;
    }

    double start_deg;
    double end_deg;
    __m128d cv;
    double cy;
    __m128d radv;

    if (tolv > 1.0e-10)
    {

        double tx;
        double ta;
        double ang = 0.0;
        tx = t1->x;
        ta = t1->y;
        h053(&ta, &tx, &ang);
        start_deg = ang * 57.29577951308235;
        tx = t2->x;
        ta = t2->y;
        h053(&ta, &tx, &ang);
        end_deg = ang * 57.29577951308235;

        Vector2 c;
        c.x = -t1->y;
        c.y = t1->x;
        if (sense == -1)
        {
            c.x = -c.x;
            c.y = -c.y;
        }
        cv = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&c.x), tv),
                        _mm_loadu_pd(&p1->x));
        cy = _mm_cvtsd_f64(_mm_unpackhi_pd(cv, cv));
        radv = _mm_set_sd(tolv);
    }
    else
    {

        const __m128d c5 = _mm_set1_pd(0.5);
        Vector2 chord;
        chord.y = p2->y - p1->y;



        __m128d sum = _mm_unpacklo_pd(
            _mm_add_sd(_mm_load_sd(&p2->x), _mm_load_sd(&p1->x)),
            _mm_add_sd(_mm_load_sd(&p2->y), _mm_load_sd(&p1->y)));
        __m128d midv = _mm_mul_pd(c5, sum);
        chord.x = p2->x - p1->x;
        Point2 mid;
        mid.x = _mm_cvtsd_f64(midv);
        mid.y = _mm_cvtsd_f64(_mm_unpackhi_pd(midv, midv));

        Vector2 uchord = {0.0, 0.0};
        double clen = 0.0;
        VEC2_unitize(&chord, 1.0e-10, &clen, &uchord);
        if (1.0e-10 > clen)
        {
            *status = 2;
            return;
        }

        double d1x = -t1->y;
        double d1y = t1->x;
        double d2x = -uchord.y;
        double d2y = uchord.x;
        if (sense == -1)
        {
            d1x = -d1x;
            d1y = -d1y;
            d2x = -d2x;
            d2y = -d2y;
        }
        Vector2 d1 = {d1x, d1y};
        Vector2 d2 = {d2x, d2y};

        const double itol[2] = {1.0e-10, 0.005};
        double params[2] = {0.0, 0.0};
        double dot = 0.0;
        int st = 0;
        ARC_SPLINE_inter_line_line_2d(itol, p1, &mid, 1, &d1, &d2, &X,
                                      params, &dot, &st);
        if (st != 0)
        {
            *status = 3;
            return;
        }

        *tol = fabs(params[0]);
        Vector2 u;
        u.x = X.x - p2->x;
        u.y = X.y - p2->y;
        double ulen = 0.0;
        VEC2_unitize(&u, 1.0e-10, &ulen, &u);

        start_deg = ARC_SPLINE_ask_inclination_angle_from_tan_2d(t1);

        double xp = -u.y;
        double yq = u.x;
        if (sense == 1)
        {
            xp = -xp;
            yq = -yq;
        }
        double radang = 0.0;
        h053(&yq, &xp, &radang);
        end_deg = radang * 57.29577951308235;

        cv = _mm_loadu_pd(&X.x);
        cy = X.y;
        radv = _mm_set_sd(fabs(params[0]));
    }

    const __m128d radb = _mm_unpacklo_pd(radv, radv);
    if (sense == 1)
    {
        if (start_deg > end_deg) end_deg += 360.0;
    }
    else if (sense == -1)
    {
        if (end_deg > start_deg) end_deg += -360.0;
    }

    seg->tag = 1;
    seg->sense = sense;
    seg->base_x = p1->x;
    seg->base_y = p1->y;
    seg->start = start_deg;
    seg->end = end_deg;
    seg->center_x = _mm_cvtsd_f64(cv);
    seg->center_y = cy;
    seg->d38 = 0.0;
    seg->d40 = 0.0;
    _mm_storeu_pd(&seg->radius1, radb);
}
