# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.21)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

function(fetchLibrary LIBRARY_NAME LIBRARY_REPOSITORY LIBRARY_TAG)
  message("Fetching ${LIBRARY_NAME}")

  FetchContent_Declare(
    ${LIBRARY_NAME}
    GIT_REPOSITORY ${LIBRARY_REPOSITORY}
    GIT_TAG ${LIBRARY_TAG}
  )
  FetchContent_MakeAvailable(${LIBRARY_NAME})

  while(NOT EXISTS ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/cmake/_deps/${LIBRARY_NAME}-src/ci/build.sh)
    execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 0.5)
  endwhile()
  message("Done fetching")
  message("Building ${LIBRARY_NAME}")

  set(ENV{LOCAL_INSTALL_DIR} ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/dist)

  execute_process(
  COMMAND ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/cmake/_deps/${LIBRARY_NAME}-src/ci/build.sh ${CMAKE_BUILD_TYPE}
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/cmake/_deps/${LIBRARY_NAME}-src/"
  COMMAND_ECHO STDOUT
  )

  message("Done building")
endfunction()
