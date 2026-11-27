













__declspec(dllimport) void SM_free(void* ptr);


struct PNTLST_s
{
    void* points;
    int   num;
};

struct BCDF_s
{
    char      pad0[0x38];
    PNTLST_s* deriv_pts;
    PNTLST_s* deriv_slopes;
    char      pad1[0x10];
    int*      deriv_pars;
};

void PNTLST_free_structure(PNTLST_s* p);
void PNTLST_remove_points(PNTLST_s* p, int start, int count);

extern "C" void* memmove(void* dst, const void* src, unsigned long long count);

void BCDF_remove_curvature_derivs(BCDF_s* a, int start, int count)
{
    PNTLST_s* pts = a->deriv_pts;
    if (count >= 1 && pts)
    {
        PNTLST_s* slp = a->deriv_slopes;
        if (count == pts->num)
        {
            PNTLST_free_structure(pts);
            a->deriv_pts = 0;
            PNTLST_free_structure(slp);
            a->deriv_slopes = 0;
            SM_free(a->deriv_pars);
            a->deriv_pars = 0;
        }
        else
        {
            PNTLST_remove_points(pts, start, count);
            PNTLST_remove_points(slp, start, count);
            memmove(a->deriv_pars + start, a->deriv_pars + (start + count),
                    (long long)count * 4);
        }
    }
}
