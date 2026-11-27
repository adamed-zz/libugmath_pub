

#pragma once

#include "b18_kit.h"

struct B18MapCase
{
    int reps;
    int alias;
    double mtx[9];
    double pt[3];
    double tol;
    double in[4];
    double out0[6];
};


inline int b18_make_map_cases(B18MapCase *cs)
{
    B18Rng rng(0xB18C0FFEEull);
    const uint64_t seeds[6] = {
        0xFFFFFFFFFFFFFFFFull,
        0x7FF8000000000123ull,
        0x7FF0000000000000ull,
        0xFFF0000000000000ull,
        0x0000000000000001ull,
        0x8000000000000000ull,
    };
    int n = 0;


    B18MapCase &c0 = cs[n++];
    memset(&c0, 0, sizeof c0);
    c0.reps = 1;
    c0.mtx[0] = 1.0; c0.mtx[4] = 1.0; c0.mtx[8] = 1.0;
    c0.in[0] = 1.0; c0.in[1] = -2.0; c0.in[2] = 3.5;
    for (int i = 0; i < 6; ++i)
        c0.out0[i] = b18_from_bits(seeds[i % 6]);


    for (int k = 0; k < 5; ++k)
    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        for (int i = 0; i < 9; ++i)
            c.mtx[i] = rng.sym(1.0e3);
        for (int i = 0; i < 3; ++i)
            c.pt[i] = rng.sym(10.0);
        c.in[0] = rng.sym(100.0);
        c.in[1] = rng.sym(100.0);
        c.in[2] = rng.sym(100.0);
        c.in[3] = rng.sym(100.0);
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits(0xFFFFFFFFFFFFFFFFull);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.in[0] = 0.0; c.in[1] = 0.0; c.in[2] = 0.0;
        c.in[3] = 0.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = 0.0;
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.mtx[0] = 0.0; c.mtx[4] = -0.0; c.mtx[8] = 1.0;
        c.mtx[1] = -0.0; c.mtx[3] = 1.0;
        c.in[0] = -0.0; c.in[1] = 0.0; c.in[2] = 1.0;
        c.in[3] = -0.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits(seeds[i % 6]);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.mtx[0] = 1.0; c.mtx[4] = 1.0; c.mtx[8] = 1.0;
        c.pt[0] = b18_special(2);
        c.in[0] = b18_special(2);
        c.in[1] = 2.0; c.in[2] = 3.0; c.in[3] = b18_special(2);
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_special(i);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.mtx[0] = 2.0; c.mtx[4] = -3.0; c.mtx[8] = 1.0;
        c.in[0] = b18_special(3); c.in[1] = b18_special(4); c.in[2] = 1.0;
        c.in[3] = 1.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_special(i + 1);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.mtx[0] = b18_special(6); c.mtx[4] = 1.0; c.mtx[8] = 2.0;
        c.in[0] = b18_special(5); c.in[1] = b18_special(6); c.in[2] = 3.0;
        c.in[3] = 0.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_special(i + 3);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        for (int i = 0; i < 9; ++i)
            c.mtx[i] = b18_special(i);
        c.pt[0] = b18_special(3);
        c.in[0] = 1.0; c.in[1] = 2.0; c.in[2] = 3.0; c.in[3] = 4.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits(0xFFFFFFFFFFFFFFFFull);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        for (int i = 0; i < 9; ++i)
            c.mtx[i] = (i & 1) ? -1.0e150 : 1.0e150;
        c.in[0] = 1.0e150; c.in[1] = -1.0e150; c.in[2] = 1.0e150;
        c.in[3] = 0.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits(0x7FF8000000000001ull);
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 1;
        c.alias = 1;
        c.mtx[0] = 2.0; c.mtx[1] = 1.0; c.mtx[2] = 0.5;
        c.mtx[3] = -1.0; c.mtx[4] = 3.0; c.mtx[5] = 0.25;
        c.mtx[6] = 4.0; c.mtx[7] = -2.0; c.mtx[8] = 1.0;
        c.pt[0] = 5.0; c.pt[1] = -6.0; c.pt[2] = 7.0;
        c.in[0] = 1.5; c.in[1] = -2.5; c.in[2] = 3.5;
        c.in[3] = b18_from_bits(0xFFFFFFFFFFFFFFFFull);
        for (int i = 0; i < 6; ++i)
            c.out0[i] = 0.0;
    }


    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = 3;
        c.mtx[0] = 0.5; c.mtx[4] = 0.5; c.mtx[8] = 0.5;
        c.in[0] = 8.0; c.in[1] = -4.0; c.in[2] = 2.0; c.in[3] = 1.0;
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits(0x3FF0000000000000ull + i);
    }


    for (int k = 0; k < 9; ++k)
    {
        B18MapCase &c = cs[n++];
        memset(&c, 0, sizeof c);
        c.reps = (k == 8) ? 2 : 1;
        for (int i = 0; i < 9; ++i)
        {
            double v = rng.sym(10.0);
            if (((k + i) % 7) == 0)
                v = b18_special((k + i) & 7);
            c.mtx[i] = v;
        }
        for (int i = 0; i < 3; ++i)
        {
            double v = rng.sym(5.0);
            if (((k + i) % 5) == 0)
                v = b18_special((k * 3 + i) & 7);
            c.pt[i] = v;
        }
        for (int i = 0; i < 4; ++i)
        {
            double v = rng.sym(20.0);
            if (((k + i) % 6) == 0)
                v = b18_special((k + 2 * i) & 7);
            c.in[i] = v;
        }
        for (int i = 0; i < 6; ++i)
            c.out0[i] = b18_from_bits((0x7FF8000000000000ull + (uint64_t)(k * 6 + i)));
    }
    return n;
}


