// SPDX-License-Identifier: MIT

#include "safuBase64Decode_utest.h"

int safuTestSafuBase64DecodeErrorSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuBase64DecodeErrorTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuBase64DecodeError(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_OK;
    unsigned char *testOutput = NULL;
    size_t testOutputLen = 0;

    TEST("safuBase64Decode");
    SHOULD("%s", "return SAFU_RESULT_FAILED since test string is NULL or empty");

    PARAM("Input is NULL");
    result = safuBase64Decode(NULL, 1, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Empty");
    result = safuBase64Decode("", 0, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Invalid");
    result = safuBase64Decode("!$%()?#+", 8, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Invalid Length");
    result = safuBase64Decode("SGVsbG8uCg==", 2, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Incomplete Padding");
    result = safuBase64Decode("SGVsbG8uCg=", 12, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Invalid Padding");
    result = safuBase64Decode("SGVsbG8uCg=?", 12, &testOutput, &testOutputLen);
    assert_int_equal(result, SAFU_RESULT_FAILED);
}
