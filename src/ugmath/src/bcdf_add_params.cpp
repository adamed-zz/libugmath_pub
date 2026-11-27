














#include <math.h>

struct BCDF_s;

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     stride;
};


double* BCDF_return_df_point_array(struct BCDF_s* a, int* count, int* stride);
int*    BCDF_create_slope_pos_array(struct BCDF_s* a, int* out_count);
double* BCDF_return_slope_pars_array(struct BCDF_s* a, int* count);
double* BCDF_return_crvatr_pars_array(struct BCDF_s* a, int* count);
int*    BCDF_create_crvatr_pos_array(struct BCDF_s* a, int* out_count);
double* BCDF_return_crvatr_deriv_pars_array(struct BCDF_s* a, int* count);
int*    BCDF_create_crvatr_deriv_pos_array(struct BCDF_s* a, int* out_count);
double* BCDF_return_slope_array(struct BCDF_s* a, int* count1, int* count2);
void    BCDF_CALC_parameters(int n, int stride, double* pts, double alpha,
                             bool normalize, double* out);
struct PNTLST_s* PNTLST_allocate_struct(int stride, int n);
void    PNTLST_allocate_points(struct PNTLST_s* lst, int n);
__declspec(dllimport) void __cdecl SM_free(void* p);

void BCDF_add_params(struct BCDF_s* a1, double* a2)
{
    double v4 = 0.0;
    int nDfPts;
    int dfStride;
    double* dfPts = BCDF_return_df_point_array(a1, &nDfPts, &dfStride);
    struct PNTLST_s* lst = *(struct PNTLST_s**)((char*)a1 + 0x10);

    int nSlope;
    int* slopePos = BCDF_create_slope_pos_array(a1, &nSlope);
    double* slopePars = BCDF_return_slope_pars_array(a1, &nSlope);
    int nCrv;
    double* crvPars = BCDF_return_crvatr_pars_array(a1, &nCrv);
    int* crvPos = BCDF_create_crvatr_pos_array(a1, &nCrv);
    int nDer;
    double* derPars = BCDF_return_crvatr_deriv_pars_array(a1, &nDer);
    int* derPos = BCDF_create_crvatr_deriv_pos_array(a1, &nDer);

    double* par;
    if (lst)
    {
        par = lst->points;
        v4 = par[nDfPts - 1];
        if (lst->alloc < nDfPts)
        {
            PNTLST_allocate_points(lst, nDfPts);
            par = lst->points;
        }
    }
    else
    {
        lst = PNTLST_allocate_struct(1, nDfPts);
        par = lst->points;
    }

    int i = 0;
    lst->num = nDfPts;

    if (a2)
    {
        for (i = 0; i < nDfPts; i++)
            par[i] = a2[i];
    }
    else
    {
        BCDF_CALC_parameters(nDfPts, dfStride, dfPts, 1.0, false, par);
    }

    *(struct PNTLST_s**)((char*)a1 + 0x10) = lst;

    if (nSlope > 0)
    {
        double v19 = par[nDfPts - 1];
        double v20;
        if (fabs(v4) <= 1.0e-10 || fabs(v19) <= 1.0e-10)
            v20 = 1.0;
        else
            v20 = v4 / v19;

        int c1, c2;
        double* slopes = BCDF_return_slope_array(a1, &c1, &c2);
        for (i = 0; i < c1 * c2; i++)
            slopes[i] = v20 * slopes[i];

        for (i = 0; i < nSlope; i++)
            slopePars[i] = par[slopePos[i] - 1];
        SM_free(slopePos);
    }

    if (nCrv > 0)
    {
        for (i = 0; i < nCrv; i++)
            crvPars[i] = par[crvPos[i] - 1];
        SM_free(crvPos);
    }

    if (nDer > 0)
    {
        for (i = 0; i < nDer; i++)
            derPars[i] = par[derPos[i] - 1];
        SM_free(derPos);
    }
}
