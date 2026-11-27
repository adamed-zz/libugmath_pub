












#include <cstring>


struct PNTLST_s
{
    void* points;
    int   num;
};


struct BCDF_s
{
    char      pad0[0x18];
    PNTLST_s* slopes1;
    PNTLST_s* slopes2;
    char      pad1[0x20];
    int*      values;
};

int BCDF_curvature_at_slope(BCDF_s* a, int slope, int* curvature);
void BCDF_remove_curvatures(BCDF_s* a, int start, int count);
int BCDF_return_num_of_crvatrs(BCDF_s* a);
void PNTLST_free_structure(PNTLST_s* p);
void PNTLST_remove_points(PNTLST_s* p, int start, int count);

void BCDF_remove_slopes(BCDF_s* a, int start, int count)
{
    PNTLST_s* s1 = a->slopes1;
    if (count >= 1 && s1)
    {
        PNTLST_s* s2 = a->slopes2;
        if (count == s1->num)
        {
            PNTLST_free_structure(s1);
            a->slopes1 = 0;
            PNTLST_free_structure(s2);
            a->slopes2 = 0;
            BCDF_remove_curvatures(a, 0, BCDF_return_num_of_crvatrs(a));
        }
        else
        {
            if (BCDF_return_num_of_crvatrs(a) > 0)
            {
                int i = 0;
                do
                {
                    int idx;
                    if (BCDF_curvature_at_slope(a, i + start, &idx))
                        BCDF_remove_curvatures(a, idx, 1);
                    ++i;
                } while (i < count);
            }
            PNTLST_remove_points(s1, start, count);
            PNTLST_remove_points(s2, start, count);
            memmove(a->values + start, a->values + (start + count), (long long)count * 4);
        }
    }
}
