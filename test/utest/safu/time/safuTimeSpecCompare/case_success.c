// SPDX-License-Identifier: MIT

#include <limits.h>
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecCompare_utest.h"

int safuTestSafuTimeSpecCompareSuccessSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuTimeSpecCompareSuccessTeardown(UNUSED void **state) {
    return 0;
}

static void _manualChecks() {
    struct timespec x;
    struct timespec y;
    int cmp;
    safuResultE_t result;

    // x > y
    x.tv_sec = 6;
    y.tv_sec = 4;
    result = safuTimeSpecCompare(&x, &y, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_int_equal(cmp, 1);

    // x < y
    x.tv_sec = 6;
    y.tv_sec = 8;
    result = safuTimeSpecCompare(&x, &y, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_int_equal(cmp, -1);

    // x > y
    y.tv_sec = x.tv_sec;
    x.tv_nsec = 23;
    y.tv_nsec = 12;
    result = safuTimeSpecCompare(&x, &y, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_int_equal(cmp, 1);

    // x < y
    y.tv_sec = x.tv_sec;
    x.tv_nsec = 23;
    y.tv_nsec = 42;
    result = safuTimeSpecCompare(&x, &y, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_int_equal(cmp, -1);

    // x == y
    y.tv_sec = x.tv_sec;
    x.tv_nsec = y.tv_nsec;
    result = safuTimeSpecCompare(&x, &y, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_int_equal(cmp, 0);
}

static void _checkComparision(struct timespec const *a, struct timespec const *b) {
    int cmp;
    safuResultE_t result = safuTimeSpecCompare(a, b, &cmp);
    assert_int_equal(result, SAFU_RESULT_OK);
    int value;
    if (a->tv_sec > b->tv_sec) {
        value = 1;
    } else if (a->tv_sec < b->tv_sec) {
        value = -1;
    } else if (a->tv_nsec > b->tv_nsec) {
        value = 1;
    } else if (a->tv_nsec < b->tv_nsec) {
        value = -1;
    } else {
        value = 0;
    }
    assert_int_equal(cmp, value);
}

static void _genericChecks() {
    time_t secsList[] = {0, 1, 12, INT_MAX};
    long nsecsList[] = {0, 1, 42, INT_MAX};

    for (size_t as = 0; as < ARRAY_SIZE(secsList); as++) {
        for (size_t an = 0; an < ARRAY_SIZE(nsecsList); an++) {
            struct timespec a = {.tv_sec = secsList[as], .tv_nsec = nsecsList[an]};
            for (size_t bs = 0; bs < ARRAY_SIZE(secsList); bs++) {
                for (size_t bn = 0; bn < ARRAY_SIZE(nsecsList); bn++) {
                    struct timespec b = {.tv_sec = secsList[bs], .tv_nsec = nsecsList[bn]};
                    _checkComparision(&a, &b);
                }
            }
        }
    }
}

void safuTestSafuTimeSpecCompareSuccess(UNUSED void **state) {
    TEST("safuTimeSpecCompareSuccess");
    SHOULD("%s", "successfully comare two timespec structs");

    _manualChecks();
    _genericChecks();
}
