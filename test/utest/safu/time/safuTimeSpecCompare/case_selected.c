// SPDX-License-Identifier: MIT

#include <limits.h>
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecCompare_utest.h"

int safuTestSafuTimeSpecCompareSelectedSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuTimeSpecCompareSelectedTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuTimeSpecCompareSelected(UNUSED void **state) {
    TEST("safuTimeSpecCompareSelected");
    SHOULD("%s", "successfully compare two timespec structs with a selected number of specific comparisons");

    struct timespec timeA;
    struct timespec timeB;
    int result;

    // x > y
    timeA.tv_sec = 6;
    timeB.tv_sec = 4;
    result = safuTimeSpecCompare(timeA, timeB);
    assert_int_equal(result, 1);

    // x < y
    timeA.tv_sec = 6;
    timeB.tv_sec = 8;
    result = safuTimeSpecCompare(timeA, timeB);
    assert_int_equal(result, -1);

    // x > y
    timeB.tv_sec = timeA.tv_sec;
    timeA.tv_nsec = 23;
    timeB.tv_nsec = 12;
    result = safuTimeSpecCompare(timeA, timeB);
    assert_int_equal(result, 1);

    // x < y
    timeB.tv_sec = timeA.tv_sec;
    timeA.tv_nsec = 23;
    timeB.tv_nsec = 42;
    result = safuTimeSpecCompare(timeA, timeB);
    assert_int_equal(result, -1);

    // x == y
    timeB.tv_sec = timeA.tv_sec;
    timeA.tv_nsec = timeB.tv_nsec;
    result = safuTimeSpecCompare(timeA, timeB);
    assert_int_equal(result, 0);
}
