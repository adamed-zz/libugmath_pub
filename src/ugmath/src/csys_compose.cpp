














struct CSYS_s
{
    double origin[3];
    double axes[3][3];
};

struct Matrix3
{
    double m[9];
};

double* sub_180001820(double* out, double s, const double* v);
void MTX3_multiply(const Matrix3* a1, const Matrix3* a2, Matrix3* a3);

void CSYS_compose(const CSYS_s* a1, const CSYS_s* a2, CSYS_s* a3)
{
    double temp[3];
    double* r1 = sub_180001820(temp, -1.0, a1->origin);
    double n1x = r1[0];
    double n1y = r1[1];
    double n1z = r1[2];

    double a1_00 = a1->axes[0][0];
    double a1_01 = a1->axes[0][1];
    double a1_02 = a1->axes[0][2];
    double a1_10 = a1->axes[1][0];
    double a1_11 = a1->axes[1][1];
    double a1_12 = a1->axes[1][2];
    double a1_20 = a1->axes[2][0];
    double a1_21 = a1->axes[2][1];
    double a1_22 = a1->axes[2][2];

    double* r2 = sub_180001820(temp, -1.0, a2->origin);
    double n2x = r2[0];
    double n2y = r2[1];
    double n2z = r2[2];

    double p0 = n2y * a2->axes[0][1] + n2x * a2->axes[0][0] + n2z * a2->axes[0][2];
    double p1 = n2y * a2->axes[1][1] + n2x * a2->axes[1][0] + n2z * a2->axes[1][2];
    double p2 = n2y * a2->axes[2][1] + n2x * a2->axes[2][0] + n2z * a2->axes[2][2];


    double q0 = (p1 * a1_01 + p0 * a1_00) + p2 * a1_02 +
                ((n1y * a1_01 + n1x * a1_00) + n1z * a1_02);
    double q1 = (p1 * a1_11 + p0 * a1_10) + p2 * a1_12 +
                ((n1y * a1_11 + n1x * a1_10) + n1z * a1_12);
    double q2 = (p1 * a1_21 + p0 * a1_20) + p2 * a1_22 +
                ((n1y * a1_21 + n1x * a1_20) + n1z * a1_22);

    MTX3_multiply((const Matrix3*)&a2->axes[0][0], (const Matrix3*)&a1->axes[0][0],
                  (Matrix3*)&a3->axes[0][0]);

    double o0 = q1 * a3->axes[1][0] + q0 * a3->axes[0][0] + q2 * a3->axes[2][0];
    double o1 = q1 * a3->axes[1][1] + q0 * a3->axes[0][1] + q2 * a3->axes[2][1];
    double o2 = q1 * a3->axes[1][2] + q0 * a3->axes[0][2] + q2 * a3->axes[2][2];

    a3->origin[0] = o0;
    a3->origin[1] = o1;
    a3->origin[2] = o2;

    double* r3 = sub_180001820(temp, -1.0, a3->origin);
    a3->origin[0] = r3[0];
    a3->origin[1] = r3[1];
    a3->origin[2] = r3[2];
}
