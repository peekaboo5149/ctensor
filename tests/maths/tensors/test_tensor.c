#include <criterion/criterion.h>

#include "maths/tensors/tensor.h"

Test(tensor_create, creates_1d_tensor)
{
    u64 shape[] = {5};

    tensor *t = tensor_create(TENSOR_F32, 1, shape);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_F32);
    cr_expect_eq(t->ndim, 1);
    cr_expect_eq(t->elem_size, sizeof(f32));
    cr_expect_eq(t->length, 5);
    cr_expect_eq(t->bytes, 5 * sizeof(f32));
    cr_expect_eq(t->shape[0], 5);

    cr_expect_eq(t->strides[0], 1);

    cr_assert_not_null(t->data);

    tensor_destroy(t);
}

Test(tensor_create, creates_2d_tensor)
{
    u64 shape[] = {3, 4};

    tensor *t = tensor_create(TENSOR_I32, 2, shape);

    cr_assert_not_null(t);

    cr_expect_eq(t->length, 12);
    cr_expect_eq(t->bytes, 12 * sizeof(i32));

    cr_expect_eq(t->shape[0], 3);
    cr_expect_eq(t->shape[1], 4);

    cr_expect_eq(t->strides[0], 4);
    cr_expect_eq(t->strides[1], 1);

    tensor_destroy(t);
}

Test(tensor_create, creates_3d_tensor)
{
    u64 shape[] = {2, 3, 4};

    tensor *t = tensor_create(TENSOR_F64, 3, shape);

    cr_assert_not_null(t);

    cr_expect_eq(t->length, 24);
    cr_expect_eq(t->bytes, 24 * sizeof(f64));

    cr_expect_eq(t->strides[0], 12);
    cr_expect_eq(t->strides[1], 4);
    cr_expect_eq(t->strides[2], 1);

    tensor_destroy(t);
}

Test(tensor_create, invalid_dtype_returns_null)
{
    u64 shape[] = {2, 2};

    tensor *t = tensor_create(TENSOR_DTYPE_UNKNOWN, 2, shape);

    cr_expect_null(t);
}

Test(tensor_create, custom_dtype_returns_null)
{
    u64 shape[] = {2, 2};

    tensor *t = tensor_create(TENSOR_CUSTOM, 2, shape);

    cr_expect_null(t);
}

Test(tensor_create, null_shape_returns_null)
{
    tensor *t = tensor_create(TENSOR_F32, 2, NULL);

    cr_expect_null(t);
}

Test(tensor_create, zero_dimension_returns_null)
{
    u64 shape[] = {2};

    tensor *t = tensor_create(TENSOR_F32, 0, shape);

    cr_expect_null(t);
}

Test(tensor_create, zero_shape_entry_returns_null)
{
    u64 shape[] = {3, 0, 5};

    tensor *t = tensor_create(TENSOR_F32, 3, shape);

    cr_expect_null(t);
}

Test(tensor_destroy, destroy_null_tensor)
{
    tensor_destroy(NULL);

    cr_assert(true);
}