#include <stdio.h>

#include "maths/complex/complex.h"
#include "maths/tensors/tensor.h"

int main(void)
{
    // /* ---------- complex32 ---------- */

    // complex32 a = cx32_from(3.0f, 4.0f);
    // complex32 b = cx32_from(1.0f, 2.0f);

    // complex32 sum32 = cx32_add(a, b);
    // complex32 mul32 = cx32_mul(a, b);

    // printf("complex32\n");
    // printf("a      = %.2f + %.2fi\n", a.real, a.img);
    // printf("b      = %.2f + %.2fi\n", b.real, b.img);
    // printf("a + b  = %.2f + %.2fi\n", sum32.real, sum32.img);
    // printf("a * b  = %.2f + %.2fi\n", mul32.real, mul32.img);
    // printf("|a|    = %.2f\n\n", cx32_abs(a));

    // /* ---------- complex64 ---------- */

    // complex64 x = cx64_from(3.0, 4.0);
    // complex64 y = cx64_from(1.0, 2.0);

    // complex64 sum64 = cx64_add(x, y);
    // complex64 mul64 = cx64_mul(x, y);

    // printf("complex64\n");
    // printf("x      = %.2lf + %.2lfi\n", x.real, x.img);
    // printf("y      = %.2lf + %.2lfi\n", y.real, y.img);
    // printf("x + y  = %.2lf + %.2lfi\n", sum64.real, sum64.img);
    // printf("x * y  = %.2lf + %.2lfi\n", mul64.real, mul64.img);
    // printf("|x|    = %.2lf\n", cx64_abs(x));

    // /*---------TENSOR------------*/
    // u64 shape[] = {2, 3, 4};

    // int values[2][3][4] =
    //     {
    //         {{0, 1, 2, 3},
    //          {4, 5, 6, 7},
    //          {8, 9, 10, 11}},
    //         {{12, 13, 14, 15},
    //          {16, 17, 18, 19},
    //          {20, 21, 22, 23}}};
    // tensor *t = tensor_from_buffer(
    //     TENSOR_F32,
    //     3,
    //     shape,
    //     values);

    // if (t == NULL)
    //     return 1;

    // printf("Shape   : [%llu %llu %llu]\n",
    //        t->shape[0],
    //        t->shape[1],
    //        t->shape[2]);

    // printf("Strides : [%llu %llu %llu]\n",
    //        t->strides[0],
    //        t->strides[1],
    //        t->strides[2]);

    // u64 idx[] = {1, 2, 3};

    // int *p = tensor_ptr(t, idx);

    // printf("\n");
    // printf("tensor[1][2][3] = %d\n", *p);

    // tensor_destroy(t);

    // return 0;

    u64 shape[] = {2, 2};

    complex32 values[2][2] =
        {
            {{.real = 1, .img = 2},
             {.real = 3, .img = 4}},
            {{.real = 5, .img = 6},
             {.real = 7, .img = 8}}};

    tensor *t = tensor_from_buffer(
        TENSOR_C32,
        2,
        shape,
        values);

    if (t == NULL)
        return 1;

    u64 idx[] = {1, 0};

    complex32 *c = tensor_ptr(t, idx);

    printf("real = %.2f\n", c->real);
    printf("imag = %.2f\n", c->img);

    tensor_destroy(t);

    return 0;
}