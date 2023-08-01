# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.21)
include(cmake/project.cmake)
include(cmake/ConfigureLibrary.cmake)

project(safu LANGUAGES C VERSION ${SAFU_VERSION})

configureLibrary(cmocka_extensions ${CMOCKA_EXTENSIONS_URI} ${CMOCKA_EXTENSIONS_REF})
configureLibrary(cmocka_mocks ${CMOCKA_MOCKS_URI} ${CMOCKA_MOCKS_REF})

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/dist/usr/local/lib/cmake")

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
