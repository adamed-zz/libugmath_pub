







void MC_proj_point_onto_plane(double* const pt, double* const n, double d, double* const out)
{
    double s = n[0] * pt[0] + n[1] * pt[1] + n[2] * pt[2] - d;
    double v = -s;
    out[0] = n[0] * v + pt[0];
    out[1] = n[1] * v + pt[1];
    out[2] = n[2] * v + pt[2];
}
