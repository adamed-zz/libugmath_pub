






void bc_POLE_average_in_3d(double (*a1)[4], int a2, double (*a3)[3])
{
    double sx = 0.0, sy = 0.0, sz = 0.0;
    (*a3)[0] = 0.0;
    (*a3)[1] = 0.0;
    (*a3)[2] = 0.0;

    for (int i = 0; i < a2; ++i)
    {
        double w = a1[i][3];
        sx = sx + a1[i][0] / w;
        (*a3)[0] = sx;
        sy = sy + a1[i][1] / w;
        (*a3)[1] = sy;
        sz = sz + a1[i][2] / w;
        (*a3)[2] = sz;
    }

    double inv = 1.0 / (double)a2;
    (*a3)[2] = sz * inv;
    (*a3)[0] = sx * inv;
    (*a3)[1] = sy * inv;
}
