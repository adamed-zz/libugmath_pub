









#include <math.h>
#include <stddef.h>

namespace UGS {
namespace Math {

struct Point2
{
    double x;
    double y;
};

struct Point3
{
    double x;
    double y;
    double z;
};

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}


struct CSYS_s
{
    double T[3];
    double M[9];
};


__declspec(dllimport) void* SM_alloc(size_t size);
__declspec(dllimport) void SM_free(void* p);


extern "C" void sub_180055700(int n, UGS::Math::Point3* pts, UGS::Math::Point3* center,
                              UGS::Math::Vector3* normal, UGS::Math::Point2* out2d,
                              CSYS_s* csys);



void __cdecl LSFIT_plane_to_points(int mode, UGS::Math::Point3* pts, int n,
                                   UGS::Math::Point3* out_pt, UGS::Math::Vector3* out_vec,
                                   int* status, double* dist);



void __cdecl LSFIT_circle_to_points_2d(UGS::Math::Point2* pts, int count, double tolerance,
                                       UGS::Math::Point2* result, double* radius, int* status,
                                       double* resid);


void __cdecl LSFIT_circle_to_points_3d(int a1, UGS::Math::Point3* pts, int n, double tol,
                                       UGS::Math::Point3* center, UGS::Math::Vector3* normal,
                                       UGS::Math::Point3* outpt, double* radius, int* status,
                                       double* resid, CSYS_s* csys)
{
    center->x = 0.0;
    center->y = 0.0;
    center->z = 0.0;
    outpt->x = 0.0;
    outpt->y = 0.0;
    outpt->z = 0.0;
    *radius = 1.0e19;
    *status = 0;

    double norm = sqrt(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z);
    if (norm <= 1.0e-10)
    {
        LSFIT_plane_to_points(a1, pts, n, center, normal, status, resid);
    }
    else
    {
        double sx = 0.0;
        double sy = 0.0;
        double sz = 0.0;
        if (n > 0)
        {
            __int64 k = n;
            const UGS::Math::Point3* p = pts;
            do
            {
                sx += p->x;
                sy += p->y;
                sz += p->z;
                ++p;
            } while (--k);
        }
        center->x = sx / (double)n;
        center->y = sy / (double)n;
        center->z = sz / (double)n;
    }

    if (!*status)
    {
        UGS::Math::Point2 v30;
        v30.x = 0.0;
        v30.y = 0.0;
        UGS::Math::Point2* p2 = (UGS::Math::Point2*)SM_alloc((size_t)(16 * (__int64)n));
        sub_180055700(n, pts, center, normal, p2, csys);
        LSFIT_circle_to_points_2d(p2, n, tol, &v30, radius, status, resid);
        if (!*status)
        {
            outpt->x = v30.x;
            outpt->y = v30.y;
            outpt->z = 0.0;
            UGS::Math::Point3 p = *outpt;
            outpt->x = p.x * csys->M[0] + p.y * csys->M[3] + p.z * csys->M[6] + csys->T[0];
            outpt->y = p.x * csys->M[1] + p.y * csys->M[4] + p.z * csys->M[7] + csys->T[1];
            outpt->z = p.x * csys->M[2] + p.y * csys->M[5] + p.z * csys->M[8] + csys->T[2];
        }
        if (p2)
        {
            SM_free(p2);
        }
    }
}
