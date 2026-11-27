











int SOLVE_lu_solver_with_abort(double** a1, double** a2, int a3, int a4,
                               bool(__cdecl* abort)(void));

int SOLVE_lu_solver(double** a1, double** a2, int a3, int a4)
{
    return SOLVE_lu_solver_with_abort(a1, a2, a3, a4, nullptr);
}
