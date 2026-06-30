#include <criterion/criterion.h>
#include <math.h>

#include "maths/complex/complex.h"

#define EPS32 1e-5f
#define EPS64 1e-10

/*----------------------------------------------------------
 * Constructors
 *----------------------------------------------------------*/

Test(complex32, from)
{
    complex32 c = cx32_from(3.0f, 4.0f);

    cr_assert_float_eq(c.real, 3.0f, EPS32);
    cr_assert_float_eq(c.img, 4.0f, EPS32);
}

Test(complex64, from)
{
    complex64 c = cx64_from(3.0, 4.0);

    cr_assert_float_eq(c.real, 3.0, EPS64);
    cr_assert_float_eq(c.img, 4.0, EPS64);
}

/*----------------------------------------------------------
 * Addition
 *----------------------------------------------------------*/

Test(complex32, add)
{
    complex32 a = cx32_from(1.0f, 2.0f);
    complex32 b = cx32_from(3.0f, 4.0f);

    complex32 c = cx32_add(a, b);

    cr_assert_float_eq(c.real, 4.0f, EPS32);
    cr_assert_float_eq(c.img, 6.0f, EPS32);
}

Test(complex64, add)
{
    complex64 a = cx64_from(1.0, 2.0);
    complex64 b = cx64_from(3.0, 4.0);

    complex64 c = cx64_add(a, b);

    cr_assert_float_eq(c.real, 4.0, EPS64);
    cr_assert_float_eq(c.img, 6.0, EPS64);
}

/*----------------------------------------------------------
 * Multiplication
 *----------------------------------------------------------*/

Test(complex32, mul)
{
    complex32 a = cx32_from(3.0f, 4.0f);
    complex32 b = cx32_from(1.0f, 2.0f);

    complex32 c = cx32_mul(a, b);

    cr_assert_float_eq(c.real, -5.0f, EPS32);
    cr_assert_float_eq(c.img, 10.0f, EPS32);
}

Test(complex64, mul)
{
    complex64 a = cx64_from(3.0, 4.0);
    complex64 b = cx64_from(1.0, 2.0);

    complex64 c = cx64_mul(a, b);

    cr_assert_float_eq(c.real, -5.0, EPS64);
    cr_assert_float_eq(c.img, 10.0, EPS64);
}

/*----------------------------------------------------------
 * Conjugate
 *----------------------------------------------------------*/

Test(complex32, conjugate)
{
    complex32 a = cx32_from(5.0f, -3.0f);

    complex32 c = cx32_conj(a);

    cr_assert_float_eq(c.real, 5.0f, EPS32);
    cr_assert_float_eq(c.img, 3.0f, EPS32);
}

Test(complex64, conjugate)
{
    complex64 a = cx64_from(5.0, -3.0);

    complex64 c = cx64_conj(a);

    cr_assert_float_eq(c.real, 5.0, EPS64);
    cr_assert_float_eq(c.img, 3.0, EPS64);
}

/*----------------------------------------------------------
 * Magnitude
 *----------------------------------------------------------*/

Test(complex32, abs)
{
    complex32 a = cx32_from(3.0f, 4.0f);

    cr_assert_float_eq(cx32_abs(a), 5.0f, EPS32);
}

Test(complex64, abs)
{
    complex64 a = cx64_from(3.0, 4.0);

    cr_assert_float_eq(cx64_abs(a), 5.0, EPS64);
}

/*----------------------------------------------------------
 * Division
 *----------------------------------------------------------*/

Test(complex32, div)
{
    complex32 a = cx32_from(4.0f, 2.0f);
    complex32 b = cx32_from(1.0f, -1.0f);

    complex32 c = cx32_div(a, b);

    cr_assert_float_eq(c.real, 1.0f, EPS32);
    cr_assert_float_eq(c.img, 3.0f, EPS32);
}

Test(complex64, div)
{
    complex64 a = cx64_from(4.0, 2.0);
    complex64 b = cx64_from(1.0, -1.0);

    complex64 c = cx64_div(a, b);

    cr_assert_float_eq(c.real, 1.0, EPS64);
    cr_assert_float_eq(c.img, 3.0, EPS64);
}

/*----------------------------------------------------------
 * Argument
 *----------------------------------------------------------*/

Test(complex32, arg)
{
    complex32 a = cx32_from(1.0f, 1.0f);

    cr_assert_float_eq(cx32_arg(a), (float)M_PI / 4.0f, EPS32);
}

Test(complex64, arg)
{
    complex64 a = cx64_from(1.0, 1.0);

    cr_assert_float_eq(cx64_arg(a), M_PI / 4.0, EPS64);
}