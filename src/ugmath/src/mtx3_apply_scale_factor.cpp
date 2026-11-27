






#pragma once



namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}

using UGS::Math::Matrix3;



bool MTX3_get_scale_factor(const Matrix3* m, double tol, double* scale_out);



bool MTX3_apply_scale_factor(Matrix3* m, double tol, double* scale_out)
{
    bool result = MTX3_get_scale_factor(m, tol, scale_out);
    if (result && *scale_out > tol)
    {
        m->m[0] /= *scale_out;
        m->m[1] /= *scale_out;
        m->m[2] /= *scale_out;
        m->m[3] /= *scale_out;
        m->m[4] /= *scale_out;
        m->m[5] /= *scale_out;
        m->m[6] /= *scale_out;
        m->m[7] /= *scale_out;
        m->m[8] /= *scale_out;
    }
    return result;
}
