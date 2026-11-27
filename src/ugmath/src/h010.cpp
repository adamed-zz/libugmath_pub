







#include <cmath>

double EQ_ask_number_tolerance(void);
void h002(double *a1, const double *a2);

void h010(double *a1, double *a2, int *a3, double *a4)
{
    *a3 = 1;
    *a4 = *a2;
    a4[1] = a2[1];
    double v24 = 6.283185307179586;
    if (!(*a1 >= *a2) || !(a2[1] >= *a1))
    {
        if (EQ_ask_number_tolerance() >= fabs(*a1 - *a2))
        {
            *a1 = *a2;
        }
        else if (!(EQ_ask_number_tolerance() >= fabs(*a1 - a2[1])))
        {
            double v13 = a1[1];
            if (!(a1[1] >= *a2) || !(a2[1] >= a1[1]))
            {
                if (EQ_ask_number_tolerance() >= fabs(a1[1] - *a2))
                {
                    v13 = *a2;
                }
                else if (EQ_ask_number_tolerance() >= fabs(a1[1] - a2[1]))
                {
                    v13 = a2[1];
                }
                else
                {
                    if (!(*a2 >= *a1) || !(a1[1] >= *a2))
                    {
                        if (EQ_ask_number_tolerance() >= fabs(*a2 - *a1))
                        {
                            *a2 = *a1;
                        }
                        else if (EQ_ask_number_tolerance() >= fabs(*a2 - a1[1]))
                        {
                            *a2 = a1[1];
                        }
                        else
                        {
                            return;
                        }
                    }
                    goto LABEL_25;
                }
                a1[1] = v13;
                a4[1] = v13;
                goto LABEL_25;
            }
            a4[1] = v13;
            goto LABEL_25;
        }
        else
        {
            *a1 = a2[1];
        }
    }
    {
        double v19 = a1[1];
        if (!(v19 >= *a2) || !(a2[1] >= v19))
        {
            if (EQ_ask_number_tolerance() >= fabs(a1[1] - *a2))
            {
                a1[1] = *a2;
            }
            else if (EQ_ask_number_tolerance() >= fabs(a1[1] - a2[1]))
            {
                a1[1] = a2[1];
            }
            else
            {
                *a4 = *a1;
                goto LABEL_25;
            }
        }
    }
    *a4 = *a1;
    a4[1] = a1[1];
LABEL_25:
    h002(a4, &v24);
    h002(a4 + 1, &v24);
    int b = EQ_ask_number_tolerance() >= fabs(*a4 - a4[1]);
    if (b != 1)
    {
        *a3 = 2;
        if (*a4 > a4[1])
            a4[1] = a4[1] + 6.283185307179586;
    }
}
