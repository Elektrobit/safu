// SPDX-License-Identifier: MIT

#include <cmocka_extensions/cmocka_extensions.h>

#include "safuCheckBase64Encoding_utest.h"

int safuTestSafuCheckBase64EncodingErrorSetup(UNUSED void **state) {
    return 0;
}

int safuTestSafuCheckBase64EncodingErrorTeardown(UNUSED void **state) {
    return 0;
}

void safuTestSafuCheckBase64EncodingError(UNUSED void **state) {
    safuResultE_t result = SAFU_RESULT_OK;

    TEST("safuCheckBase64Encoding");
    SHOULD("%s", "return SAFU_RESULT_FAILED since test string is NULL or empty");

    PARAM("Input is NULL");
    result = safuCheckBase64Encoding(NULL, 1);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    PARAM("Input is Empty");
    result = safuCheckBase64Encoding("", 0);
    assert_int_equal(result, SAFU_RESULT_FAILED);
}
