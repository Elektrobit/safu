// SPDX-License-Identifier: MIT

#include "safuStrdup_utest.h"

int safuTestSafuStrdupExterrStrdupSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuStrdupExterrStrdupTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuStrdupExterrStrdup(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_FAILED;
    const char *testInput = "testInput";
    char *testOutput = NULL;

    TEST("safuStrdup");
    SHOULD("%s", "receive error duplicating string");

    MOCK_FUNC_AFTER_CALL(strdup, 0);
    expect_value(__wrap_strdup, string, testInput);
    will_return(__wrap_strdup, NULL);

    result = safuStrdup(&testOutput, testInput);
    assert_int_equal(result, SAFU_RESULT_FAILED);
    assert_null(testOutput);
}
