












int DGEOM_convert_radius_to_crvatr(double* const a1, double* const a2)
{
    double v3 = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
    if (v3 >= 1.0e-38)
    {
        double v4 = 1.0 / v3;
        a2[0] = a1[0] * v4;
        a2[1] = a1[1] * v4;
        a2[2] = a1[2] * v4;
        return 0;
    }
    return 1;
}
