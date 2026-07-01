#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
 * @defgroup types Primitive Types
 * @brief Common fixed-width integer and floating-point type aliases.
 *
 * These aliases provide shorter, consistent names for standard C numeric
 * types defined in `<stdint.h>`. They improve readability and portability
 * across the library.
 *
 * @{
 */

/** @brief 32-bit IEEE 754 floating-point type. */
typedef float f32;

/** @brief 64-bit double-precision floating-point type. */
typedef double f64;

/** @brief Unsigned 8-bit integer. */
typedef uint8_t u8;

/** @brief Unsigned 16-bit integer. */
typedef uint16_t u16;

/** @brief Unsigned 32-bit integer. */
typedef uint32_t u32;

/** @brief Unsigned 64-bit integer. */
typedef uint64_t u64;

/** @brief Signed 8-bit integer. */
typedef int8_t i8;

/** @brief Signed 16-bit integer. */
typedef int16_t i16;

/** @brief Signed 32-bit integer. */
typedef int32_t i32;

/** @brief Signed 64-bit integer. */
typedef int64_t i64;

/** @} */

/**
 * @brief Iterate from 0 to n-1 using a 16-bit unsigned index.
 *
 * Expands to a standard for loop:
 *
 * @code
 * for (u16 i = 0; i < n; ++i)
 * @endcode
 *
 * @param i Loop variable name.
 * @param n Number of iterations.
 */
#define FOR_U16(i, n) \
    for (u16 i = 0; i < (n); ++i)

/**
 * @brief Iterate over a half-open range [begin, end) using a 16-bit unsigned index.
 *
 * Expands to:
 *
 * @code
 * for (u16 i = begin; i < end; ++i)
 * @endcode
 *
 * @param i Loop variable name.
 * @param begin Starting value (inclusive).
 * @param end Ending value (exclusive).
 */
#define FOR_RANGE_U16(i, begin, end) \
    for (u16 i = (begin); i < (end); ++i)

/**
 * @brief Iterate from 0 to n-1 using a 32-bit unsigned index.
 *
 * @param i Loop variable name.
 * @param n Number of iterations.
 */
#define FOR_U32(i, n) \
    for (u32 i = 0; i < (n); ++i)

/**
 * @brief Iterate over a half-open range [begin, end) using a 32-bit unsigned index.
 *
 * @param i Loop variable name.
 * @param begin Starting value (inclusive).
 * @param end Ending value (exclusive).
 */
#define FOR_RANGE_U32(i, begin, end) \
    for (u32 i = (begin); i < (end); ++i)

/**
 * @brief Iterate from 0 to n-1 using a 64-bit unsigned index.
 *
 * @param i Loop variable name.
 * @param n Number of iterations.
 */
#define FOR_U64(i, n) \
    for (u64 i = 0; i < (n); ++i)

/**
 * @brief Iterate over a half-open range [begin, end) using a 64-bit unsigned index.
 *
 * @param i Loop variable name.
 * @param begin Starting value (inclusive).
 * @param end Ending value (exclusive).
 */
#define FOR_RANGE_U64(i, begin, end) \
    for (u64 i = (begin); i < (end); ++i)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(x, lo, hi) \
    (MAX((lo), MIN((x), (hi))))
#define ABS(x) (((x) < 0) ? -(x) : (x))
#define SWAP(type, a, b) \
    do                   \
    {                    \
        type tmp = (a);  \
        (a) = (b);       \
        (b) = tmp;       \
    } while (0)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define BIT(x) (1ULL << (x))

#define SET_BIT(v, b) ((v) |= BIT(b))
#define CLEAR_BIT(v, b) ((v) &= ~BIT(b))
#define TOGGLE_BIT(v, b) ((v) ^= BIT(b))
#define TEST_BIT(v, b) (((v) & BIT(b)) != 0)

#define ALIGN_UP(x, a) \
    (((x) + ((a) - 1)) & ~((a) - 1))

#define ALIGN_DOWN(x, a) \
    ((x) & ~((a) - 1))

#define KB(x) ((x) * 1024ULL)
#define MB(x) (KB(x) * 1024ULL)
#define GB(x) (MB(x) * 1024ULL)

#define STATIC_ASSERT(cond, msg) \
    _Static_assert(cond, msg)

#define OFFSETOF(type, member) \
    ((size_t)&(((type *)0)->member))

#define ASSERT(expr)                                  \
    do                                                \
    {                                                 \
        if (!(expr))                                  \
        {                                             \
            fprintf(stderr,                           \
                    "Assertion failed: %s\n", #expr); \
            abort();                                  \
        }                                             \
    } while (0)

#define DEFAULT_IF_NULL(ptr, value) \
    ((ptr) ? (ptr) : (value))

#define NEW(type) ((type *)malloc(sizeof(type)))
#define NEW_ZERO(type) ((type *)calloc(1, sizeof(type)))

#define NEW_ARRAY(type, count) \
    ((type *)malloc(sizeof(type) * (count)))

#define NEW_ARRAY_ZERO(type, count) \
    ((type *)calloc((count), sizeof(type)))

#define DELETE(ptr) free(ptr)

#define REPEAT(n) \
    for (u32 _ = 0; _ < (n); ++_)

#endif /* TYPES_H */