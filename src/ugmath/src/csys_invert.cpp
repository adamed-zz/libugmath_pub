










struct CSYS_s
{
    double origin[3];
    double axes[3][3];
};

double* sub_180001820(double* out, double s, const double* v);

void CSYS_invert(const CSYS_s* a1, CSYS_s* a2)
{
    const double* o = a1->origin;
    const double* m = &a1->axes[0][0];
    double x = o[1] * m[1] + o[0] * m[0] + o[2] * m[2];
    double y = o[0] * m[3] + o[1] * m[4] + o[2] * m[5];
    double z = o[0] * m[6] + o[1] * m[7] + o[2] * m[8];
    double temp[3];
    a2->origin[0] = x;
    a2->origin[1] = y;
    a2->origin[2] = z;
    double* r = sub_180001820(temp, -1.0, a2->origin);
    a2->origin[0] = r[0];
    a2->origin[1] = r[1];
    a2->origin[2] = r[2];
    double a00 = m[0];
    double a01 = m[1];
    double a02 = m[2];
    double a10 = m[3];
    double a11 = m[4];
    double a12 = m[5];
    double a20 = m[6];
    double a21 = m[7];
    double a22 = m[8];
    a2->axes[0][0] = a00;
    a2->axes[0][1] = a10;
    a2->axes[0][2] = a20;
    a2->axes[1][0] = a01;
    a2->axes[1][1] = a11;
    a2->axes[1][2] = a21;
    a2->axes[2][0] = a02;
    a2->axes[2][1] = a12;
    a2->axes[2][2] = a22;
}
