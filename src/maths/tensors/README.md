# TODO

> Roadmap for the `tensor` library.

| Done | Function                                                                                           | Description                                                             |
| :--: | -------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------- |
| [x]  | `tensor *tensor_create(tensor_dtype dtype, u32 ndim, const u64 *shape);`                           | Create a tensor with built-in data types.                               |
| [x]  | `tensor *tensor_create_custom(size_t elem_size, u32 ndim, const u64 *shape);`                      | Create a tensor with a user-defined element type.                       |
| [x]  | `tensor *tensor_from_data(tensor_dtype dtype, u32 ndim, const u64 *shape, const void *data);`      | Create a tensor by copying data from a contiguous memory buffer.        |
| [x]  | `tensor *tensor_from_custom_data(size_t elem_size, u32 ndim, const u64 *shape, const void *data);` | Create a custom tensor by copying data from a contiguous memory buffer. |
| [x]  | `tensor *tensor_from_buffer(tensor_dtype dtype, u32 ndim, const u64 *shape, void *buffer);`        | Create a tensor that wraps an external buffer without copying.          |
| [x]  | `tensor *tensor_from_custom_buffer(size_t elem_size, u32 ndim, const u64 *shape, void *buffer);`   | Create a custom tensor that wraps an external buffer without copying.   |
| [x]  | `void tensor_destroy(tensor *t);`                                                                  | Destroy a tensor and release owned resources.                           |
| [x]  | `void *tensor_ptr(const tensor *t, const u64 *indices);`                                           | Return a pointer to an element using multidimensional indices.          |
| [x]  | `bool tensor_get(const tensor *t, const u64 *indices, void *out);`                                 | Copy a tensor element into an output buffer.                            |
| [x]  | `bool tensor_set(tensor *t, const u64 *indices, const void *value);`                               | Replace a tensor element with a new value.                              |
| [x]  | `bool tensor_fill(tensor *t, const void *value);`                                                  | Fill every tensor element with the same value.                          |

---

# Tensor Factory

| Done | Function                                                                                       | Description                                           |
| :--: | ---------------------------------------------------------------------------------------------- | ----------------------------------------------------- |
| [ ]  | `tensor *tensor_zeros(tensor_dtype dtype, u32 ndim, const u64 *shape);`                        | Create a tensor initialized to zeros.                 |
| [ ]  | `tensor *tensor_ones(tensor_dtype dtype, u32 ndim, const u64 *shape);`                         | Create a tensor initialized to ones.                  |
| [ ]  | `tensor *tensor_full(tensor_dtype dtype, u32 ndim, const u64 *shape, const void *value);`      | Create a tensor filled with a specified value.        |
| [ ]  | `tensor *tensor_identity(tensor_dtype dtype, u64 n);`                                          | Create an identity matrix.                            |
| [ ]  | `tensor *tensor_diag(const tensor *v);`                                                        | Create a diagonal matrix from a vector.               |
| [ ]  | `tensor *tensor_custom_zeros(size_t elem_size, u32 ndim, const u64 *shape);`                   | Create a zero-initialized custom tensor.              |
| [ ]  | `tensor *tensor_custom_full(size_t elem_size, u32 ndim, const u64 *shape, const void *value);` | Create a custom tensor filled with a specified value. |

---

# Sequence Generation

| Done | Function                                                                             | Description                                               |
| :--: | ------------------------------------------------------------------------------------ | --------------------------------------------------------- |
| [ ]  | `tensor *tensor_arange(tensor_dtype dtype, double start, double stop, double step);` | Create a tensor containing evenly spaced values.          |
| [ ]  | `tensor *tensor_linspace(tensor_dtype dtype, double start, double stop, u64 num);`   | Create a tensor containing linearly spaced values.        |
| [ ]  | `tensor *tensor_logspace(tensor_dtype dtype, double start, double stop, u64 num);`   | Create a tensor containing logarithmically spaced values. |

---

# Random Initialization

| Done | Function                                                                                                  | Description                                          |
| :--: | --------------------------------------------------------------------------------------------------------- | ---------------------------------------------------- |
| [ ]  | `tensor *tensor_rand(tensor_dtype dtype, u32 ndim, const u64 *shape);`                                    | Create a tensor with random values.                  |
| [ ]  | `tensor *tensor_rand_uniform(tensor_dtype dtype, u32 ndim, const u64 *shape, double low, double high);`   | Create a tensor sampled from a uniform distribution. |
| [ ]  | `tensor *tensor_rand_normal(tensor_dtype dtype, u32 ndim, const u64 *shape, double mean, double stddev);` | Create a tensor sampled from a normal distribution.  |

---

# Utility

| Done | Function                                                      | Description                                         |
| :--: | ------------------------------------------------------------- | --------------------------------------------------- |
| [ ]  | `tensor *tensor_clone(const tensor *src);`                    | Create a deep copy of a tensor.                     |
| [ ]  | `bool tensor_copy(tensor *dst, const tensor *src);`           | Copy one tensor into another.                       |
| [ ]  | `bool tensor_equal(const tensor *a, const tensor *b);`        | Compare two tensors for equality.                   |
| [ ]  | `bool tensor_zero(tensor *t);`                                | Set all tensor elements to zero.                    |
| [ ]  | `bool tensor_reshape(tensor *t, u32 ndim, const u64 *shape);` | Change tensor shape without copying data.           |
| [ ]  | `bool tensor_resize(tensor *t, u32 ndim, const u64 *shape);`  | Resize a tensor, reallocating storage if necessary. |
| [ ]  | `tensor *tensor_flatten(const tensor *t);`                    | Flatten a tensor into one dimension.                |
| [ ]  | `tensor *tensor_squeeze(const tensor *t);`                    | Remove dimensions of size one.                      |
| [ ]  | `tensor *tensor_unsqueeze(const tensor *t, u32 axis);`        | Insert a dimension of size one.                     |
| [ ]  | `tensor *tensor_slice(const tensor *t, ...);`                 | Create a tensor view from a slice.                  |
| [ ]  | `tensor *tensor_view(const tensor *t, ...);`                  | Create a tensor view without copying data.          |

