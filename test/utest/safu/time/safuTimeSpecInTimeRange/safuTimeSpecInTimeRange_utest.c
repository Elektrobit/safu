// SPDX-License-Identifier: MIT
#include "safuTimeSpecInTimeRange_utest.h"

#include <time.h>

TEST_SUITE_FUNC_PROTOTYPES(_testSuiteSafuTimeSpecInTimeRange)

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuTimeSpecInTimeRangeRealTimestamps),
    };
    return RUN_TEST_SUITE(tests, _testSuiteSafuTimeSpecInTimeRange);
}

static int _testSuiteSafuTimeSpecInTimeRangeSetup(void **state) {
    struct timespec *times = calloc(4, sizeof(struct timespec));
    assert_non_null(times);
    int ret = clock_gettime(CLOCK_REALTIME, &times[OLDEST]);
    assert_int_equal(ret, 0);

    times[NOTSET].tv_sec = 0;
    times[NOTSET].tv_nsec = 0;

    *state = times;
    return 0;
}
static int _testSuiteSafuTimeSpecInTimeRangeTeardown(void **state) {
    free(*state);
    *state = NULL;
    return 0;
}
