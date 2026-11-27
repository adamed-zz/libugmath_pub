








double EQ_ask_length_tolerance(void);
void h099a(double *a1, double a2, double *a3);

void h099(double *a1, double *a2)
{
    h099a(a1, EQ_ask_length_tolerance(), a2);
}
