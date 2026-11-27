






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


int BCDF_curvature_deriv_at_point(BCDF_s* bcdf, int position, int* crvatr_deriv_index);
void BCDF_copy_single_3d_crvatr_deriv(BCDF_s* bcdf, int position, double* const values, int* crvatr_deriv_index);

bool BCDF_get_curvature_deriv_at_point(BCDF_s* bcdf, int h, UGS::Math::Vector3& vec, int* idx_out)
{
    vec.z = 0.0;
    vec.y = 0.0;
    vec.x = 0.0;
    *idx_out = -1;
    int position = 0;
    if (!BCDF_curvature_deriv_at_point(bcdf, h, &position))
        return false;
    BCDF_copy_single_3d_crvatr_deriv(bcdf, position, (double*)&vec, idx_out);
    return true;
}
