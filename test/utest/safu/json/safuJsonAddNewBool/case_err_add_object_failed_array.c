// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonAddNewBool_utest.h"

SETUP(safuTestSafuJsonAddNewBoolErrAddObjectFailedArray)
TEARDOWN(safuTestSafuJsonAddNewBoolErrAddObjectFailedArray)

static void _testCase(struct json_object *jobj, bool val) {
    PARAM("val = %d", val);

    struct json_object *jadd = MOCK_FUNC_REAL(json_object_new_boolean)(val);

    MOCK_FUNC_AFTER_CALL(json_object_new_boolean, 0);

    expect_value(__wrap_json_object_new_boolean, b, val);
    will_return(__wrap_json_object_new_boolean, jadd);

    expect_value(safuJsonAddObject, jobj, jobj);
    expect_value(safuJsonAddObject, name, NULL);
    expect_value(safuJsonAddObject, jdata, jadd);
    will_return(safuJsonAddObject, -1);

    struct json_object *jbool = safuJsonAddNewBool(jobj, NULL, val);
    assert_null(jbool);
}

void safuTestSafuJsonAddNewBoolErrAddObjectFailedArray(void **state) {
    TEST("safuJsonAddNewBool");
    SHOULD("%s", "fail to add an object with an boolean to an array");
    *(struct json_object **)state = json_object_new_array();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    bool testRows[] = {false, true};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i]);
    }
}
