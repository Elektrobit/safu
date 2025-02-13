// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonAddNewBool_utest.h"

SETUP(safuTestSafuJsonAddNewBoolSuccessObject)
TEARDOWN(safuTestSafuJsonAddNewBoolSuccessObject)

static void _testCase(struct json_object *jobj, const char *key, bool val) {
    PARAM("key = \"%s\"", key);
    PARAM("val = %d", val);

    struct json_object *jadd = MOCK_FUNC_REAL(json_object_new_boolean)(val);

    MOCK_FUNC_AFTER_CALL(json_object_new_boolean, 0);

    expect_value(__wrap_json_object_new_boolean, b, val);
    will_return(__wrap_json_object_new_boolean, jadd);

    expect_value(safuJsonAddObject, jobj, jobj);
    expect_value(safuJsonAddObject, name, key);
    expect_value(safuJsonAddObject, jdata, jadd);
    will_return(safuJsonAddObject, json_object_object_add(jobj, key, jadd));

    struct json_object *jbool = safuJsonAddNewBool(jobj, key, val);
    assert_non_null(jbool);
    assert_ptr_equal(jbool, jadd);
    assert_int_equal(json_object_get_boolean(jbool), val);
    assert_int_equal(json_object_get_boolean(json_object_object_get(jobj, key)), val);
}

void safuTestSafuJsonAddNewBoolSuccessObject(void **state) {
    TEST("safuJsonAddNewBool");
    SHOULD("%s", "successfully add a new bool to a json object");

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
