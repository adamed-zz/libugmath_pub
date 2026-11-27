















#include <cmath>
#include <xmmintrin.h>
#include <emmintrin.h>



namespace UGS
{
namespace Math
{
struct Point3
{
    double x, y, z;
};
struct Vector3
{
    double x, y, z;
};
}
}


struct ARC_SPLINE_monge_plane_s
{
    UGS::Math::Vector3 pm;
    double             d;
    unsigned char   flag;
};


void ARC_SPLINE_inter_2_monge_planes(ARC_SPLINE_monge_plane_s* a1,
                                     ARC_SPLINE_monge_plane_s* a2,
                                     double* a3,
                                     UGS::Math::Point3* a4,
                                     UGS::Math::Vector3* a5,
                                     int* a6);


void ARC_SPLINE_ask_pt_and_normal_of_monge_plane(ARC_SPLINE_monge_plane_s* a1,
                                                 UGS::Math::Point3* a2,
                                                 UGS::Math::Vector3* a3);


void ARC_SPLINE_inter_3_monge_planes(ARC_SPLINE_monge_plane_s* a1,
                                     ARC_SPLINE_monge_plane_s* a2,
                                     ARC_SPLINE_monge_plane_s* a3,
                                     double* a4,
                                     UGS::Math::Point3* a5,
                                     int* a6,
                                     int* a7,
                                     int* a8)
{
    a5->x = 0.0;
    a5->y = 0.0;
    a5->z = 0.0;
    *a6 = 0;
    *a7 = 0;
    *a8 = 0;


    UGS::Math::Point3 p12 = {0.0, 0.0, 0.0};
    UGS::Math::Point3 p23 = {0.0, 0.0, 0.0};
    UGS::Math::Point3 p13 = {0.0, 0.0, 0.0};
    UGS::Math::Point3 p3  = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 d12 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 d23 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 d13 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 n3  = {0.0, 0.0, 0.0};

    ARC_SPLINE_inter_2_monge_planes(a1, a2, a4, &p12, &d12, a6);
    ARC_SPLINE_inter_2_monge_planes(a2, a3, a4, &p23, &d23, a7);
    ARC_SPLINE_inter_2_monge_planes(a1, a3, a4, &p13, &d13, a8);

    if (*a6 == 0 && *a7 == 0 && *a8 == 0)
    {
        ARC_SPLINE_ask_pt_and_normal_of_monge_plane(a3, &p3, &n3);


        double v17 = (p12.y - p3.y) * n3.y + (p12.x - p3.x) * n3.x + (p12.z - p3.z) * n3.z;
        double v18 = n3.y * d12.y + n3.x * d12.x + n3.z * d12.z;


        if (cos((90.0 - a4[1]) * 0.01745329251994328) >= fabs(v18))
        {

            if (a4[0] >= fabs(v17))
            {
                a5->x = p12.x;
                a5->y = p12.y;
                a5->z = p12.z;
            }
            else
            {
                *a7 = 1;
                *a8 = 1;
            }
        }
        else
        {
            double v19 = -v17 / v18;



            a5->x = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&d12.x), _mm_set_sd(v19)), _mm_load_sd(&p12.x)));
            a5->y = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&d12.y), _mm_set_sd(v19)), _mm_load_sd(&p12.y)));
            a5->z = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_load_sd(&d12.z), _mm_set_sd(v19)), _mm_load_sd(&p12.z)));
        }
    }
}
