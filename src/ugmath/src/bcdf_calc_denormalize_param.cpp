









struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a, int* count);

double BCDF_CALC_denormalize_param(struct BCDF_s* a, double t)
{
    int count;
    double* params = BCDF_return_param_array(a, &count);
    return t * params[count - 1] + (1.0 - t) * params[0];
}
