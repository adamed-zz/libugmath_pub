







int h0917(double a1, const double* a2, int a3, double a4)
{
    if (*a2 - a4 > a1)
        return -1;
    int v4 = a3 - 1;
    if (a1 > a2[v4] + a4)
        return -1;
    if (*a2 >= a1)
    {
        int result = 0;
        if (v4 > 0)
        {
            int v6 = 0;
            while (!(a2[v6 + 1] > a2[v6]))
            {
                ++result;
                if (++v6 >= v4)
                    return -1;
            }
            return result;
        }
        return -1;
    }
    if (!(a1 >= a2[v4]))
    {
        int result = 0;
        if (v4 <= 0)
            return -1;
        int v9 = 0;
        while (1)
        {
            double v10 = a2[v9];
            double v11 = a2[v9 + 1];
            if (v10 != v11 && a1 >= v10 && v11 > a1)
                break;
            ++result;
            if (++v9 >= v4)
                return -1;
        }
        return result;
    }
    else
    {
        int v7 = a3 - 2;
        int v8 = a3 - 2;
        if (a3 - 2 < 0)
            return -1;
        while (!(a2[v8 + 1] > a2[v8]))
        {
            --v7;
            if (--v8 < 0)
                return -1;
        }
        return v7;
    }
}
