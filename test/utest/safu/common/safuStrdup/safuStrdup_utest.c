// SPDX-License-Identifier: MIT

#include "safuStrdup_utest.h"

int main() {
    const struct CMUnitTest tests[] = {cmocka_unit_test(safuTestSafuStrdupSuccessStringDuplicated),
                                       cmocka_unit_test(safuTestSafuStrdupErrorInputNull),
                                       cmocka_unit_test(safuTestSafuStrdupExterrStrdup)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}
