#pragma once

#include <cstddef>




struct Solver_data_s {
    unsigned char pad0[0x68];
    int method;

    int ask_method() const;
    void set_method(int m);
};

static_assert(offsetof(Solver_data_s, method) == 0x68,
              "Solver_data_s::method 必须位于 +104");
