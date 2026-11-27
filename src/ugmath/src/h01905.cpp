





void vunt3(const double* a1, int* a2, double* a3);

void h01905(const double* a1, const double* a2, double* a3) {
    int flag = 0;
    double u[3] = {0.0, 0.0, 0.0};
    vunt3(a1, &flag, u);
    double c0 = a2[2] * u[1] - a2[1] * u[2];
    double c1 = a2[0] * u[2] - a2[2] * u[0];
    double c2 = a2[1] * u[0] - a2[0] * u[1];
    a3[0] = c1 * u[2] - c2 * u[1];
    a3[1] = c2 * u[0] - c0 * u[2];
    a3[2] = c0 * u[1] - c1 * u[0];
}
