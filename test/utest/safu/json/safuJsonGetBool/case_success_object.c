// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

SETUP(safuTestSafuJsonGetBoolSuccessObject)
TEARDOWN(safuTestSafuJsonGetBoolSuccessObject)

static void _testCase(struct json_object *jarray, const char *key, bool val) {
    PARAM("key = \"%s\"", key);
    PARAM("val = %d", val);

    bool result;

    MOCK_FUNC_AFTER_CALL(json_object_get_boolean, 0);

    expect_any(__wrap_json_object_get_boolean, obj);
    will_return(__wrap_json_object_get_boolean, val);

    int retval = safuJsonGetBool(jarray, key, 0, &result);

    assert_int_equal(retval, 0);
    assert_int_equal(result, val);
}

void safuTestSafuJsonGetBoolSuccessObject(void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "successfully get a bool from a json object");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    struct {
        char *key;
        bool val;
    } testRows[] = {{"isTrue", true}, {"isFalse", false}};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewBool(jobj, testRows[i].key, testRows[i].val);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i].key, testRows[i].val);
    }
}
