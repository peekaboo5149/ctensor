#include <math.h>

/* Helper macros */
#define CONCAT2(a, b) a##b
#define CONCAT(a, b) CONCAT2(a, b)

/*==========================================================
 * Constructors
 *==========================================================*/

CX_TYPE CONCAT(CX_PREFIX, _from)(CX_REAL real, CX_REAL img)
{
    return (CX_TYPE){
        .real = real,
        .img = img};
}

/*==========================================================
 * Arithmetic
 *==========================================================*/

CX_TYPE CONCAT(CX_PREFIX, _add)(CX_TYPE a, CX_TYPE b)
{
    return (CX_TYPE){
        .real = a.real + b.real,
        .img = a.img + b.img};
}

CX_TYPE CONCAT(CX_PREFIX, _sub)(CX_TYPE a, CX_TYPE b)
{
    return (CX_TYPE){
        .real = a.real - b.real,
        .img = a.img - b.img};
}

CX_TYPE CONCAT(CX_PREFIX, _mul)(CX_TYPE a, CX_TYPE b)
{
    return (CX_TYPE){
        .real = a.real * b.real - a.img * b.img,
        .img = a.real * b.img + a.img * b.real};
}

CX_TYPE CONCAT(CX_PREFIX, _div)(CX_TYPE a, CX_TYPE b)
{
    CX_REAL denom = b.real * b.real + b.img * b.img;

    return (CX_TYPE){
        .real = (a.real * b.real + a.img * b.img) / denom,
        .img = (a.img * b.real - a.real * b.img) / denom};
}

/*==========================================================
 * Utilities
 *==========================================================*/

CX_TYPE CONCAT(CX_PREFIX, _conj)(CX_TYPE a)
{
    return (CX_TYPE){
        .real = a.real,
        .img = -a.img};
}

CX_REAL CONCAT(CX_PREFIX, _abs)(CX_TYPE a)
{
    return sqrt(a.real * a.real + a.img * a.img);
}

CX_REAL CONCAT(CX_PREFIX, _arg)(CX_TYPE a)
{
    return atan2(a.img, a.real);
}

/* Cleanup */
#undef CONCAT
#undef CONCAT2