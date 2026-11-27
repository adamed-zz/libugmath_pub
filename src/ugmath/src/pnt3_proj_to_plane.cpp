































#include "ugmath/pnt3.h"
#include "ugmath/point3.h"






void h635(const double* a1, const double* a2, const double* a3,
          const double* a4, int* status, double* out);

bool PNT3_proj_to_plane(const UGS::Math::Point3* point, const PLN3_s* plane,
                        UGS::Math::Point3* out)
{
    int status = 0;
    h635(&point->x,
         (const double*)((const char*)plane + 24),
         (const double*)plane,
         (const double*)((const char*)plane + 24),
         &status,
         (double*)out);
    return status == 2;
}
