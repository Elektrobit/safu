// SPDX-License-Identifier: MIT

#include <safu/result.h>

#include "safuStrdup_utest.h"

int safuTestSafuStrdupErrorrInputNullSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuStrdupErrorInputNullTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuStrdupErrorInputNull(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_FAILED;
    const char *testInput = NULL;
    char *testOutput = NULL;

    TEST("safuStrdup");
    SHOULD("%s", "return null pointer to null input string");

    result = safuStrdup(&testOutput, testInput);
    assert_int_equal(result, SAFU_RESULT_FAILED);
    assert_null(testOutput);
}
