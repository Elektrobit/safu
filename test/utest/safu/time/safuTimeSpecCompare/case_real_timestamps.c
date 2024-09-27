// SPDX-License-Identifier: MIT

#include <limits.h>
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecCompare_utest.h"

int safuTestSafuTimeSpecCompareRealTimestampsSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuTimeSpecCompareRealTimestampsTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuTimeSpecCompareRealTimestamps(void **state) {
    TEST("safuTimeSpecCompareRealTimestamp");
    SHOULD(
        "%s",
        "successfully compare two timespec structs gotten from the system clock to make sure it's a real time stamp");

    int result;
    struct timespec *olderTimestamp = *state;
    struct timespec newerTimestamp = {0};
    if (clock_gettime(CLOCK_REALTIME, &newerTimestamp) != 0) {
        print_error("failed to get newer time stamp for tests");
        fail();
    }

    result = safuTimeSpecCompare(newerTimestamp, *olderTimestamp);
    assert_int_equal(result, 1);

    result = safuTimeSpecCompare(newerTimestamp, newerTimestamp);
    assert_int_equal(result, 0);

    result = safuTimeSpecCompare(*olderTimestamp, newerTimestamp);
    assert_int_equal(result, -1);

    result = safuTimeSpecCompare(*olderTimestamp, *olderTimestamp);
    assert_int_equal(result, 0);
}
