









extern "C" unsigned __int64 sub_18004C7E0(double a1, double a2, double a3, double a4,
                                          double a5, double a6, double a7, double a8)
{
    double d = a6 - a8;
    double e = a7 - a5;
    double t = a5 * a8 - a6 * a7;
    return (d * a1 + e * a2 + t) * (d * a3 + e * a4 + t) > 0.0;
}
