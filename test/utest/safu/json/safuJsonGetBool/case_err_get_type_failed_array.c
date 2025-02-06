// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

SETUP(safuTestSafuJsonGetBoolErrGetTypeArray)
TEARDOWN(safuTestSafuJsonGetBoolErrGetTypeArray)

static void _testCase(struct json_object *jarray, size_t idx, bool val) {
    PARAM("idx = %lu", idx);
    PARAM("val = %d", val);

    bool initResult = false;
    bool result = initResult;

    MOCK_FUNC_AFTER_CALL(json_object_get_type, 0);

    expect_any(__wrap_json_object_get_type, obj);
    will_return(__wrap_json_object_get_type, json_type_array);

    int retval = safuJsonGetBool(jarray, NULL, idx, &result);

    assert_int_equal(retval, -1);
    assert_int_equal(result, initResult);
}

void safuTestSafuJsonGetBoolErrGetTypeArray(void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "return -1 when json_object_get_type fails");

    *(struct json_object **)state = json_object_new_array();
    struct json_object *jarray = *(struct json_object **)state;
    assert_non_null(jarray);

    bool testRows[] = {true, false, 42};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewInt(jarray, NULL, testRows[i]);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jarray, i, testRows[i]);
    }
}