---

# Arithmetic

| Done | Function                                                 | Description                           |
| :--: | -------------------------------------------------------- | ------------------------------------- |
| [ ]  | `tensor *tensor_add(const tensor *a, const tensor *b);`  | Element-wise tensor addition.         |
| [ ]  | `tensor *tensor_sub(const tensor *a, const tensor *b);`  | Element-wise tensor subtraction.      |
| [ ]  | `tensor *tensor_mul(const tensor *a, const tensor *b);`  | Element-wise tensor multiplication.   |
| [ ]  | `tensor *tensor_div(const tensor *a, const tensor *b);`  | Element-wise tensor division.         |
| [ ]  | `bool tensor_add_scalar(tensor *t, const void *scalar);` | Add a scalar to every element.        |
| [ ]  | `bool tensor_sub_scalar(tensor *t, const void *scalar);` | Subtract a scalar from every element. |
| [ ]  | `bool tensor_mul_scalar(tensor *t, const void *scalar);` | Multiply every element by a scalar.   |
| [ ]  | `bool tensor_div_scalar(tensor *t, const void *scalar);` | Divide every element by a scalar.     |

---

# Statistics

| Done | Function                                  | Description                              |
| :--: | ----------------------------------------- | ---------------------------------------- |
| [ ]  | `tensor *tensor_sum(const tensor *t);`    | Sum all tensor elements.                 |
| [ ]  | `tensor *tensor_mean(const tensor *t);`   | Compute the mean of all elements.        |
| [ ]  | `tensor *tensor_min(const tensor *t);`    | Compute the minimum element.             |
| [ ]  | `tensor *tensor_max(const tensor *t);`    | Compute the maximum element.             |
| [ ]  | `tensor *tensor_argmin(const tensor *t);` | Return the index of the minimum element. |
| [ ]  | `tensor *tensor_argmax(const tensor *t);` | Return the index of the maximum element. |
| [ ]  | `tensor *tensor_std(const tensor *t);`    | Compute the standard deviation.          |
| [ ]  | `tensor *tensor_var(const tensor *t);`    | Compute the variance.                    |

---

# Linear Algebra

| Done | Function                                                   | Description                           |
| :--: | ---------------------------------------------------------- | ------------------------------------- |
| [ ]  | `tensor *tensor_transpose(const tensor *t);`               | Transpose a matrix or tensor.         |
| [ ]  | `tensor *tensor_matmul(const tensor *a, const tensor *b);` | Matrix multiplication.                |
| [ ]  | `tensor *tensor_dot(const tensor *a, const tensor *b);`    | Dot product.                          |
| [ ]  | `tensor *tensor_outer(const tensor *a, const tensor *b);`  | Outer product.                        |
| [ ]  | `tensor *tensor_trace(const tensor *t);`                   | Compute the trace of a matrix.        |
| [ ]  | `tensor *tensor_inverse(const tensor *t);`                 | Compute the matrix inverse.           |
| [ ]  | `tensor *tensor_det(const tensor *t);`                     | Compute the determinant.              |
| [ ]  | `tensor *tensor_norm(const tensor *t);`                    | Compute the tensor norm.              |
| [ ]  | `tensor *tensor_eigen(const tensor *t);`                   | Compute eigenvalues and eigenvectors. |
| [ ]  | `tensor *tensor_svd(const tensor *t);`                     | Singular Value Decomposition.         |

---

# Neural Network Operations (Future)

| Done | Function                                             | Description                     |
| :--: | ---------------------------------------------------- | ------------------------------- |
| [ ]  | `tensor *tensor_exp(const tensor *t);`               | Element-wise exponential.       |
| [ ]  | `tensor *tensor_log(const tensor *t);`               | Element-wise natural logarithm. |
| [ ]  | `tensor *tensor_pow(const tensor *t, double power);` | Raise each element to a power.  |
| [ ]  | `tensor *tensor_sqrt(const tensor *t);`              | Element-wise square root.       |
| [ ]  | `tensor *tensor_relu(const tensor *t);`              | ReLU activation.                |
| [ ]  | `tensor *tensor_sigmoid(const tensor *t);`           | Sigmoid activation.             |
| [ ]  | `tensor *tensor_tanh(const tensor *t);`              | Hyperbolic tangent activation.  |
| [ ]  | `tensor *tensor_softmax(const tensor *t);`           | Softmax activation.             |
| [ ]  | `tensor *tensor_gelu(const tensor *t);`              | GELU activation.                |

---

# Autograd (Future)

| Done | Function                                 | Description                  |
| :--: | ---------------------------------------- | ---------------------------- |
| [ ]  | `tensor *tensor_grad(const tensor *t);`  | Return the gradient tensor.  |
| [ ]  | `tensor *tensor_backward(tensor *loss);` | Perform backpropagation.     |
| [ ]  | `tensor *tensor_jacobian(...);`          | Compute the Jacobian matrix. |
| [ ]  | `tensor *tensor_hessian(...);`           | Compute the Hessian matrix.  |
