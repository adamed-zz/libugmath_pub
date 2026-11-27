













extern void h0736(const double* a1, double* a2);
extern double EQ_ask_number_tolerance();
extern void h07313(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);
extern void h07314(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);

void h07318(const int* a1, const int* a2, const double* a3, const double* a4, double* a5,
            double* a6, int* a7, int* a8)
{
    int v8 = *a1;
    int v9 = *a2;
    *a7 = 0;
    *a8 = 0;
    if (v8 != 1 && v9 != 1)
        return;
    double v24 = *a3;
    double v23 = *a4;
    double b1[4];
    double b2[4];
    h0736(a5, b1);
    h0736(a6, b2);
    if (v8 == 1) {
        int c1, c2;
        if (!(b2[1] - b2[0] > b1[1] - b1[0])) {
            *a7 = 2;
            if (!(EQ_ask_number_tolerance() + b1[1] > b2[1])) {
                c1 = -1;
                c2 = 0;
                h07314(&c1, &c2, &v24, &v23, a6);
            }
        } else {
            *a7 = 1;
            if (!(EQ_ask_number_tolerance() + b2[1] > b1[1])) {
                c1 = -1;
                c2 = 0;
                h07313(&c1, &c2, &v24, &v23, a5);
            }
        }
    }
    int c3 = 0;
    int c4 = 0;
    if (v9 == 1) {
        if (!(b2[3] - b2[2] > b1[3] - b1[2])) {
            *a8 = 2;
            if (!(EQ_ask_number_tolerance() + b1[3] > b2[3])) {
                c4 = -1;
                h07314(&c3, &c4, &v24, &v23, a6);
            }
        } else {
            *a8 = 1;
            if (!(EQ_ask_number_tolerance() + b2[3] > b1[3])) {
                c4 = -1;
                h07313(&c3, &c4, &v24, &v23, a5);
            }
        }
    }
}
