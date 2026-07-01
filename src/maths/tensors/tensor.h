#ifndef TENSOR_H
#define TENSOR_H

#include "common/types.h"
#include <stdbool.h>
#include <stddef.h>

typedef enum tensor_dtype
{
    TENSOR_DTYPE_UNKNOWN = 0,

    /* Boolean */
    TENSOR_BOOL,

    /* Signed integers */
    TENSOR_I8,
    TENSOR_I16,
    TENSOR_I32,
    TENSOR_I64,

    /* Unsigned integers */
    TENSOR_U8,
    TENSOR_U16,
    TENSOR_U32,
    TENSOR_U64,

    /* Floating point */
    TENSOR_F32,
    TENSOR_F64,

    /* Complex */
    TENSOR_C32,
    TENSOR_C64,

    /* User-defined type */
    TENSOR_CUSTOM

} tensor_dtype;

typedef struct tensor
{
    void *data;
    tensor_dtype dtype;
    size_t elem_size;
    u32 ndim;
    u64 *shape;
    u64 *strides;
    u64 length;
    size_t bytes;
    bool owns_data;
} tensor;

/**
 * @brief Creates a new tensor.
 *
 * @param dtype Tensor element type.
 * @param ndim Number of dimensions.
 * @param shape Array of dimension sizes.
 *
 * @return Newly allocated tensor on success, NULL on failure.
 */
tensor *tensor_create(
    tensor_dtype dtype,
    u32 ndim,
    const u64 *shape);

/**
 * @brief Creates a tensor for a user-defined element type.
 *
 * @param elem_size Size of one element in bytes.
 * @param ndim Number of dimensions.
 * @param shape Array of dimension sizes.
 *
 * @return Newly allocated tensor on success, NULL on failure.
 */
tensor *tensor_create_custom(
    size_t elem_size,
    u32 ndim,
    const u64 *shape);

/**
 * @brief Releases all resources owned by a tensor.
 *
 * Safe to call with NULL.
 *
 * @param t Tensor to destroy.
 */
void tensor_destroy(tensor *t);

#endif