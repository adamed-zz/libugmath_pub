














struct BCDF_s;

namespace UGS {
namespace Math {
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

int BCDF_slope_at_point(BCDF_s* a, int idx, int* out);
void BCDF_copy_single_3d_slope(BCDF_s* a, int index, double* const out, int* flag);

bool BCDF_get_slope_at_point(BCDF_s* a, int idx, UGS::Math::Vector3& vec, int* flag)
{
    vec.z = 0.0;
    vec.y = 0.0;
    vec.x = 0.0;
    *flag = -1;
    int v9 = 0;
    if (!BCDF_slope_at_point(a, idx, &v9))
        return false;
    BCDF_copy_single_3d_slope(a, v9, (double*)&vec, flag);
    return true;
}
