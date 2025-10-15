// SPDX-License-Identifier: MIT

#pragma once

#include <cmocka_extensions/cmocka_extensions.h>
#include <safu/result.h>

#include "cmocka_mocks/mock_libc.h"
#include "safu/common.h"

TEST_CASE_FUNC_PROTOTYPES(safuTestSafuStrdupSuccessStringDuplicated)
TEST_CASE_FUNC_PROTOTYPES(safuTestSafuStrdupErrorInputNull)
TEST_CASE_FUNC_PROTOTYPES(safuTestSafuStrdupExterrStrdup)
