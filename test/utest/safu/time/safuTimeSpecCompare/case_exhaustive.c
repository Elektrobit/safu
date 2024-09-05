// SPDX-License-Identifier: MIT

#include <limits.h>
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecCompare_utest.h"

int safuTestSafuTimeSpecCompareExhaustiveSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuTimeSpecCompareExhaustiveTeardown(UNUSED void **state) {
    return 0;
}

static void _checkComparision(struct timespec a, struct timespec b) {
    int result = safuTimeSpecCompare(a, b);
    int value;
    if (a.tv_sec > b.tv_sec) {
        value = 1;
    } else if (a.tv_sec < b.tv_sec) {
        value = -1;
    } else if (a.tv_nsec > b.tv_nsec) {
        value = 1;
    } else if (a.tv_nsec < b.tv_nsec) {
        value = -1;
    } else {
        value = 0;
    }
    assert_int_equal(result, value);
}
void safuTestSafuTimeSpecCompareExhaustive(UNUSED void **state) {
    TEST("safuTimeSpecCompareExhaustive");
    SHOULD("%s", "successfully compare two timespec structs with a lot of combinations of values");

    time_t secsList[] = {0, 1, 12, 457789, 999999999, INT_MAX};
    long nsecsList[] = {0, 1, 42, 999999999};

    for (size_t as = 0; as < ARRAY_SIZE(secsList); as++) {
        for (size_t an = 0; an < ARRAY_SIZE(nsecsList); an++) {
            struct timespec a = {.tv_sec = secsList[as], .tv_nsec = nsecsList[an]};
            for (size_t bs = 0; bs < ARRAY_SIZE(secsList); bs++) {
                for (size_t bn = 0; bn < ARRAY_SIZE(nsecsList); bn++) {
                    struct timespec b = {.tv_sec = secsList[bs], .tv_nsec = nsecsList[bn]};
                    _checkComparision(a, b);
                }
            }
        }
    }
}
