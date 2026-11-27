







#include <cmath>

namespace UGS {
namespace Math {

struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };

}
}


double __cdecl LSFIT_ask_dist_pt_to_line_3d(
    UGS::Math::Point3* p, UGS::Math::Point3* base, UGS::Math::Vector3* dir,
    double tol, UGS::Math::Point3* proj, double* param)
{
    double dy = p->y - base->y;
    double dx = p->x - base->x;
    double dz = p->z - base->z;
    double t = dy * dir->y + dx * dir->x + dz * dir->z;
    *param = t;
    double py = base->y + t * dir->y;
    double px = base->x + t * dir->x;
    double pz = base->z + t * dir->z;
    proj->x = px;
    proj->y = py;
    proj->z = pz;
    double d = sqrt((base->y - proj->y) * (base->y - proj->y)
                  + (base->x - proj->x) * (base->x - proj->x)
                  + (base->z - proj->z) * (base->z - proj->z));
    if (tol >= d)
    {
        proj->x = base->x;
        proj->y = base->y;
        proj->z = base->z;
        *param = 0.0;
    }
    return sqrt((proj->y - p->y) * (proj->y - p->y)
              + (proj->x - p->x) * (proj->x - p->x)
              + (proj->z - p->z) * (proj->z - p->z));
}
