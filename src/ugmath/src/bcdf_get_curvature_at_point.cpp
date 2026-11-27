







struct BCDF_s;

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}


int BCDF_curvature_at_point(BCDF_s* bcdf, int point_index, int* crv_index);
void BCDF_copy_single_3d_crvatr(BCDF_s* bcdf, int crv_index,
                                UGS::Math::Vector3* crv, int* status);

bool BCDF_get_curvature_at_point(BCDF_s* a1, int a2, UGS::Math::Vector3& a3,
                                 int* a4)
{
    a3.z = 0.0;
    a3.y = 0.0;
    a3.x = 0.0;
    *a4 = -1;
    int pos = 0;
    if (!BCDF_curvature_at_point(a1, a2, &pos))
        return false;
    BCDF_copy_single_3d_crvatr(a1, pos, &a3, a4);
    return true;
}
