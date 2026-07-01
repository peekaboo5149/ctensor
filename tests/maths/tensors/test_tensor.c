#include <criterion/criterion.h>
#include <string.h>

#include "maths/complex/complex.h"
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

typedef struct
{
    int id;
    float value;
} custom_type;

Test(tensor_create_custom, creates_custom_tensor)
{
    u64 shape[] = {2, 3};

    tensor *t = tensor_create_custom(
        sizeof(custom_type),
        2,
        shape);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_CUSTOM);
    cr_expect_eq(t->elem_size, sizeof(custom_type));

    cr_expect_eq(t->ndim, 2);

    cr_expect_eq(t->length, 6);

    cr_expect_eq(
        t->bytes,
        6 * sizeof(custom_type));

    cr_expect_eq(t->shape[0], 2);
    cr_expect_eq(t->shape[1], 3);

    cr_expect_eq(t->strides[0], 3);
    cr_expect_eq(t->strides[1], 1);

    cr_assert_not_null(t->data);

    tensor_destroy(t);
}

Test(tensor_create_custom, zero_elem_size_returns_null)
{
    u64 shape[] = {2, 2};

    tensor *t = tensor_create_custom(
        0,
        2,
        shape);

    cr_expect_null(t);
}

Test(tensor_create_custom, zero_ndim_returns_null)
{
    u64 shape[] = {2};

    tensor *t = tensor_create_custom(
        sizeof(custom_type),
        0,
        shape);

    cr_expect_null(t);
}

Test(tensor_create_custom, null_shape_returns_null)
{
    tensor *t = tensor_create_custom(
        sizeof(custom_type),
        2,
        NULL);

    cr_expect_null(t);
}

Test(tensor_create_custom, zero_shape_dimension_returns_null)
{
    u64 shape[] = {4, 0, 2};

    tensor *t = tensor_create_custom(
        sizeof(custom_type),
        3,
        shape);

    cr_expect_null(t);
}

Test(tensor_from_data, f32_1d)
{
    u64 shape[] = {4};
    f32 values[] = {1.f, 2.f, 3.f, 4.f};

    tensor *t = tensor_from_data(
        TENSOR_F32,
        1,
        shape,
        values);

    cr_assert_not_null(t);

    cr_expect_arr_eq(
        (f32 *)t->data,
        values,
        4 * sizeof(f32));

    tensor_destroy(t);
}

