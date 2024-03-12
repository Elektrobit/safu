# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.21)

include(cmake/project.cmake)

project(
  safu
    DESCRIPTION "SAFe Utilities"
    VERSION ${SAFU_VERSION}
    LANGUAGES C
)

project_set_environment()
project_set_version_variables()
project_add_documentation_target(
  TITLE
    "BaseOS Safu Documentation"
  MARKDOWN
    ${CMAKE_SOURCE_DIR}/documentation/documentation.md
)

add_subdirectory(src)
if(UNIT_TESTS)
  enable_testing()
  add_subdirectory(test/utest)
endif(UNIT_TESTS)

if(PACKAGING)
  include(cmake/Packing.cmake)
endif(PACKAGING)
