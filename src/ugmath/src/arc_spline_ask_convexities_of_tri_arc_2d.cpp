






#include <cmath>
#include <cstdint>

namespace UGS {
namespace Math {

struct Point2 {
    double x;
    double y;
};

struct Vector2 {
    double x;
    double y;
};

}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;



void __declspec(noinline) ARC_SPLINE_ask_isosceles_to_pt_2d(
    double* a1, Point2* a2, Vector2* a3, Point2* a4, Vector2* a5, int a6,
    Point2* a7, double* a8, int* a9, Point2* a10, Point2* a11, int* a12,
    int* a13);


int __declspec(noinline) ARC_SPLINE_ask_are_two_rays_homodromic_2d(
    double* a1, Point2* a2, Vector2* a3, Point2* a4, Vector2* a5, int a6,
    Point2* a7, double* a8, int* a9);

void ARC_SPLINE_ask_convexities_of_tri_arc_2d(
    double* a1, Point2* a2, Vector2* a3, Point2* a4, Vector2* a5, int a6,
    Point2* a7, double* a8, int* a9, Point2* a10, Point2* a11, int* a12,
    int* a13, char* a14)
{


    double* const v18 = a8;
    int* v15 = a12;
    int* v17 = a13;
    char* v14 = a14;
    int* const p12 = reinterpret_cast<int*>(&a12);
    int* const p14 = reinterpret_cast<int*>(&a14);

    *v14 = 110;
    *v15 = -2;
    *v17 = -2;
    ARC_SPLINE_ask_isosceles_to_pt_2d(a1, a2, a3, a4, a5, a6, a7, v18, a9, a10,
                                      a11, p12, p14);

    if (*a9 > 1) {
        *v15 = 0;
        *v17 = 0;
        return;
    }
    if (!a6 && *a9 > 0) {
        *v18 = 1.0e19;
        v18[1] = 1.0e19;
    }
    Point2* const va2 = a2;
    Vector2* const va3 = a3;
    int const v19 = ARC_SPLINE_ask_are_two_rays_homodromic_2d(
        a1, va2, va3, a4, a5, 1, a7, v18, a9);
    if (v19 == -1)
        return;

    {
        int v20 = -1;
        int const slot14 = *reinterpret_cast<volatile int*>(&a14);
        if (slot14 == 1) {
            *v15 = -1;
        } else if (slot14 == -1) {
            *v15 = 1;
        } else {
            *v14 = 108;
        }
        int const slot12 = *reinterpret_cast<volatile int*>(&a12);
        if (slot12 == 1) {
            *v17 = -1;
        } else if (slot12 == -1) {
            *v17 = 1;
            v20 = 1;
        } else {
            *v14 = 114;
            v20 = *v17;
            if (*v17 == -2)
                goto LABEL_24;
        }
        if (!(*a1 > fabs(v18[0]))) {
            if (*v15 == -2 || *a1 > fabs(v18[1])) {
                if (v19 == 0)
                    *v15 = v20;
                else if (v19 == 1)
                    *v15 = -v20;
            }
            goto LABEL_29;
        }
    LABEL_24:
        if (v19 == 0)
            *v17 = *v15;
        else if (v19 == 1)
            *v17 = -*v15;
    LABEL_29:
        if (*a9 == 1) {
            double const v22 = a10->y - va2->y;
            double const v23 = a10->x - va2->x;
            double const v25 = sqrt(v23 * v23 + v22 * v22);
            if (*a1 >= v25) {
                *v14 = 101;
            } else {
                char v26 = 108;
                if (v23 * va3->x + v22 * va3->y > 0.0)
                    v26 = 114;
                *v14 = v26;
            }
        } else {
            double const v27 = fabs(*v18);
            double const v28 = fabs(v18[1]);
            if (*a1 >= fabs(v27 - v28)) {
                *v14 = 101;
            } else {
                char v29 = 114;
                if (v28 > v27)
                    v29 = 108;
                *v14 = v29;
            }
        }
    }
}
