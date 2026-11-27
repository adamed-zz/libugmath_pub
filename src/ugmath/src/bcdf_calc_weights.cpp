












void BCDF_CALC_weights(int periodicity, int count, double* params, double* out)
{
    for (int i = 1; i < count - 1; ++i)
        out[i] = (params[i + 1] - params[i - 1]) * 0.5;

    out[0] = (params[1] - params[0]) * 0.5;
    out[count - 1] = (params[count - 1] - params[count - 2]) * 0.5;

    if (periodicity)
    {
        double sum = out[0] + out[count - 1];
        out[0] = sum;
        out[count - 1] = sum;
    }
}
