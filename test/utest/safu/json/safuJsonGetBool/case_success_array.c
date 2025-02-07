// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

SETUP(safuTestSafuJsonGetBoolSuccessArray)
TEARDOWN(safuTestSafuJsonGetBoolSuccessArray)

static void _testCase(struct json_object *jarray, size_t idx, bool val) {
    PARAM("idx = %lu", idx);
    PARAM("val = %d", val);

    bool result;

    MOCK_FUNC_AFTER_CALL(json_object_get_boolean, 0);

    expect_any(__wrap_json_object_get_boolean, obj);
    will_return(__wrap_json_object_get_boolean, val);

    int retval = safuJsonGetBool(jarray, NULL, idx, &result);

    assert_int_equal(retval, 0);
    assert_int_equal(result, val);
}

void safuTestSafuJsonGetBoolSuccessArray(void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "successfully get a bool from a json array");

    *(struct json_object **)state = json_object_new_array();
    struct json_object *jarray = *(struct json_object **)state;
    assert_non_null(jarray);

    bool testRows[] = {true, false};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewBool(jarray, NULL, testRows[i]);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jarray, i, testRows[i]);
    }
}
