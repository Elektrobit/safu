// SPDX-License-Identifier: MIT
#include "safuJsonAddNewBool_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuJsonAddNewBoolSuccessArray),
        TEST_CASE(safuTestSafuJsonAddNewBoolSuccessObject),
        TEST_CASE(safuTestSafuJsonAddNewBoolErrAddObjectFailedArray),
        TEST_CASE(safuTestSafuJsonAddNewBoolErrAddObjectFailedObject),
        TEST_CASE(safuTestSafuJsonAddNewBoolErrNewObjectFailedArray),
        TEST_CASE(safuTestSafuJsonAddNewBoolErrNewObjectFailedObject),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
