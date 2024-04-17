// SPDX-License-Identifier: MIT
#include "safuJsonAddNewTimestamp_utest.h"

SETUP(safuTestSafuJsonAddNewTimestampErrNewArrayObject)
TEARDOWN(safuTestSafuJsonAddNewTimestampErrNewArrayObject)

static void _testCase(struct json_object *jobj, const char *key, struct timespec timestamp) {
    PARAM("key = \"%s\"", key);
    PARAM("timestamp = { tv_sec = %ld, tv_nsec = %ld }", timestamp.tv_sec, timestamp.tv_nsec);

    MOCK_FUNC_AFTER_CALL(json_object_new_array, 0);
    will_return(__wrap_json_object_new_array, NULL);

    struct json_object *jtimestamp = safuJsonAddNewTimestamp(jobj, key, &timestamp);

    assert_null(jtimestamp);

    jtimestamp = json_object_object_get(jobj, key);

    assert_null(jtimestamp);
}

void safuTestSafuJsonAddNewTimestampErrNewArrayObject(void **state) {
    TEST("safuJsonAddNewTimestamp");
    SHOULD("%s", "fail to create an array for a timestamp to add to a json object");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    const struct {
        char *key;
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
        _testCase(jobj, testRows[i].key, testRows[i].time);
    }
}
