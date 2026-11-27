





















namespace UGS
{
namespace Math
{

struct TransformMatrix
{
    double m[4][4];
};



struct Matrix3Copy
{
    double m[9];
    Matrix3Copy(const double (&v)[9])
    {
        for (int i = 0; i < 9; ++i)
            m[i] = v[i];
    }
};

}
}

extern "C" int sub_18009D300(double *m3x3);

int MTX4_fixup(UGS::Math::TransformMatrix *mtx)
{
    const double vals[9] = {mtx->m[0][0], mtx->m[0][1], mtx->m[0][2],
                            mtx->m[1][0], mtx->m[1][1], mtx->m[1][2],
                            mtx->m[2][0], mtx->m[2][1], mtx->m[2][2]};
    UGS::Math::Matrix3Copy rot(vals);

    int status = sub_18009D300(rot.m);

    mtx->m[0][0] = rot.m[0];
    mtx->m[0][1] = rot.m[1];
    mtx->m[0][2] = rot.m[2];
    mtx->m[1][0] = rot.m[3];
    mtx->m[1][1] = rot.m[4];
    mtx->m[1][2] = rot.m[5];
    mtx->m[2][0] = rot.m[6];
    mtx->m[2][1] = rot.m[7];
    mtx->m[2][2] = rot.m[8];

    return status;
}
