// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

int safuTestSafuJsonGetBoolErrGetObjectFailedObjectSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuJsonGetBoolErrGetObjectFailedObjectTeardown(UNUSED void **state) {
    return 0;
}

static void _testCase(const char *key) {
    PARAM("key = \"%s\"", key);

    bool initResult = false;
    bool result = initResult;

    int retval = safuJsonGetBool(NULL, key, 0, &result);

    assert_int_equal(retval, -1);
    assert_int_equal(result, initResult);
}

void safuTestSafuJsonGetBoolErrGetObjectFailedObject(UNUSED void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "return -1 when safuJsonGetObject fails with an array index");

    char *testRows[] = {"IsTrue", "IsFalse"};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(testRows[i]);
    }
}
