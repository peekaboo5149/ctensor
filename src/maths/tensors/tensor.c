#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maths/tensors/tensor.h"
#include "maths/complex/complex.h"
#include "common/types.h"

/**
 * @brief Returns the size (in bytes) of a built-in tensor dtype.
 *
 * Returns 0 for invalid or unsupported types.
 */
static size_t tensor_dtype_size(tensor_dtype dtype);

/**
 * @brief Validates the common tensor creation arguments.
 *
 * Returns true if the arguments are valid, false otherwise.
 */
static bool tensor_validate_args(
    u32 ndim,
    const u64 *shape);

/**
 * @brief Allocates and initializes a tensor.
 *
 * Assumes all arguments have already been validated.
 */
static tensor *tensor_alloc(
    tensor_dtype dtype,
    size_t elem_size,
    u32 ndim,
    const u64 *shape);

tensor *tensor_create(
    tensor_dtype dtype,
    u32 ndim,
    const u64 *shape)
{
    if (dtype == TENSOR_DTYPE_UNKNOWN)
    {
        fprintf(stderr,
                "tensor_create: dtype cannot be of type TENSOR_DTYPE_UNKNOWN\n");
        return NULL;
    }

    if (dtype == TENSOR_CUSTOM)
    {
        fprintf(stderr,
                "tensor_create: cannot be used to create tensor for custom dtype\n");
        return NULL;
    }

    if (!tensor_validate_args(ndim, shape))
        return NULL;

    return tensor_alloc(
        dtype,
        tensor_dtype_size(dtype),
        ndim,
        shape);
}

void tensor_destroy(tensor *t)
{
    if (t == NULL)
        return;

    if (t->owns_data && t->data != NULL)
        DELETE(t->data);

    DELETE(t->shape);
    DELETE(t->strides);

    free(t);
}

static bool tensor_validate_args(
    u32 ndim,
    const u64 *shape)
{
    if (ndim == 0)
    {
        fprintf(stderr,
                "tensor_create: ndim must be greater than zero\n");
        return false;
    }

    if (shape == NULL)
    {
        fprintf(stderr,
                "tensor_create: shape cannot be null\n");
        return false;
    }

    FOR_U32(i, ndim)
    {
        if (shape[i] == 0)
        {
            fprintf(stderr,
                    "tensor_create: shape[%u] is 0; all dimensions must be greater than 0.\n",
                    i);
            return false;
        }
    }

    return true;
}

static tensor *tensor_alloc(
    tensor_dtype dtype,
    size_t elem_size,
    u32 ndim,
    const u64 *shape)
{
    tensor *t = NEW_ZERO(tensor);
    if (t == NULL)
    {
        perror("tensor_create");
        return NULL;
    }

    t->dtype = dtype;
    t->ndim = ndim;
    t->owns_data = true;
    t->elem_size = elem_size;

    t->shape = NEW_ARRAY(u64, ndim);
    if (t->shape == NULL)
    {
        tensor_destroy(t);
        perror("tensor_create");
        return NULL;
    }

    memcpy(t->shape, shape, ndim * sizeof(u64));

    /* Compute the total number of elements. */
    u64 product = 1;

    FOR_U32(i, ndim)
    {
        if (product > UINT64_MAX / t->shape[i])
        {
            tensor_destroy(t);
            fprintf(stderr,
                    "tensor_create: tensor size overflow.\n");
            return NULL;
        }

        product *= t->shape[i];
    }

    t->length = product;

    if (t->length > SIZE_MAX / t->elem_size)
    {
        tensor_destroy(t);
        fprintf(stderr,
                "tensor_create: tensor memory size overflow.\n");
        return NULL;
    }

    t->bytes = t->length * t->elem_size;

    t->strides = NEW_ARRAY_ZERO(u64, ndim);
    if (t->strides == NULL)
    {
        tensor_destroy(t);
        perror("tensor_create");
        return NULL;
    }

    t->strides[ndim - 1] = 1;

    for (u32 i = ndim - 1; i-- > 0;)
    {
        t->strides[i] =
            t->strides[i + 1] * t->shape[i + 1];
    }

    t->data = calloc(t->length, t->elem_size);
    if (t->data == NULL)
    {
        tensor_destroy(t);
        perror("tensor_create");
        return NULL;
    }

    return t;
}

static size_t tensor_dtype_size(tensor_dtype dtype)
{
    switch (dtype)
    {
    case TENSOR_BOOL:
        return sizeof(bool);

    case TENSOR_I8:
        return sizeof(i8);
    case TENSOR_I16:
        return sizeof(i16);
    case TENSOR_I32:
        return sizeof(i32);
    case TENSOR_I64:
        return sizeof(i64);

    case TENSOR_U8:
        return sizeof(u8);
    case TENSOR_U16:
        return sizeof(u16);
    case TENSOR_U32:
        return sizeof(u32);
    case TENSOR_U64:
        return sizeof(u64);

    case TENSOR_F32:
        return sizeof(f32);
    case TENSOR_F64:
        return sizeof(f64);

    case TENSOR_C32:
        return sizeof(complex32);
    case TENSOR_C64:
        return sizeof(complex64);

    case TENSOR_CUSTOM:
    case TENSOR_DTYPE_UNKNOWN:
    default:
        return 0;
    }
}