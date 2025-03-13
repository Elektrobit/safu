// SPDX-License-Identifier: MIT
#include <errno.h>

#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetBool_utest.h"

int safuTestSafuJsonGetBoolErrGetObjectFailedArraySetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuJsonGetBoolErrGetObjectFailedArrayTeardown(UNUSED void **state) {
    return 0;
}

static void _testCase(size_t idx) {
    PARAM("idx = %lu", idx);

    bool initResult = true;
    bool result = initResult;

    int retval = safuJsonGetBool(NULL, NULL, idx, &result);

    assert_int_equal(retval, -1);
    assert_int_equal(result, initResult);
}

void safuTestSafuJsonGetBoolErrGetObjectFailedArray(UNUSED void **state) {
    TEST("safuJsonGetBool");
    SHOULD("%s", "return -1 when safuJsonGetObject fails with an array index");

    for (size_t i = 0; i < 6; i++) {
        _testCase(i);
    }
}
