# SPDX-License-Identifier: MIT
if (UNIT_TESTS)
  include(unit_test.cmake)
  add_subdirectory(safu)
endif (UNIT_TESTS)
if (SAFU_MOCK_LIBRARY OR UNIT_TESTS)
  add_subdirectory(mocks)
endif (SAFU_MOCK_LIBRARY OR UNIT_TESTS)
