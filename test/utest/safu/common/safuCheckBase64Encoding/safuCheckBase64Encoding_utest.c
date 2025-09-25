// SPDX-License-Identifier: MIT
#include "safuCheckBase64Encoding_utest.h"

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuCheckBase64EncodingSuccessStringEncoded),
        TEST_CASE(safuTestSafuCheckBase64EncodingError),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
