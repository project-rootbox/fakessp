#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#define UNPACK(...) __VA_ARGS__


#define BASIC_ALIAS(ret, name, actual, args, topass) \
    ret name args { return actual topass; }
#define UNDERSCORE_ALIAS(ret, name, ...) \
    BASIC_ALIAS(ret, __##name, name, __VA_ARGS__)
#define CHECK_ALIAS(ret, name, ...) \
    BASIC_ALIAS(ret, __##name##_chk, name, __VA_ARGS__)


#define VA_ALIAS(ret, name, actual, args, topass, last) \
    ret name(UNPACK args, ...) {\
        va_list va;\
        ret r; \
        va_start(va, last); \
        r = actual(UNPACK topass, last, va); \
        va_end(va); \
        return r; \
    }
#define VA_CHECK_ALIAS(ret, name, ...) \
    VA_ALIAS(ret, __##name##_chk, name, __VA_ARGS__)


CHECK_ALIAS(void*, memcpy,
            (void* dst, const void* src, size_t len, size_t destlen),
            (dst, src, len))
CHECK_ALIAS(void*, memset,
            (void* dst, int value, size_t len, size_t destlen),
            (dst, value, len))
CHECK_ALIAS(char*, strcpy,
            (void* dst, const char* src, size_t dstlen),
            (dst, src))
CHECK_ALIAS(int, vsnprintf,
            (char* str, size_t len, int flags, size_t strlen,
             const char* format, va_list va),
            (str, len, format, va))

UNDERSCORE_ALIAS(int, isinf, (double value), (value))
UNDERSCORE_ALIAS(int, isnan, (double value), (value))

VA_CHECK_ALIAS(int, fprintf,
               (FILE* file, int flag, const char* format),
               (file), format)
VA_CHECK_ALIAS(int, snprintf,
               (char* str, size_t len, int flags, size_t strlen,
                const char* format),
               (str, len), format)
