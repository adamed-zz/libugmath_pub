










#include <intrin.h>

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

struct BCDF_s
{
    PNTLST_s* df_points;
    PNTLST_s* field_08;
    PNTLST_s* params;
    PNTLST_s* slopes;
    PNTLST_s* slope_pars;
    PNTLST_s* curvatures;
    PNTLST_s* crv_pars;
    PNTLST_s* crv_derivs;
    PNTLST_s* crv_deriv_pars;
    int*      slope_types;
    int*      crv_types;
    int*      crv_deriv_types;
    char      pad[0x20];
    int*      constraint_types;
};


void    PNTLST_reverse(PNTLST_s* list);
double* BCDF_return_param_array(BCDF_s* a, int* count);
double* BCDF_return_slope_array(BCDF_s* a, int* count, int* dim);
double* BCDF_return_slope_pars_array(BCDF_s* a, int* count);
double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count);
double* BCDF_return_crvatr_deriv_array(BCDF_s* a, int* count, int* dim);
double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* count);
double* BCDF_return_knot_sequence(BCDF_s* a, int* count);


__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line,
                                          const char* msg, ...);

void BCDF_reverse_bcdf_data(BCDF_s* a1)
{
    PNTLST_reverse(a1->df_points);

    int n;
    double* par = BCDF_return_param_array(a1, &n);
    if (!par)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
                       4278, "Bcurve Defining Data Structure Corrupt");
        __debugbreak();
        __assume(0);
    }
    double last = par[n - 1];
    for (int i = 0; i < n; i++)
        par[i] = last - par[i];

    PNTLST_reverse(a1->params);

    int nslope;
    int dim;
    double* slope = BCDF_return_slope_array(a1, &nslope, &dim);
    for (int i = 0; i < nslope * dim; i++)
        slope[i] = slope[i] * -1.0;

    PNTLST_reverse(a1->slopes);

    double* spars = BCDF_return_slope_pars_array(a1, &nslope);
    for (int i = 0; i < nslope; i++)
        spars[i] = last - spars[i];

    PNTLST_reverse(a1->slope_pars);

    if (nslope)
    {
        int* types = a1->slope_types;
        if (types)
        {
            int i = 0;
            int j = nslope - 1;
            while (i < j)
            {
                int t = types[i];
                types[i] = types[j];
                types[j] = t;
                ++i;
                --j;
            }
        }
    }

    PNTLST_reverse(a1->curvatures);

    int nc;
    double* cpars = BCDF_return_crvatr_pars_array(a1, &nc);
    for (int i = 0; i < nc; i++)
        cpars[i] = last - cpars[i];

    PNTLST_reverse(a1->crv_pars);

    if (nc)
    {
        int* types = a1->crv_types;
        if (types)
        {
            int i = 0;
            int j = nc - 1;
            while (i < j)
            {
                int t = types[i];
                types[i] = types[j];
                types[j] = t;
                ++i;
                --j;
            }
        }
    }

    int nd;
    double* deriv = BCDF_return_crvatr_deriv_array(a1, &nd, &dim);
    for (int i = 0; i < nd * dim; i++)
        deriv[i] = deriv[i] * -1.0;

    PNTLST_reverse(a1->crv_derivs);

    double* dpars = BCDF_return_crvatr_deriv_pars_array(a1, &nd);
    for (int i = 0; i < nd; i++)
        dpars[i] = last - dpars[i];

    PNTLST_reverse(a1->crv_deriv_pars);

    if (nd)
    {
        int* types = a1->crv_deriv_types;
        if (types)
        {
            int i = 0;
            int j = nd - 1;
            while (i < j)
            {
                int t = types[i];
                types[i] = types[j];
                types[j] = t;
                ++i;
                --j;
            }
        }
    }

    if (n)
    {
        int* types = a1->constraint_types;
        if (types)
        {
            int i = 0;
            int j = n - 1;
            while (i < j)
            {
                int t = types[i];
                types[i] = types[j];
                types[j] = t;
                ++i;
                --j;
            }
        }
    }

    int nk;
    double* knots = BCDF_return_knot_sequence(a1, &nk);
    if (knots)
    {
        double lastk = knots[nk - 1];
        for (int i = 0; i < nk; i++)
            knots[i] = lastk - knots[i] + knots[0];
        if (nk)
        {
            for (__int64 i = 0, j = nk - 1; i < nk; i++, j--)
            {
                if (j <= i)
                    break;
                double t = knots[i];
                knots[i] = knots[j];
                knots[j] = t;
            }
        }
    }

    PNTLST_reverse(a1->field_08);
}