Test(tensor_from_data, i32_2d)
{
    u64 shape[] = {2, 3};

    i32 values[2][3] =
        {
            {1, 2, 3},
            {4, 5, 6}};

    tensor *t =
        tensor_from_data(
            TENSOR_I32,
            2,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_arr_eq(
        (i32 *)t->data,
        (i32 *)values,
        6 * sizeof(i32));

    tensor_destroy(t);
}

Test(tensor_from_data, u64_3d)
{
    u64 shape[] = {2, 2, 2};

    u64 values[2][2][2] =
        {
            {{1, 2},
             {3, 4}},
            {{5, 6},
             {7, 8}}};

    tensor *t =
        tensor_from_data(
            TENSOR_U64,
            3,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_arr_eq(
        (u64 *)t->data,
        (u64 *)values,
        8 * sizeof(u64));

    tensor_destroy(t);
}

Test(tensor_from_data, complex32)
{
    u64 shape[] = {2};

    complex32 values[] =
        {
            {.real = 1.f, .img = 2.f},
            {.real = 3.f, .img = 4.f}};

    tensor *t =
        tensor_from_data(
            TENSOR_C32,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    complex32 *ptr = t->data;

    cr_expect_float_eq(ptr[0].real, 1.f, 1e-6);
    cr_expect_float_eq(ptr[0].img, 2.f, 1e-6);

    cr_expect_float_eq(ptr[1].real, 3.f, 1e-6);
    cr_expect_float_eq(ptr[1].img, 4.f, 1e-6);

    tensor_destroy(t);
}

Test(tensor_from_data, complex64)
{
    u64 shape[] = {1};

    complex64 values[] =
        {
            {.real = 10, .img = 20}};

    tensor *t =
        tensor_from_data(
            TENSOR_C64,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    complex64 *ptr = t->data;

    cr_expect_eq(ptr[0].real, 10);
    cr_expect_eq(ptr[0].img, 20);

    tensor_destroy(t);
}

Test(tensor_from_data, performs_deep_copy)
{
    u64 shape[] = {4};

    f32 values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    values[0] = 100;

    cr_expect_float_eq(
        ((f32 *)t->data)[0],
        1,
        1e-6);

    tensor_destroy(t);
}

Test(tensor_from_data, metadata)
{
    u64 shape[] = {2, 3};

    i16 values[] =
        {
            1, 2, 3,
            4, 5, 6};

    tensor *t =
        tensor_from_data(
            TENSOR_I16,
            2,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_I16);

    cr_expect_eq(t->elem_size,
                 sizeof(i16));

    cr_expect_eq(t->length, 6);

    cr_expect_eq(
        t->bytes,
        6 * sizeof(i16));

    cr_expect_eq(
        t->strides[0],
        3);

    cr_expect_eq(
        t->strides[1],
        1);

    tensor_destroy(t);
}

Test(tensor_from_data, null_data)
{
    u64 shape[] = {4};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            1,
            shape,
            NULL);

    cr_expect_null(t);
}

Test(tensor_from_data, invalid_dtype)
{
    u64 shape[] = {4};

    f32 values[] = {1, 2, 3, 4};

    tensor *t =
        tensor_from_data(
            TENSOR_DTYPE_UNKNOWN,
            1,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_data, custom_dtype)
{
    u64 shape[] = {4};

    int values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_data(
            TENSOR_CUSTOM,
            1,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_data, null_shape)
{
    f32 values[] =
        {
            1, 2};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            1,
            NULL,
            values);

    cr_expect_null(t);
}

Test(tensor_from_data, zero_ndim)
{
    u64 shape[] = {2};

    f32 values[] =
        {
            1, 2};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            0,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_data, zero_shape_dimension)
{
    u64 shape[] =
        {
            2, 0};

    f32 values[] =
        {
            1, 2};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            2,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_data, data_pointer_is_not_source_pointer)
{
    u64 shape[] = {4};

    f32 values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_data(
            TENSOR_F32,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_neq(
        t->data,
        values);

    tensor_destroy(t);
}

typedef struct
{
    i32 id;
    f32 salary;
} employee;

typedef struct
{
    u64 x;
    u64 y;
    u64 z;
} point3d;

Test(tensor_from_custom_data, creates_tensor)
{
    u64 shape[] = {2};

    employee employees[] =
        {
            {1, 1000.0f},
            {2, 2500.5f}};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            shape,
            employees);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_CUSTOM);
    cr_expect_eq(t->elem_size, sizeof(employee));
    cr_expect_eq(t->length, 2);
    cr_expect_eq(t->bytes, 2 * sizeof(employee));

    employee *ptr = (employee *)t->data;

    cr_expect_eq(ptr[0].id, 1);
    cr_expect_float_eq(ptr[0].salary, 1000.0f, 1e-6);

    cr_expect_eq(ptr[1].id, 2);
    cr_expect_float_eq(ptr[1].salary, 2500.5f, 1e-6);

    tensor_destroy(t);
}

Test(tensor_from_custom_data, performs_deep_copy)
{
    u64 shape[] = {2};

    employee employees[] =
        {
            {1, 100},
            {2, 200}};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            shape,
            employees);

    cr_assert_not_null(t);

    employees[0].id = 999;
    employees[0].salary = 9999;

    employee *ptr = (employee *)t->data;

    cr_expect_eq(ptr[0].id, 1);
    cr_expect_float_eq(ptr[0].salary, 100, 1e-6);

    tensor_destroy(t);
}

Test(tensor_from_custom_data, multidimensional)
{
    u64 shape[] = {2, 2};

    point3d points[2][2] =
        {
            {{1, 2, 3},
             {4, 5, 6}},
            {{7, 8, 9},
             {10, 11, 12}}};

    tensor *t =
        tensor_from_custom_data(
            sizeof(point3d),
            2,
            shape,
            points);

    cr_assert_not_null(t);

    point3d *ptr = t->data;

    cr_expect_eq(ptr[0].x, 1);
    cr_expect_eq(ptr[3].z, 12);

    cr_expect_eq(t->strides[0], 2);
    cr_expect_eq(t->strides[1], 1);

    tensor_destroy(t);
}

Test(tensor_from_custom_data, metadata)
{
    u64 shape[] = {4};

    employee employees[4] = {0};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            shape,
            employees);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_CUSTOM);
    cr_expect_eq(t->elem_size, sizeof(employee));
    cr_expect_eq(t->length, 4);
    cr_expect_eq(t->bytes, 4 * sizeof(employee));

    tensor_destroy(t);
}

