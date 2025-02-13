// SPDX-License-Identifier: MIT
#include "safuJsonGetBool_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuJsonGetBoolSuccessArray),
        TEST_CASE(safuTestSafuJsonGetBoolSuccessObject),
        TEST_CASE(safuTestSafuJsonGetBoolErrGetObjectFailedArray),
        TEST_CASE(safuTestSafuJsonGetBoolErrGetObjectFailedObject),
        TEST_CASE(safuTestSafuJsonGetBoolErrGetTypeArray),
        TEST_CASE(safuTestSafuJsonGetBoolErrGetTypeObject),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
