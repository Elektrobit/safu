// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

SETUP(safuTestSafuJsonGetBoolErrGetTypeObject)
TEARDOWN(safuTestSafuJsonGetBoolErrGetTypeObject)

static void _testCase(struct json_object *jobj, char *key, bool val) {
    PARAM("key = \"%s\"", key);
    PARAM("val = %d", val);

    bool initResult = false;
    bool result = initResult;

    MOCK_FUNC_AFTER_CALL(json_object_get_type, 0);

    expect_any(__wrap_json_object_get_type, obj);
    will_return(__wrap_json_object_get_type, json_type_array);

    int retval = safuJsonGetBool(jobj, key, 0, &result);

    assert_int_equal(retval, -1);
    assert_int_equal(result, initResult);
}

void safuTestSafuJsonGetBoolErrGetTypeObject(void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "return -1 when json_object_get_type fails");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;
    assert_non_null(jobj);

    struct {
        char *key;
        bool val;
    } testRows[] = {{"isFalse", false}, {"isTrue", true}, {"noBool", 42}};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewInt(jobj, testRows[i].key, testRows[i].val);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i].key, testRows[i].val);
    }
}