Test(tensor_from_custom_data, allocates_new_storage)
{
    u64 shape[] = {2};

    employee employees[2] = {0};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            shape,
            employees);

    cr_assert_not_null(t);

    cr_expect_neq(t->data, employees);

    tensor_destroy(t);
}

Test(tensor_from_custom_data, null_data)
{
    u64 shape[] = {2};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            shape,
            NULL);

    cr_expect_null(t);
}

Test(tensor_from_custom_data, zero_elem_size)
{
    u64 shape[] = {2};

    employee employees[2] = {0};

    tensor *t =
        tensor_from_custom_data(
            0,
            1,
            shape,
            employees);

    cr_expect_null(t);
}

Test(tensor_from_custom_data, null_shape)
{
    employee employees[2] = {0};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            1,
            NULL,
            employees);

    cr_expect_null(t);
}

Test(tensor_from_custom_data, zero_ndim)
{
    u64 shape[] = {2};

    employee employees[2] = {0};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            0,
            shape,
            employees);

    cr_expect_null(t);
}

Test(tensor_from_custom_data, zero_shape_dimension)
{
    u64 shape[] = {2, 0};

    employee employees[2] = {0};

    tensor *t =
        tensor_from_custom_data(
            sizeof(employee),
            2,
            shape,
            employees);

    cr_expect_null(t);
}

Test(tensor_from_buffer, creates_tensor)
{
    u64 shape[] = {2, 3};

    f32 values[] =
        {
            1, 2, 3,
            4, 5, 6};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            2,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_eq(t->dtype, TENSOR_F32);
    cr_expect_eq(t->elem_size, sizeof(f32));

    cr_expect_eq(t->length, 6);

    cr_expect_eq(
        t->bytes,
        6 * sizeof(f32));

    cr_expect_eq(
        t->owns_data,
        false);

    cr_expect_eq(
        t->data,
        values);

    tensor_destroy(t);
}

Test(tensor_from_buffer, reflects_buffer_changes)
{
    u64 shape[] = {4};

    f32 values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    values[2] = 100;

    cr_expect_float_eq(
        ((f32 *)t->data)[2],
        100,
        1e-6);

    tensor_destroy(t);
}

Test(tensor_from_buffer, writes_to_original_buffer)
{
    u64 shape[] = {4};

    f32 values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            1,
            shape,
            values);

    ((f32 *)t->data)[0] = 99;

    cr_expect_float_eq(
        values[0],
        99,
        1e-6);

    tensor_destroy(t);
}

Test(tensor_from_buffer, does_not_allocate_new_buffer)
{
    u64 shape[] = {2};

    i32 values[] =
        {
            10,
            20};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            1,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_eq(
        t->data,
        values);

    tensor_destroy(t);
}

Test(tensor_from_buffer, null_buffer)
{
    u64 shape[] = {2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            1,
            shape,
            NULL);

    cr_expect_null(t);
}

