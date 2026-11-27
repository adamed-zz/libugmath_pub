















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

int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* m);

void CSYS_map_csys(const CSYS_s* a1, const CSYS_s* a2, CSYS_s* a3)
{

    double v5 = (a1->origin[1] - a2->origin[1]) * a2->axes[0][1] +
                (a1->origin[0] - a2->origin[0]) * a2->axes[0][0] +
                (a1->origin[2] - a2->origin[2]) * a2->axes[0][2];
    double v6 = (a1->origin[1] - a2->origin[1]) * a2->axes[1][1] +
                (a1->origin[0] - a2->origin[0]) * a2->axes[1][0] +
                (a1->origin[2] - a2->origin[2]) * a2->axes[1][2];
    double v7 = (a1->origin[1] - a2->origin[1]) * a2->axes[2][1] +
                (a1->origin[0] - a2->origin[0]) * a2->axes[2][0] +
                (a1->origin[2] - a2->origin[2]) * a2->axes[2][2];
    UGS::Math::Vector3 org;
    org.x = v5;
    org.y = v6;
    org.z = v7;
    memcpy(a3->origin, &org, sizeof(org));

    double v8 = a1->axes[0][1];
    double v9 = a1->axes[0][2];
    double v10 = a2->axes[0][0];
    double v11 = a2->axes[0][2];
    double v12 = a2->axes[1][0];
    double v13 = a2->axes[1][2];
    double v14 = a2->axes[2][0];
    double v15 = a1->axes[1][0];
    double v16 = a1->axes[1][1];
    double v17 = a1->axes[1][2];
    double v18 = a2->axes[0][1] * v8;
    double v19 = a2->axes[1][1] * v8;
    double v20 = a2->axes[2][1] * v8;
    double v21 = a2->axes[2][2];
    UGS::Math::Vector3 v31;
    double v22 = a1->axes[0][0];
    v31.x = v18 + v10 * v22 + v11 * v9;
    v31.y = v19 + v12 * v22 + v13 * v9;
    v31.z = v20 + v14 * v22 + v21 * v9;
    double v23 = a2->axes[1][1];
    double v24 = a2->axes[2][1];
    UGS::Math::Vector3 v30;
    v30.x = a2->axes[0][1] * v16 + v10 * v15 + v11 * v17;
    double v25 = a1->axes[2][1];
    v30.y = v23 * v16 + v12 * v15 + v13 * v17;
    double v26 = a2->axes[0][1];
    double v27 = a1->axes[2][0];
    v30.z = v24 * v16 + v14 * v15 + v21 * v17;
    double v28 = a1->axes[2][2];
    UGS::Math::Vector3 v29;
    v29.x = v26 * v25 + v10 * v27 + v11 * v28;
    v29.y = v23 * v25 + v12 * v27 + v13 * v28;
    v29.z = v24 * v25 + v14 * v27 + v21 * v28;

    MTX3_init_x_y_z(&v31, &v30, &v29, (UGS::Math::Matrix3*)&a3->axes[0][0]);
}
