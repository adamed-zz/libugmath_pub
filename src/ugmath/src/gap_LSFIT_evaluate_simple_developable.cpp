



#include <math.h>
#include <emmintrin.h>

namespace UGS {
namespace Math {

struct Vector3
{
    double x;
    double y;
    double z;
};

struct Point3
{
    double x;
    double y;
    double z;
};

}
}


struct LSFIT_simple_developable_geom_s
{
    int                type;
    UGS::Math::Point3  base;
    UGS::Math::Vector3 v;
    UGS::Math::Vector3 w;
    double             a;
    double             b;
    double             c;
    double             d;
    double             e;
    double             f;
    double             extra[3];
};



int VEC3_unitize(const UGS::Math::Vector3 *u, double tol, double *len_out,
                 UGS::Math::Vector3 *out);


__declspec(noreturn) void ERROR_internal(const char *file, int line, const char *msg);

void LSFIT_evaluate_simple_developable(
    double *uv,
    LSFIT_simple_developable_geom_s *geom,
    UGS::Math::Point3 *pt,
    UGS::Math::Vector3 *const dir,
    UGS::Math::Vector3 *normal)
{
    double len;
    UGS::Math::Vector3 bn;

    pt->x = 0.0;
    pt->y = 0.0;
    pt->z = 0.0;
    dir[0].x = 0.0;
    dir[0].y = 0.0;
    dir[0].z = 0.0;
    dir[1].x = 0.0;
    dir[1].y = 0.0;
    dir[1].z = 0.0;
    normal->x = 0.0;
    normal->y = 0.0;
    normal->z = 0.0;

    bn.x = geom->v.y * geom->w.z - geom->v.z * geom->w.y;
    bn.y = geom->v.z * geom->w.x - geom->v.x * geom->w.z;
    bn.z = geom->v.x * geom->w.y - geom->v.y * geom->w.x;
    VEC3_unitize(&bn, 1.0e-10, &len, &bn);

    if (geom->type == 2)
    {
        double u = uv[0];
        double v = uv[1];
        pt->x = geom->base.x + (u * geom->w.x + v * bn.x);
        pt->y = geom->base.y + (u * geom->w.y + v * bn.y);
        pt->z = geom->base.z + (u * geom->w.z + v * bn.z);
        dir[0] = geom->w;
        dir[1] = bn;
    }
    else if (geom->type == 3)
    {
        double R = geom->a;
        double v = uv[1];
        double cs = cos(uv[0]) * R;
        double sn = sin(uv[0]) * R;
        pt->x = geom->base.x + (cs * geom->w.x + sn * bn.x);
        pt->y = geom->base.y + (cs * geom->w.y + sn * bn.y);
        pt->z = geom->base.z + (cs * geom->w.z + sn * bn.z);
        pt->x = pt->x + v * geom->v.x;
        pt->y = pt->y + v * geom->v.y;
        pt->z = pt->z + v * geom->v.z;
        sn = sin(uv[0]) * R;
        cs = cos(uv[0]) * R;
        const __m128 kSignMask = _mm_castsi128_ps(
            _mm_set_epi64x((long long)0x8000000000000000ULL, (long long)0x8000000000000000ULL));
        __m128d snv = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(_mm_load_sd(&sn)), kSignMask));
        __m128d csv = _mm_load_sd(&cs);


        _mm_store_sd(&dir[0].x,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.x)),
                                _mm_mul_sd(_mm_load_sd(&bn.x), csv)));
        _mm_store_sd(&dir[0].y,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.y)),
                                _mm_mul_sd(_mm_load_sd(&bn.y), csv)));
        _mm_store_sd(&dir[0].z,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.z)),
                                _mm_mul_sd(_mm_load_sd(&bn.z), csv)));
        VEC3_unitize(&dir[0], 1.0e-10, &len, &dir[0]);
        dir[1] = geom->v;
    }
    else if (geom->type == 4)
    {
        double v = uv[1];
        double r = tan(geom->b) * v + geom->a;
        double cs = cos(uv[0]) * r;
        double sn = sin(uv[0]) * r;
        pt->x = geom->base.x + cs * geom->w.x + sn * bn.x;
        pt->y = geom->base.y + cs * geom->w.y + sn * bn.y;
        pt->z = geom->base.z + cs * geom->w.z + sn * bn.z;
        pt->x = pt->x + v * geom->v.x;
        pt->y = pt->y + v * geom->v.y;
        pt->z = pt->z + v * geom->v.z;
        sn = sin(uv[0]) * r;
        cs = cos(uv[0]) * r;
        const __m128 kSignMask = _mm_castsi128_ps(
            _mm_set_epi64x((long long)0x8000000000000000ULL, (long long)0x8000000000000000ULL));
        __m128d snv = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(_mm_load_sd(&sn)), kSignMask));
        __m128d csv = _mm_load_sd(&cs);

        _mm_store_sd(&dir[0].x,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.x)),
                                _mm_mul_sd(_mm_load_sd(&bn.x), csv)));
        _mm_store_sd(&dir[0].y,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.y)),
                                _mm_mul_sd(_mm_load_sd(&bn.y), csv)));
        _mm_store_sd(&dir[0].z,
                     _mm_add_sd(_mm_mul_sd(snv, _mm_load_sd(&geom->w.z)),
                                _mm_mul_sd(_mm_load_sd(&bn.z), csv)));
        VEC3_unitize(&dir[0], 1.0e-10, &len, &dir[0]);
        double t = tan(geom->b);
        cs = cos(uv[0]) * t;
        sn = sin(uv[0]) * t;
        dir[1].x = cs * geom->w.x + sn * bn.x;
        dir[1].y = cs * geom->w.y + sn * bn.y;
        dir[1].z = cs * geom->w.z + sn * bn.z;
        dir[1].x = dir[1].x + geom->v.x;
        dir[1].y = dir[1].y + geom->v.y;
        dir[1].z = dir[1].z + geom->v.z;
        VEC3_unitize(&dir[1], 1.0e-10, &len, &dir[1]);
    }
    else
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 8543,
                       "Unrecognizabe value of simple developable type.");
    }

    normal->x = dir[0].y * dir[1].z - dir[0].z * dir[1].y;
    normal->y = dir[0].z * dir[1].x - dir[0].x * dir[1].z;
    normal->z = dir[0].x * dir[1].y - dir[0].y * dir[1].x;
    VEC3_unitize(normal, 1.0e-10, &len, normal);
}