Test(tensor_from_buffer, invalid_dtype)
{
    u64 shape[] = {2};

    f32 values[] =
        {
            1, 2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_DTYPE_UNKNOWN,
            1,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_buffer, custom_dtype)
{
    u64 shape[] = {2};

    i32 values[] =
        {
            1,
            2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_CUSTOM,
            1,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_buffer, null_shape)
{
    f32 values[] =
        {
            1,
            2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            1,
            NULL,
            values);

    cr_expect_null(t);
}

Test(tensor_from_buffer, zero_ndim)
{
    u64 shape[] = {2};

    f32 values[] =
        {
            1,
            2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            0,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_buffer, zero_dimension)
{
    u64 shape[] =
        {
            2,
            0};

    f32 values[] =
        {
            1,
            2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            2,
            shape,
            values);

    cr_expect_null(t);
}

Test(tensor_from_buffer, computes_strides)
{
    u64 shape[] = {2, 3, 4};

    f32 values[24] = {0};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            3,
            shape,
            values);

    cr_assert_not_null(t);

    cr_expect_eq(t->strides[0], 12);
    cr_expect_eq(t->strides[1], 4);
    cr_expect_eq(t->strides[2], 1);

    tensor_destroy(t);
}

Test(tensor_ptr, f32_1d)
{
    u64 shape[] = {4};

    f32 values[] =
        {
            10, 20, 30, 40};

    tensor *t =
        tensor_from_buffer(
            TENSOR_F32,
            1,
            shape,
            values);

    u64 idx[] = {2};

    f32 *x = tensor_ptr(t, idx);

    cr_assert_not_null(x);

    cr_expect_float_eq(*x, 30, 1e-6);

    tensor_destroy(t);
}

Test(tensor_ptr, i32_2d)
{
    u64 shape[] = {2, 3};

    i32 values[2][3] =
        {
            {1, 2, 3},
            {4, 5, 6}};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            2,
            shape,
            values);

    u64 idx[] = {1, 2};

    i32 *x = tensor_ptr(t, idx);

    cr_assert_not_null(x);

    cr_expect_eq(*x, 6);

    tensor_destroy(t);
}

Test(tensor_ptr, u64_3d)
{
    u64 shape[] = {2, 2, 2};

    u64 values[2][2][2] =
        {
            {{1, 2},
             {3, 4}},
            {{5, 6},
             {7, 8}}};

    tensor *t =
        tensor_from_buffer(
            TENSOR_U64,
            3,
            shape,
            values);

    u64 idx[] = {1, 0, 1};

    u64 *x = tensor_ptr(t, idx);

    cr_assert_not_null(x);

    cr_expect_eq(*x, 6);

    tensor_destroy(t);
}

Test(tensor_ptr, complex32)
{
    u64 shape[] = {2, 2};

    complex32 values[2][2] =
        {
            {{.real = 1, .img = 2},
             {.real = 3, .img = 4}},
            {{.real = 5, .img = 6},
             {.real = 7, .img = 8}}};

    tensor *t =
        tensor_from_buffer(
            TENSOR_C32,
            2,
            shape,
            values);

    u64 idx[] = {1, 0};

    complex32 *c =
        tensor_ptr(t, idx);

    cr_assert_not_null(c);

    cr_expect_float_eq(c->real, 5, 1e-6);
    cr_expect_float_eq(c->img, 6, 1e-6);

    tensor_destroy(t);
}

Test(tensor_ptr, first_element_address)
{
    u64 shape[] = {4};

    i32 values[] =
        {
            1, 2, 3, 4};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            1,
            shape,
            values);

    u64 idx[] = {0};

    cr_expect_eq(
        tensor_ptr(t, idx),
        values);

    tensor_destroy(t);
}

Test(tensor_ptr, null_tensor)
{
    u64 idx[] = {0};

    cr_expect_null(
        tensor_ptr(NULL, idx));
}

