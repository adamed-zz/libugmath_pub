























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

enum MTX_foreign_status_e : int;

extern "C"
{
__declspec(dllimport) extern bool RDEBUG__enabled;
__declspec(dllimport) int RDEBUG_ask_flag(const char *, bool);
}

extern "C"
{
void sub_18009AF10(int a1, const char *a2, int dim,
                   const UGS::Math::TransformMatrix *mat);
MTX_foreign_status_e sub_180099BE0(int a1, double *rot, bool flag, double *out);
}

MTX_foreign_status_e MTX4_fixup_foreign(UGS::Math::TransformMatrix *mtx, bool flag,
                                        double *out)
{
    if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        sub_18009AF10(0, "Entering MTX4_fixup_foreign:", 4, mtx);

    const double vals[9] = {mtx->m[0][0], mtx->m[0][1], mtx->m[0][2],
                            mtx->m[1][0], mtx->m[1][1], mtx->m[1][2],
                            mtx->m[2][0], mtx->m[2][1], mtx->m[2][2]};
    UGS::Math::Matrix3Copy rot(vals);

    MTX_foreign_status_e status = sub_180099BE0(0, rot.m, flag, out);

    const double back[9] = {rot.m[0], rot.m[1], rot.m[2], rot.m[3], rot.m[4],
                            rot.m[5], rot.m[6], rot.m[7], rot.m[8]};

    mtx->m[0][0] = back[0];
    mtx->m[0][1] = back[1];
    mtx->m[3][2] = 0.0;
    mtx->m[0][2] = back[2];
    mtx->m[2][0] = back[6];
    mtx->m[2][1] = back[7];
    mtx->m[3][1] = 0.0;
    mtx->m[1][0] = back[3];
    mtx->m[1][1] = back[4];
    mtx->m[3][0] = 0.0;
    mtx->m[2][2] = back[8];
    mtx->m[1][2] = back[5];

    if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        sub_18009AF10(0, "Exiting MTX4_fixup_foreign:", 4, mtx);

    return status;
}
