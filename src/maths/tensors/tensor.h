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
 * @brief Creates a tensor by copying data from a contiguous memory buffer.
 *
 * The returned tensor owns its internal storage. The caller retains ownership
 * of @p data and may modify or free it after this function returns.
 *
 * Example:
 *
 *     u64 shape[] = {2, 3};
 *     f32 values[] = {1, 2, 3, 4, 5, 6};
 *
 *     tensor *t = tensor_from_data(
 *         TENSOR_F32,
 *         2,
 *         shape,
 *         values
 *     );
 *
 * @param dtype Tensor element data type.
 * @param ndim Number of tensor dimensions.
 * @param shape Array of dimension sizes.
 * @param data Pointer to the source data buffer.
 *
 * @return A newly allocated tensor on success, or NULL on failure.
 */
tensor *tensor_from_data(
    tensor_dtype dtype,
    u32 ndim,
    const u64 *shape,
    const void *data);

/**
 * @brief Creates a tensor by copying data from a contiguous memory buffer.
 *
 * The returned tensor stores elements of a user-defined type and owns its
 * internal storage. The caller retains ownership of @p data and may modify
 * or free it after this function returns.
 *
 * @param elem_size Size of each element in bytes.
 * @param ndim Number of tensor dimensions.
 * @param shape Array of dimension sizes.
 * @param data Pointer to the source data buffer.
 *
 * @return A newly allocated tensor on success, or NULL on failure.
 */
tensor *tensor_from_custom_data(
    size_t elem_size,
    u32 ndim,
    const u64 *shape,
    const void *data);

tensor *tensor_from_buffer(
    tensor_dtype dtype,
    u32 ndim,
    const u64 *shape,
    void *buffer);

void *tensor_ptr(
    const tensor *t,
    const u64 *indices);

bool tensor_get(
    const tensor *t,
    const u64 *indices,
    void *out);

bool tensor_set(
    tensor *t,
    const u64 *indices,
    const void *value);

bool tensor_fill(
    tensor *t,
    const void *value);

/**
 * @brief Releases all resources owned by a tensor.
 *
 * Safe to call with NULL.
 *
 * @param t Tensor to destroy.
 */
void tensor_destroy(tensor *t);

#endif