// SPDX-License-Identifier: MIT

#include <cmocka_extensions/cmocka_extensions.h>

#include "safuBase64Encode_utest.h"

int safuTestSafuBase64EncodeErrorSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuBase64EncodeErrorTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuBase64EncodeError(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_OK;
    char *testOutput = NULL;
    size_t testOutputLen = 0;

    TEST("safuBase64Encode");
    SHOULD("%s", "return SAFU_RESULT_FAILED since test string is NULL or empty");

    PARAM("Input is NULL");
    result = safuBase64Encode(NULL, 1, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Empty");
    result = safuBase64Encode("", 0, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);
}
