#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdarg.h>

#include "colorize.h"

#define ASSERT_IS_TRUE(a, msg, ...)                                                    \
    {                                                                                  \
        if (a)                                                                         \
        {                                                                              \
            printf(msg "" ANSI_COLOR_GREEN " PASSED" ANSI_COLOR_RESET"\n", ##__VA_ARGS__); \
        }                                                                              \
        else                                                                           \
        {                                                                              \
            printf(msg "" ANSI_COLOR_RED " FAILED" ANSI_COLOR_RESET"\n", ##__VA_ARGS__);   \
            return -1;                                                                 \
        }                                                                              \
    }

#define ASSERT_IS_EQUAL(a, b, msg, ...) ASSERT_IS_TRUE((a) == (b), msg, ##__VA_ARGS__)
#define ASSERT_IS_NOT_EQUAL(a, b, msg, ...) ASSERT_IS_TRUE((a) != (b), msg, ##__VA_ARGS__)
#define ASSERT_IS_NULL(a, msg, ...) ASSERT_IS_TRUE((a) == NULL, msg, ##__VA_ARGS__)
#define ASSERT_IS_NOT_NULL(a, msg, ...) ASSERT_IS_TRUE((a) != NULL, msg, ##__VA_ARGS__)
#define ASSERT(msg, ...) ASSERT_IS_TRUE(1, msg, ##__VA_ARGS__)

#endif // _TESTER_H_