// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonAddNewBool_utest.h"

SETUP(safuTestSafuJsonAddNewBoolSuccessArray)
TEARDOWN(safuTestSafuJsonAddNewBoolSuccessArray)

static void _testCase(struct json_object *jobj, size_t idx, bool val) {
    PARAM("idx = %ld", idx);
    PARAM("val = %d", val);

    struct json_object *jadd = MOCK_FUNC_REAL(json_object_new_boolean)(val);
    assert_non_null(jadd);

    MOCK_FUNC_AFTER_CALL(json_object_new_boolean, 0);

    expect_value(__wrap_json_object_new_boolean, b, val);
    will_return(__wrap_json_object_new_boolean, jadd);

    expect_value(safuJsonAddObject, jobj, jobj);
    expect_value(safuJsonAddObject, name, NULL);
    expect_value(safuJsonAddObject, jdata, jadd);
    will_return(safuJsonAddObject, json_object_array_add(jobj, jadd));

    struct json_object *jbool = safuJsonAddNewBool(jobj, NULL, val);
    assert_non_null(jbool);
    assert_ptr_equal(jbool, jadd);
    assert_int_equal(json_object_get_boolean(jbool), val);
    assert_int_equal(json_object_get_boolean(json_object_array_get_idx(jobj, idx)), val);
}

void safuTestSafuJsonAddNewBoolSuccessArray(void **state) {
    TEST("safuJsonAddNewBool");
    SHOULD("%s", "succesfully add a new bool to a json array");

    *(struct json_object **)state = json_object_new_array();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    bool testRows[] = {false, true};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, i, testRows[i]);
    }
}
