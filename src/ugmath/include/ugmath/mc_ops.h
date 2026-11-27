#pragma once













































double __cdecl MC_triple_product(double* const a1, double* const a2, double* const a3);
double __cdecl MC_determinant(double (*const m)[4]);
void __cdecl MC_apply_transform_to_point(double (* const a1)[4], double* const a2, double* const a3);
void __cdecl MC_apply_transform_to_vector(double (* const a1)[4], double* const a2, double* const a3);