struct B18GlobCase
{
    int reps;
    int count;
    unsigned int arr[512];
    int cb;
    unsigned int arg;
    unsigned int arg2;
    unsigned char ingrip;
    int cuval;
    unsigned char b120[0x8C];
    unsigned char arg_pad[4];
};


inline int b18_make_glob_cases(B18GlobCase *cs)
{
    B18Rng rng(0xB18610Bull);
    int n = 0;

    for (int c = 0; c < 16; ++c)
    {
        B18GlobCase &g = cs[c];
        memset(&g, 0, sizeof g);
        memset(g.arr, 0xFF, sizeof g.arr);
        memset(g.b120, 0xFF, sizeof g.b120);
        g.ingrip = 0x7F;
        g.cuval = 0x7F7F7F7F;
    }


    cs[n++].reps = 1;


    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 1; g.arg = 0x11111111u;
        g.arr[0] = g.arg; g.arr[1] = 0x22222222u;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 3; g.arg = 0x33333333u;
        g.arr[0] = 0xA0000001u; g.arr[1] = g.arg; g.arr[2] = 0xA0000002u;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 5; g.arg = 0xDEADBEEFu;
        for (int i = 0; i < 5; ++i) g.arr[i] = 0xB0000000u + i;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 512; g.arg = 0xC0DE0000u;
        for (int i = 0; i < 512; ++i) g.arr[i] = 0xC0DE0000u + i;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 512; g.arg = 0xC0DE01FFu;
        for (int i = 0; i < 512; ++i) g.arr[i] = 0xC0DE0000u + i;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 2; g.arg = 0x5A5A5A5Au;
        g.arr[0] = g.arg; g.arr[1] = g.arg; g.arr[2] = 0x99999999u;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 1; g.arg = 0x2468ACE0u;
        g.ingrip = 1; g.cuval = 0x12345678;
        g.arr[0] = 0x13579BDFu;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 4; g.ingrip = 0xFF;
        for (int i = 0; i < 4; ++i) g.arr[i] = rng.next();
        for (int i = 0; i < (int)sizeof g.b120; ++i) g.b120[i] = (unsigned char)rng.next();
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 512; g.cb = 1; g.arg = 0xF00DF00Du;
        for (int i = 0; i < 512; ++i) g.arr[i] = 0xE0000000u + i;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 0; g.cb = 1;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 3; g.count = 1; g.arg = 0x0BADF00Du;
        g.arr[0] = g.arg;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 2; g.count = 0; g.arg = 0xAA000001u; g.arg2 = 0xBB000002u;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 2; g.arg = 0xFFFFFFFFu; g.arg2 = 0x80000000u;
        g.arr[0] = 0xFFFFFFFFu; g.arr[1] = 0x80000000u;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 1; g.count = 1; g.cb = 1; g.arg = 0x600DF00Du;
        g.arr[0] = g.arg;
    }

    {
        B18GlobCase &g = cs[n++];
        g.reps = 5; g.count = 512; g.cb = 1; g.arg = 0x1F1F1F1Fu;
        for (int i = 0; i < 512; ++i) g.arr[i] = 0xD0000000u + i;
    }
    return n;
}
