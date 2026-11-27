













double ARC_SPLINE_ask_central_angle_from_inclination_angles(
    double start_angle, double* end_angle, int nsegs)
{
    double result = (*end_angle - start_angle) * (double)nsegs;
    if (result < 0.0)
    {
        result = result + 360.0;
        *end_angle = (double)nsegs * result + start_angle;
    }
    return result;
}
