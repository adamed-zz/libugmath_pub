








struct ARC_SPLINE_monge_plane_s;

struct ARC_SPLINE_monge_plane_s
{
    unsigned __int64 m00;
    unsigned __int64 m08;
    unsigned __int64 m10;
    unsigned __int64 m18;
    unsigned char    m20;
};

void ARC_SPLINE_copy_monge_plane(struct ARC_SPLINE_monge_plane_s* src, struct ARC_SPLINE_monge_plane_s* dst)
{
    dst->m20 = src->m20;
    dst->m00 = src->m00;
    dst->m08 = src->m08;
    dst->m10 = src->m10;
    dst->m18 = src->m18;
}
