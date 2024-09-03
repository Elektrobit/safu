// SPDX-License-Identifier: MIT
#include <safu/result.h>
#include <safu/time.h>

#include "safuTimeSpecCompare_utest.h"

int safuTestSafuTimeSpecCompareErrorParameterSetup(UNUSED void **state) {
    return 0;
}
int safuTestSafuTimeSpecCompareErrorParameterTeardown(UNUSED void **state) {
    return 0;
}
#define CMP_BASELINE 74
void safuTestSafuTimeSpecCompareErrorParameter(UNUSED void **state) {
    TEST("safuTimeSpecCompareErrorParameter");
    SHOULD("%s", "fail to compare two struct timespec because of NULL pointer");

    struct timespec timeA = {.tv_sec = 603, .tv_nsec = 4242};
    struct timespec timeB = {.tv_sec = 2348, .tv_nsec = 32};
    int cmp = CMP_BASELINE;
    safuResultE_t result;

    result = safuTimeSpecCompare(&timeA, NULL, &cmp);
    assert_int_equal(result, SAFU_RESULT_FAILED);
    assert_int_equal(cmp, CMP_BASELINE);

    result = safuTimeSpecCompare(NULL, &timeB, &cmp);
    assert_int_equal(result, SAFU_RESULT_FAILED);
    assert_int_equal(cmp, CMP_BASELINE);

    result = safuTimeSpecCompare(NULL, NULL, &cmp);
    assert_int_equal(result, SAFU_RESULT_FAILED);
    assert_int_equal(cmp, CMP_BASELINE);

    result = safuTimeSpecCompare(&timeA, &timeB, NULL);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    result = safuTimeSpecCompare(&timeA, NULL, NULL);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    result = safuTimeSpecCompare(NULL, &timeB, NULL);
    assert_int_equal(result, SAFU_RESULT_FAILED);

    result = safuTimeSpecCompare(NULL, NULL, NULL);
    assert_int_equal(result, SAFU_RESULT_FAILED);
}
