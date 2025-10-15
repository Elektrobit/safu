// SPDX-License-Identifier: MIT

#include <stdlib.h>

#include "safuStrdup_utest.h"

int safuTestSafuStrdupSuccessrStringDuplicatedSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuStrdupSuccessStringDuplicatedTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuStrdupSuccessStringDuplicated(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_FAILED;
    const char *testInput = "testInput";
    char *testOutput = NULL;

    TEST("safuStrdup");
    SHOULD("%s", "return pointer to duplicate of input string");

    result = safuStrdup(&testOutput, testInput);
    assert_int_equal(result, SAFU_RESULT_OK);
    assert_string_equal(testOutput, "testInput");
    free(testOutput);
}
