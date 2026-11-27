












struct BCDF_s;
struct PNTLST_s;

extern void PNTLST_replace_points(struct PNTLST_s*, int, int, double*);

void BCDF_replace_weight(struct BCDF_s* a, int index, double w)
{
    PNTLST_replace_points(*(struct PNTLST_s**)((char*)a + 8), 1, index, &w);
}
