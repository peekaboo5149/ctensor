#ifndef COMPLEX_H
#define COMPLEX_H

#include "common/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*==========================================================
     * Types
     *==========================================================*/

    typedef struct
    {
        f32 real;
        f32 img;
    } complex32;

    typedef struct
    {
        f64 real;
        f64 img;
    } complex64;

    /*==========================================================
     * API Generator
     *==========================================================*/

#define COMPLEX_DECLARE(TYPE, REAL, PREFIX)  \
    TYPE PREFIX##_from(REAL real, REAL img); \
    TYPE PREFIX##_add(TYPE a, TYPE b);       \
    TYPE PREFIX##_sub(TYPE a, TYPE b);       \
    TYPE PREFIX##_mul(TYPE a, TYPE b);       \
    TYPE PREFIX##_div(TYPE a, TYPE b);       \
    TYPE PREFIX##_conj(TYPE a);              \
    REAL PREFIX##_abs(TYPE a);               \
    REAL PREFIX##_arg(TYPE a);

    COMPLEX_DECLARE(complex32, f32, cx32)
    COMPLEX_DECLARE(complex64, f64, cx64)

#undef COMPLEX_DECLARE

#ifdef __cplusplus
}
#endif

#endif