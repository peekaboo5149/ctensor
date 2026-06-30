#include <stdio.h>

#include "maths/complex.h"

int main(void)
{
    /* ---------- complex32 ---------- */

    complex32 a = cx32_from(3.0f, 4.0f);
    complex32 b = cx32_from(1.0f, 2.0f);

    complex32 sum32 = cx32_add(a, b);
    complex32 mul32 = cx32_mul(a, b);

    printf("complex32\n");
    printf("a      = %.2f + %.2fi\n", a.real, a.img);
    printf("b      = %.2f + %.2fi\n", b.real, b.img);
    printf("a + b  = %.2f + %.2fi\n", sum32.real, sum32.img);
    printf("a * b  = %.2f + %.2fi\n", mul32.real, mul32.img);
    printf("|a|    = %.2f\n\n", cx32_abs(a));

    /* ---------- complex64 ---------- */

    complex64 x = cx64_from(3.0, 4.0);
    complex64 y = cx64_from(1.0, 2.0);

    complex64 sum64 = cx64_add(x, y);
    complex64 mul64 = cx64_mul(x, y);

    printf("complex64\n");
    printf("x      = %.2lf + %.2lfi\n", x.real, x.img);
    printf("y      = %.2lf + %.2lfi\n", y.real, y.img);
    printf("x + y  = %.2lf + %.2lfi\n", sum64.real, sum64.img);
    printf("x * y  = %.2lf + %.2lfi\n", mul64.real, mul64.img);
    printf("|x|    = %.2lf\n", cx64_abs(x));

    return 0;
}