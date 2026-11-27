







#include <math.h>
#include <stddef.h>

namespace UGS
{
namespace Math
{

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

struct Vector2
{
    double x;
    double y;
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


void* SM_alloc(size_t size);
void SM_free(void* p);





extern "C" void sub_180055700(int n, UGS::Math::Point3* pts, UGS::Math::Point3* base,
                               UGS::Math::Vector3* dir, UGS::Math::Point2* out2d,
                               CSYS_s* csys);


double* sub_180054C60(int n, double* pts2d, double tol,
                      double* out_pt, double* out_vec, int* status);


void LSFIT_plane_to_points(int mode, UGS::Math::Point3* pts, int n,
                           UGS::Math::Point3* out_pt, UGS::Math::Vector3* out_vec,
                           int* status, double* dist);

void LSFIT_line_to_points_2d(int mode, UGS::Math::Point2* pts, int n,
                             UGS::Math::Point2* out_pt, UGS::Math::Vector2* out_vec,
                             int* status, double* dist);


void __cdecl LSFIT_line_to_points_3d(UGS::Math::Point3* pts, int n, UGS::Math::Vector3* dir,
                                     int* fit_type, int* status, UGS::Math::Point3* out_pt,
                                     UGS::Math::Vector3* out_dir, double* dev, CSYS_s* csys)
{
    *status = 0;
    out_pt->x = 0.0;
    out_pt->y = 0.0;
    out_pt->z = 0.0;
    out_dir->x = 0.0;
    out_dir->y = 0.0;
    out_dir->z = 0.0;
    dev[0] = 0.0;
    dev[1] = 0.0;
    dev[2] = 0.0;






    double plane_dist[8] = { 0.0 };
    double line_dist[8] = { 0.0 };
    UGS::Math::Point2 out2d = { 0.0, 0.0 };
    UGS::Math::Vector2 dir2d = { 0.0, 0.0 };
    UGS::Math::Vector2 fixed2d = { 0.0, 0.0 };
    UGS::Math::Point3 base = { 0.0, 0.0, 0.0 };

    double len = sqrt(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);

    if (len <= 1.0e-10 || *fit_type == -1)
    {

        LSFIT_plane_to_points(0, pts, n, &base, dir, fit_type, plane_dist);
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
        base.x = sx / (double)n;
        base.y = sy / (double)n;
        base.z = sz / (double)n;
    }

    UGS::Math::Point2* p2 = (UGS::Math::Point2*)SM_alloc((size_t)(16 * (__int64)n));
    sub_180055700(n, pts, &base, dir, p2, csys);

    if (!*fit_type)
    {
        LSFIT_line_to_points_2d(0, p2, n, &out2d, &dir2d, status, line_dist);
        fixed2d.x = dir2d.y;
        fixed2d.y = -dir2d.x;
        out_pt->x = out2d.x;
        out_pt->y = out2d.y;
        out_pt->z = 0.0;
        {
            UGS::Math::Point3 p = *out_pt;
            out_pt->x = p.x * csys->M[0] + p.y * csys->M[3] + p.z * csys->M[6] + csys->T[0];
            out_pt->y = p.x * csys->M[1] + p.y * csys->M[4] + p.z * csys->M[7] + csys->T[1];
            out_pt->z = p.x * csys->M[2] + p.y * csys->M[5] + p.z * csys->M[8] + csys->T[2];
        }
        out_dir->x = fixed2d.x;
        out_dir->y = fixed2d.y;
        out_dir->z = 0.0;
    }
    else
    {
        sub_180054C60(n, (double*)p2, 1.0e-10, (double*)&out2d, (double*)&fixed2d, status);
        if (*status == 1)
        {
            *fit_type = 1;
            *status = 1;
            goto deviations;
        }
        out_pt->x = out2d.x;
        out_pt->y = out2d.y;
        out_pt->z = 0.0;
        {
            UGS::Math::Point3 p = *out_pt;
            out_pt->x = p.x * csys->M[0] + p.y * csys->M[3] + p.z * csys->M[6] + csys->T[0];
            out_pt->y = p.x * csys->M[1] + p.y * csys->M[4] + p.z * csys->M[7] + csys->T[1];
            out_pt->z = p.x * csys->M[2] + p.y * csys->M[5] + p.z * csys->M[8] + csys->T[2];
        }
        out_dir->x = fixed2d.x;
        out_dir->y = fixed2d.y;
        out_dir->z = 0.0;
    }

    {
        UGS::Math::Vector3 d = *out_dir;
        out_dir->x = d.x * csys->M[0] + d.y * csys->M[3] + d.z * csys->M[6];
        out_dir->y = d.x * csys->M[1] + d.y * csys->M[4] + d.z * csys->M[7];
        out_dir->z = d.x * csys->M[2] + d.y * csys->M[5] + d.z * csys->M[8];
    }

deviations:
    if (n > 0)
    {
        double sum = dev[2];
        __int64 k = n;
        const UGS::Math::Point3* p = pts;
        do
        {
            double t = (p->x - out_pt->x) * out_dir->x + (p->y - out_pt->y) * out_dir->y +
                       (p->z - out_pt->z) * out_dir->z;
            double proj_x = out_pt->x + out_dir->x * t;
            double proj_y = out_pt->y + out_dir->y * t;
            double proj_z = out_pt->z + out_dir->z * t;
            double d1 = sqrt((out_pt->x - proj_x) * (out_pt->x - proj_x) +
                             (out_pt->y - proj_y) * (out_pt->y - proj_y) +
                             (out_pt->z - proj_z) * (out_pt->z - proj_z));
            double ox = out_pt->x;
            double oy = out_pt->y;
            double oz = out_pt->z;


            if (!(1.0e-10 >= d1))
            {
                ox = proj_x;
                oy = proj_y;
                oz = proj_z;
            }
            double e = sqrt((ox - p->x) * (ox - p->x) + (oy - p->y) * (oy - p->y) +
                            (oz - p->z) * (oz - p->z));
            if (e >= dev[0])
            {
                dev[0] = e;
            }
            sum += e;
            dev[2] = sum;
            ++p;
        } while (--k);
    }
    dev[2] = dev[2] / (double)n;


    dev[1] = sqrt(line_dist[1] * line_dist[1] + plane_dist[1] * plane_dist[1]);
    SM_free(p2);
}
