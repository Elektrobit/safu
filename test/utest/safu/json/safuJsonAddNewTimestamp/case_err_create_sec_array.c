// SPDX-License-Identifier: MIT
#include "safuJsonAddNewTimestamp_utest.h"

SETUP(safuTestSafuJsonAddNewTimestampErrCreateSecArray)
TEARDOWN(safuTestSafuJsonAddNewTimestampErrCreateSecArray)

static void _testCase(struct json_object *jobj, size_t idx, struct timespec timestamp) {
    PARAM("idx = %lu", idx);
    PARAM("timestamp = { tv_sec = %ld, tv_nsec = %ld }", timestamp.tv_sec, timestamp.tv_nsec);

    MOCK_FUNC_AFTER_CALL(json_object_new_array, 0);
    struct json_object *jtimewrap = __real_json_object_new_array();
    will_return(__wrap_json_object_new_array, jtimewrap);

    MOCK_FUNC_AFTER_CALL(json_object_new_int64, 0);
    expect_value(__wrap_json_object_new_int64, i, timestamp.tv_sec);
    will_return(__wrap_json_object_new_int64, NULL);

    struct json_object *jtimestamp = safuJsonAddNewTimestamp(jobj, NULL, &timestamp);

    assert_null(jtimestamp);

    assert_int_equal(0, json_object_array_length(jobj));

    jtimestamp = json_object_array_get_idx(jobj, idx);
    assert_null(jtimestamp);
}

void safuTestSafuJsonAddNewTimestampErrCreateSecArray(void **state) {
    TEST("safuJsonAddNewTimestamp");
    SHOULD("%s", "fail to add the seconds of a timestamp to a json array");

    *(struct json_object **)state = __real_json_object_new_array();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    const struct timespec testRows[] = {
        {0, 0},          {0, 42},          {0, INTMAX_MAX},          {0, INTMAX_MIN},          {0, -12},
        {42, 0},         {42, 42},         {42, INTMAX_MAX},         {42, INTMAX_MIN},         {42, -12},
        {INTMAX_MAX, 0}, {INTMAX_MAX, 42}, {INTMAX_MAX, INTMAX_MAX}, {INTMAX_MAX, INTMAX_MIN}, {INTMAX_MAX, -12},
        {INTMAX_MIN, 0}, {INTMAX_MIN, 42}, {INTMAX_MIN, INTMAX_MAX}, {INTMAX_MIN, INTMAX_MIN}, {INTMAX_MIN, -12},
        {-12, 0},        {-12, 42},        {-12, INTMAX_MAX},        {-12, INTMAX_MIN},        {-12, -12},
    };
    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, i, testRows[i]);
    }
}