Test(tensor_ptr, null_indices)
{
    u64 shape[] = {2};

    i32 values[] =
        {
            1, 2};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            1,
            shape,
            values);

    cr_expect_null(
        tensor_ptr(t, NULL));

    tensor_destroy(t);
}

Test(tensor_ptr, index_out_of_bounds)
{
    u64 shape[] = {2, 3};

    i32 values[2][3] =
        {
            {1, 2, 3},
            {4, 5, 6}};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            2,
            shape,
            values);

    u64 idx[] = {1, 3};

    cr_expect_null(
        tensor_ptr(t, idx));

    tensor_destroy(t);
}

Test(tensor_ptr, first_dimension_out_of_bounds)
{
    u64 shape[] = {2, 3};

    i32 values[2][3] = {0};

    tensor *t =
        tensor_from_buffer(
            TENSOR_I32,
            2,
            shape,
            values);

    u64 idx[] = {2, 0};

    cr_expect_null(
        tensor_ptr(t, idx));

    tensor_destroy(t);
}

Test(tensor_ptr, null_data)
{
    tensor t = {0};

    u64 idx[] = {0};

    cr_expect_null(
        tensor_ptr(&t, idx));
}

Test(tensor_get, f32)
{
    u64 shape[] = {2, 2};

    f32 values[2][2] =
        {
            {1, 2},
            {3, 4}};

    tensor *t = tensor_from_buffer(
        TENSOR_F32,
        2,
        shape,
        values);

    u64 idx[] = {1, 0};

    f32 out = 0;

    cr_assert(tensor_get(t, idx, &out));

    cr_expect_float_eq(out, 3.0f, 1e-6);

    tensor_destroy(t);
}

Test(tensor_get, complex32)
{
    u64 shape[] = {2};

    complex32 values[] =
        {
            {1, 2},
            {3, 4}};

    tensor *t = tensor_from_buffer(
        TENSOR_C32,
        1,
        shape,
        values);

    u64 idx[] = {1};

    complex32 out;

    cr_assert(tensor_get(t, idx, &out));

    cr_expect_float_eq(out.real, 3, 1e-6);
    cr_expect_float_eq(out.img, 4, 1e-6);

    tensor_destroy(t);
}

Test(tensor_get, null_output)
{
    u64 shape[] = {2};

    i32 values[] = {1, 2};

    tensor *t = tensor_from_buffer(
        TENSOR_I32,
        1,
        shape,
        values);

    u64 idx[] = {0};

    cr_expect_not(tensor_get(t, idx, NULL));

    tensor_destroy(t);
}

Test(tensor_set, f32)
{
    u64 shape[] = {2};

    f32 values[] = {1, 2};

    tensor *t = tensor_from_buffer(
        TENSOR_F32,
        1,
        shape,
        values);

    u64 idx[] = {1};

    f32 x = 99;

    cr_assert(tensor_set(t, idx, &x));

    cr_expect_float_eq(values[1], 99, 1e-6);

    tensor_destroy(t);
}

Test(tensor_set, complex32)
{
    u64 shape[] = {2};

    complex32 values[] =
        {
            {1, 2},
            {3, 4}};

    tensor *t = tensor_from_buffer(
        TENSOR_C32,
        1,
        shape,
        values);

    u64 idx[] = {0};

    complex32 c = {10, 20};

    cr_assert(tensor_set(t, idx, &c));

    cr_expect_float_eq(values[0].real, 10, 1e-6);
    cr_expect_float_eq(values[0].img, 20, 1e-6);

    tensor_destroy(t);
}

Test(tensor_set, null_value)
{
    u64 shape[] = {2};

    i32 values[] = {1, 2};

    tensor *t = tensor_from_buffer(
        TENSOR_I32,
        1,
        shape,
        values);

    u64 idx[] = {0};

    cr_expect_not(tensor_set(t, idx, NULL));

    tensor_destroy(t);
}

Test(tensor_destroy, destroy_null_tensor)
{
    tensor_destroy(NULL);

    cr_assert(true);
}