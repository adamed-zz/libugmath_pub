



extern "C" double* sub_180063A60(double* dst, const double* pt, const double* mtx)
{
    double y = pt[1];
    double x = pt[0];
    double z = pt[2];
    double r0 = x * mtx[0] + y * mtx[1] + z * mtx[2] + mtx[3];
    double r1 = x * mtx[4] + y * mtx[5] + z * mtx[6] + mtx[7];
    double r2 = x * mtx[8] + y * mtx[9] + z * mtx[10] + mtx[11];
    double w  = x * mtx[12] + y * mtx[13] + z * mtx[14] + mtx[15];
    if (w < 1.0e-19)
    {
        if (w >= 0.0)
            w = 1.0e-19;
        else
            w = (w > -1.0e-19) ? -1.0e-19 : w;
    }
    dst[0] = r0 / w;
    dst[1] = r1 / w;
    dst[2] = r2 / w;
    return dst;
}
