




















#include <cmath>
#include <cstring>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
struct Matrix3
{
    double m[9];
};
}
}

struct CSYS_s
{
    double origin[3];
    double axes[3][3];
};

int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* m);

bool CSYS_get_csys_given_z_dir(const CSYS_s* a1, const UGS::Math::Vector3* a2, CSYS_s* a3)
{
    double len = sqrt(a2->x * a2->x + a2->y * a2->y + a2->z * a2->z);
    if (1.0e-10 >= len)
        return false;
    UGS::Math::Vector3 zdir = {0.0, 0.0, 0.0};
    double ulen;
    VEC3_unitize(a2, 1.0e-10, &ulen, &zdir);

    UGS::Math::Vector3 origin;
    memcpy(&origin, a1->origin, sizeof(origin));
    double mat[9];
    memcpy(mat, &a1->axes[0][0], sizeof(mat));
    double azx = mat[6];
    double azy = mat[7];
    double azz = mat[8];
    double dx = zdir.x - azx;
    double dy = zdir.y - azy;
    double dz = zdir.z - azz;
    double dist = sqrt(dx * dx + dy * dy + dz * dz);
    if (1.0e-10 >= dist)
    {
        *a3 = *a1;
        return true;
    }
    {
        double sx = zdir.x + azx;
        double sy = zdir.y + azy;
        double sz = zdir.z + azz;
        double sdist = sqrt(sx * sx + sy * sy + sz * sz);
        UGS::Math::Vector3 x, y, z;
        if (!(1.0e-10 >= sdist))
        {
            x.x = zdir.z * azy - zdir.y * azz;
            x.y = zdir.x * azz - zdir.z * azx;
            x.z = zdir.y * azx - zdir.x * azy;
            VEC3_unitize(&x, 1.0e-10, &ulen, &x);
            y.x = x.z * zdir.y - x.y * zdir.z;
            y.y = x.x * zdir.z - x.z * zdir.x;
            y.z = x.y * zdir.x - x.x * zdir.y;
            z = zdir;
        }
        else
        {
            x.x = a1->axes[0][0];
            x.y = a1->axes[0][1];
            x.z = a1->axes[0][2];
            y.x = -a1->axes[1][0];
            y.y = -a1->axes[1][1];
            y.z = -a1->axes[1][2];
            z.x = -azx;
            z.y = -azy;
            z.z = -azz;
        }
        MTX3_init_x_y_z(&x, &y, &z, reinterpret_cast<UGS::Math::Matrix3*>(mat));
        memcpy(&a3->axes[0][0], mat, sizeof(mat));
        memcpy(a3->origin, &origin, sizeof(origin));
    }
    return true;
}
