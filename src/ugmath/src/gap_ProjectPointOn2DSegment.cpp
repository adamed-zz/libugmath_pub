














namespace UGS {
namespace Math {

void ProjectPointOn2DSegment(const double* const p, const double* const seg,
                             double& t, double* const proj);

void ProjectPointOn2DSegment(const double* const p, const double* const seg,
                             double& t, double* const proj)
{
    t = 0.0;
    proj[0] = seg[0];
    proj[1] = seg[1];
    const double dy = seg[3] - seg[1];
    const double dx = seg[2] - seg[0];
    const double len2 = dy * dy + dx * dx;
    if (!(len2 > 1.0000000116860974e-07)) return;
    const double v = ((p[1] - seg[1]) * dy + (p[0] - seg[0]) * dx) / len2;
    t = v;
    if (v < 1.0e-12) {
        t = 0.0;
        proj[0] = seg[0];
        proj[1] = seg[1];
    } else if (!(v > 0.999999999999)) {
        proj[0] = (seg[2] - seg[0]) * v + seg[0];
        proj[1] = (seg[3] - seg[1]) * t + seg[1];
    } else {
        t = 1.0;
        proj[0] = seg[2];
        proj[1] = seg[3];
    }
}

}
}
