// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonAddNewBool_utest.h"

SETUP(safuTestSafuJsonAddNewBoolErrNewObjectFailedObject)
TEARDOWN(safuTestSafuJsonAddNewBoolErrNewObjectFailedObject)

static void _testCase(struct json_object *jobj, const char *key, bool val) {
    PARAM("key = \"%s\"", key);
    PARAM("val = %d", val);

    MOCK_FUNC_AFTER_CALL(json_object_new_boolean, 0);

    expect_value(__wrap_json_object_new_boolean, b, val);
    will_return(__wrap_json_object_new_boolean, NULL);

    struct json_object *jbool = safuJsonAddNewBool(jobj, key, val);
    assert_null(jbool);
}

void safuTestSafuJsonAddNewBoolErrNewObjectFailedObject(void **state) {
    TEST("safuJsonAddNewBool");
    SHOULD("%s", "fail to create a json bool object to add to a json objct");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    struct {
        char *key;
        bool val;
    } testRows[] = {{"isFalse", false}, {"isTrue", true}};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i].key, testRows[i].val);
    }
}
