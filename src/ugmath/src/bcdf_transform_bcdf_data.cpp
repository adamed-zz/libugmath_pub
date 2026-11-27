







struct PNTLST_s;

namespace UGS
{
namespace Math
{
struct TransformMatrix;
}
}


struct BCDF_s
{
    PNTLST_s* p[8];
};


void PNTLST_transform(PNTLST_s* a1, UGS::Math::TransformMatrix* a2);

void BCDF_transform_bcdf_data(BCDF_s* a1, UGS::Math::TransformMatrix* a2)
{
    unsigned __int64* q = reinterpret_cast<unsigned __int64*>(a2);
    double* m = reinterpret_cast<double*>(a2);

    PNTLST_transform(a1->p[0], a2);
    q[3] = 0;
    q[7] = 0;
    q[11] = 0;
    PNTLST_transform(a1->p[3], a2);
    double v4 = m[15];
    m[15] = 1.0 / v4;
    PNTLST_transform(a1->p[5], a2);
    m[15] = 1.0 / (v4 * v4);
    PNTLST_transform(a1->p[7], a2);
}
