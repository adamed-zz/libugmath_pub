








struct LSFIT_simple_developable_geom_s
{
    int      status;

    __int64  v0[3];
    __int64  v1[3];
    __int64  v2[3];
    __int64  s0;
    __int64  s1;
    __int64  s2;
    __int64  s3;
    __int64  s4;
    __int64  s5;
    __int64  v3[3];
};

static_assert(sizeof(LSFIT_simple_developable_geom_s) == 0x98, "layout");

void LSFIT_init_simple_developable_geom(LSFIT_simple_developable_geom_s* p)
{
    p->status = -1;
    p->v0[0] = p->v0[1] = p->v0[2] = 0;
    p->v1[0] = p->v1[1] = p->v1[2] = 0;
    p->v2[0] = p->v2[1] = p->v2[2] = 0;
    p->s0 = 0;
    p->s1 = 0;
    p->s2 = 0;
    p->s3 = 0;
    p->s4 = 0;
    p->s5 = 0;
    p->v3[0] = p->v3[1] = p->v3[2] = 0;
}
