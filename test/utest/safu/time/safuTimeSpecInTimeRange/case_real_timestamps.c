// SPDX-License-Identifier: MIT

#include <limits.h>
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecInTimeRange_utest.h"

int safuTestSafuTimeSpecInTimeRangeRealTimestampsSetup(void **state) {
    struct timespec *times = *state;
    int ret = clock_gettime(CLOCK_REALTIME, &times[MIDDLE]);
    assert_int_equal(ret, 0);
    return 0;
}

int safuTestSafuTimeSpecInTimeRangeRealTimestampsTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuTimeSpecInTimeRangeRealTimestamps(void **state) {
    TEST("safuTimeSpecInTimeRangeRealTimestamp");
    SHOULD("%s", "check if a timespec struct is inside a time range, using timestamps gotten from system clock");

    bool result;
    struct timespec *times = *state;
    int ret = clock_gettime(CLOCK_REALTIME, &times[NEWEST]);
    assert_int_equal(ret, 0);

    PARAM("newest >= middle > oldest");
    result = safuTimeSpecInTimeRange(times[NEWEST], times[MIDDLE], times[OLDEST]);
    assert_int_equal(result, true);

    PARAM("{0,0}  middle > oldest");
    result = safuTimeSpecInTimeRange(times[NOTSET], times[MIDDLE], times[OLDEST]);
    assert_int_equal(result, true);

    PARAM("{0,0}   middle !> middle");
    result = safuTimeSpecInTimeRange(times[NOTSET], times[MIDDLE], times[MIDDLE]);
    assert_int_equal(result, false);

    PARAM("{0,0}   middle   {0,0}");
    result = safuTimeSpecInTimeRange(times[NEWEST], times[MIDDLE], times[NOTSET]);
    assert_int_equal(result, true);

    PARAM("newest >= oldest   {0,0}");
    result = safuTimeSpecInTimeRange(times[NEWEST], times[OLDEST], times[NOTSET]);
    assert_int_equal(result, true);

    PARAM("oldest !>= newest   {0,0}");
    result = safuTimeSpecInTimeRange(times[OLDEST], times[NEWEST], times[NOTSET]);
    assert_int_equal(result, false);

    PARAM("newest >= newest > oldest");
    result = safuTimeSpecInTimeRange(times[NEWEST], times[NEWEST], times[OLDEST]);
    assert_int_equal(result, true);

    PARAM("newest >= newest !> newest");
    result = safuTimeSpecInTimeRange(times[NEWEST], times[NEWEST], times[NEWEST]);
    assert_int_equal(result, false);

    PARAM("middle >= oldest !> oldest");
    result = safuTimeSpecInTimeRange(times[MIDDLE], times[OLDEST], times[OLDEST]);
    assert_int_equal(result, false);
}
