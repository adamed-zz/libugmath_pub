#include "ugmath/solver_data_s.h"



int Solver_data_s::ask_method() const {
    return method;
}

void Solver_data_s::set_method(int m) {
    method = m;
}
