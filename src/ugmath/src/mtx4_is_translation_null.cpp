







namespace UGS {
namespace Math {

struct TransformMatrix {
    double m[16];
};

}
}


#include <math.h>




double EQ_ask_length_tolerance();






bool MTX4_is_translation_null(UGS::Math::TransformMatrix* m)
{
    double tolerance = EQ_ask_length_tolerance();
    double x = m->m[3];
    double y = m->m[7];
    double z = m->m[11];
    return tolerance >= sqrt(y * y + x * x + z * z);
}
