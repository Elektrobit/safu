// SPDX-License-Identifier: MIT
#include "safuJsonGetTimestamp_utest.h"

SETUP(safuTestSafuJsonGetTimestampErrGetSecsFailedObject)
TEARDOWN(safuTestSafuJsonGetTimestampErrGetSecsFailedObject)

static void _testCase(const struct json_object *jobj, const char *name) {
    PARAM("name = \"%s\"", name);
    struct timespec result = {70, 70};

    expect_any(safuJsonGetInt64, jobj);
    expect_value(safuJsonGetInt64, name, NULL);
    expect_value(safuJsonGetInt64, idx, 0);
    expect_any(safuJsonGetInt64, val);
    will_return_error(safuJsonGetInt64);

    int retval = safuJsonGetTimestamp(jobj, name, 0, &result);

    assert_int_equal(retval, -1);
    assert_int_equal(result.tv_sec, 70);
    assert_int_equal(result.tv_nsec, 70);
}

void safuTestSafuJsonGetTimestampErrGetSecsFailedObject(void **state) {
    TEST("safuJsonGetTimestamp");
    SHOULD("%s", "fail to get the seconds of a Timestamp from a json object");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    const struct {
        char *name;
        struct timespec time;
    } testRows[] = {
        {"zero,zero", {0, 0}},
        {"zero,some", {0, 42}},
        {"zero/max", {0, INTMAX_MAX}},
        {"zero|min", {0, INTMAX_MIN}},
        {"zero minus", {0, -12}},
        {"stuff-nothing", {42, 0}},
        {"stuff_stuff", {42, 42}},
        {"stuff, Max", {42, INTMAX_MAX}},
        {"stuff MINIMUM", {42, INTMAX_MIN}},
        {"somthing and somthing negativ", {42, -12}},
        {"Maximum:0", {INTMAX_MAX, 0}},
        {"Maximum|fortytwo", {INTMAX_MAX, 42}},
        {"Maximum+Maximum", {INTMAX_MAX, INTMAX_MAX}},
        {"MaximumMinimum", {INTMAX_MAX, INTMAX_MIN}},
        {"Maximum|minus", {INTMAX_MAX, -12}},
        {"Mini/zero", {INTMAX_MIN, 0}},
        {"Mini fortytwo", {INTMAX_MIN, 42}},
        {"Mini|Maximum", {INTMAX_MIN, INTMAX_MAX}},
        {"Mini*2", {INTMAX_MIN, INTMAX_MIN}},
        {"Mini\\Negativ", {INTMAX_MIN, -12}},
        {"negativ!zero", {-12, 0}},
        {"negativ fortytwo", {-12, 42}},
        {"negativ!INTMAX_MAX", {-12, INTMAX_MAX}},
        {"negativ Minimum", {-12, INTMAX_MIN}},
        {"negativ!negativ", {-12, -12}},
    };

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewTimestamp(jobj, testRows[i].name, &testRows[i].time);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i].name);
    }
}
