








struct ARC_SPLINE_1_seg_2d_s;


struct ARC_SPLINE_1_seg_2d_s {
    int   f00;
    int   f04;
    void* p08;
    void* p10;
    void* p18;
    void* p20;
    void* p28;
    void* p30;
    void* p38;
    void* p40;
    void* p48;
    void* p50;
};


void ARC_SPLINE_copy_1_seg_2d_pre_allocated(struct ARC_SPLINE_1_seg_2d_s* src, struct ARC_SPLINE_1_seg_2d_s* dst)
{
    dst->f00 = src->f00;
    dst->f04 = src->f04;
    dst->p08 = src->p08;
    dst->p10 = src->p10;
    dst->p18 = src->p18;
    dst->p20 = src->p20;
    dst->p28 = src->p28;
    dst->p30 = src->p30;
    dst->p38 = src->p38;
    dst->p40 = src->p40;
    dst->p48 = src->p48;
    dst->p50 = src->p50;
}
