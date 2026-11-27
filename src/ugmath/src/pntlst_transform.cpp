









#include <cmath>
#include <emmintrin.h>


struct PNTLST_s
{
    double* points;
    int count;
    int capacity;
    int dim;
};

namespace UGS
{
namespace Math
{
struct TransformMatrix;
}
}

struct Point3_t
{
    double x, y, z;
};


extern "C" Point3_t sub_180063A60(const double* pt, const UGS::Math::TransformMatrix* mtx);

void PNTLST_transform(PNTLST_s* a1, UGS::Math::TransformMatrix* a2)
{
    if (!a1)
        return;

    int count = a1->count;
    int dim = a1->dim;
    double* p = a1->points;

    if (dim == 1)
        return;

    if (dim == 3)
    {
        if (count <= 0)
            return;
        unsigned __int64 n = (unsigned int)count;
        do
        {
            *(Point3_t*)p = sub_180063A60(p, a2);
            p += 3;
        } while (--n);
    }
    else if (dim == 4 && count > 0)
    {
        unsigned __int64 n = (unsigned int)count;
        do
        {
            double w = p[3];
            if (fabs(w - 0.0) <= 1.0e-10)
            {
                *(Point3_t*)p = sub_180063A60(p, a2);
            }
            else
            {
                Point3_t tmp;
                tmp.x = p[0] / w;
                tmp.y = p[1] / w;
                tmp.z = p[2] / w;
                Point3_t res = sub_180063A60(&tmp.x, a2);
                __m128d xy = _mm_mul_pd(_mm_loadu_pd(&res.x), _mm_set1_pd(w));
                _mm_storeu_pd(p, xy);
                p[2] = res.z * w;
            }
            p += 4;
        } while (--n);
    }
}
