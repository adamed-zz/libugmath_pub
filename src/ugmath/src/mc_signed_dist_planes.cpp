










double MC_signed_dist_planes(double* const a1, double a2,
                             double* const a3, double a4)
{
    double v7 = a3[2] * a1[1] - a3[1] * a1[2];
    double v8 = a3[0] * a1[2] - a1[0] * a3[2];
    double v9 = a1[0] * a3[1] - a3[0] * a1[1];
    double result = 0.0;
    if (v8 * v8 + v7 * v7 + v9 * v9 < 0.000017453292519943296)
    {
        double dot = a1[0] * a3[0] + a3[1] * a1[1] + a1[2] * a3[2];
        if (!(dot > 0.0))
            a4 = -a4;
        return a4 - a2;
    }
    return result;
}
