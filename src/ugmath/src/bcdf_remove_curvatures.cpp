












__declspec(dllimport) void SM_free(void* ptr);


struct PNTLST_s
{
    void* points;
    int   num;
};

struct BCDF_s
{
    char      pad0[0x28];
    PNTLST_s* points;
    PNTLST_s* slopes;
    char      pad1[0x18];
    int*      weights;
};

void PNTLST_free_structure(PNTLST_s* p);
void PNTLST_remove_points(PNTLST_s* p, int start, int count);

extern "C" void* memmove(void* dst, const void* src, unsigned long long count);

void BCDF_remove_curvatures(BCDF_s* a, int start, int count)
{
    PNTLST_s* pts = a->points;
    if (count >= 1 && pts)
    {
        PNTLST_s* slp = a->slopes;
        if (count == pts->num)
        {
            PNTLST_free_structure(pts);
            a->points = 0;
            PNTLST_free_structure(slp);
            a->slopes = 0;
            SM_free(a->weights);
            a->weights = 0;
        }
        else
        {
            PNTLST_remove_points(pts, start, count);
            PNTLST_remove_points(slp, start, count);
            memmove(a->weights + start, a->weights + (start + count),
                    (long long)count * 4);
        }
    }
}
