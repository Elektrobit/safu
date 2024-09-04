// SPDX-License-Identifier: MIT
#include "safuTimeSpecCompare_utest.h"

#include <bits/time.h>
#include <time.h>

TEST_SUITE_FUNC_PROTOTYPES(_testSuiteSafuTimeSpecCompare)

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuTimeSpecCompareSelected),
        TEST_CASE(safuTestSafuTimeSpecCompareExhaustive),
        TEST_CASE(safuTestSafuTimeSpecCompareRealTimestamps),
    };

    return RUN_TEST_SUITE(tests, _testSuiteSafuTimeSpecCompare);
}

static int _testSuiteSafuTimeSpecCompareSetup(void **state) {
    struct timespec *olderTimestamp = calloc(1, sizeof(struct timespec));
    if (olderTimestamp != NULL && !clock_gettime(CLOCK_REALTIME, olderTimestamp)) {
        print_error("failed to get older time stamp for tests");
    }
    *state = olderTimestamp;
    return 0;
}
static int _testSuiteSafuTimeSpecCompareTeardown(void **state) {
    free(*state);
    *state = NULL;
    return 0;
}
