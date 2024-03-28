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
if (UNIT_TESTS)
  enable_testing()
endif (UNIT_TESTS)

add_subdirectory(src)
add_subdirectory(test/utest)

if(PACKAGING)
  include(cmake/Packing.cmake)
endif(PACKAGING)
