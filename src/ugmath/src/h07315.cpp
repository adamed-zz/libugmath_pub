












#include <cmath>

extern void h0736(const double* a1, double* a2);
extern void h804(double* a1, const double* a2, const int* a3, int* a4);
extern double EQ_ask_number_tolerance();

void h07315(const double* a1, const double* a2, int* a3)
{
    double b1[4];
    double b2[4];
    int mode = 0;
    int st;
    *a3 = 0;
    h0736(a1, b1);
    h0736(a2, b2);
    h804(&b2[0], &b1[0], &mode, &st);
    if (((st - 1) & 0xFFFFFFFB) == 0) {
        h804(&b1[0], &b2[0], &mode, &st);
        if (((st - 1) & 0xFFFFFFFB) == 0) {
            if (!(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[0] - b2[0])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[0] - b2[1])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[1] - b2[0])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[1] - b2[1])))
                return;
        }
    }
    h804(&b2[2], &b1[2], &mode, &st);
    if (((st - 1) & 0xFFFFFFFB) == 0) {
        h804(&b1[2], &b2[2], &mode, &st);
        if (((st - 1) & 0xFFFFFFFB) == 0) {
            if (!(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[2] - b2[2])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[2] - b2[3])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[3] - b2[2])) &&
                !(EQ_ask_number_tolerance() * 100.0 >= std::fabs(b1[3] - b2[3])))
                return;
        }
    }
    *a3 = 1;
}
