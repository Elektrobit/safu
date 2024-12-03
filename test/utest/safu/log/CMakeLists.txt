# SPDX-License-Identifier: MIT

add_compile_definitions(SAFU_LOG="LOG")

add_subdirectory(safuLogFunc)
add_subdirectory(safuLogLevelFromString)
add_subdirectory(safuLogLevelToString)
add_subdirectory(safuLogSetFilterStr)
add_subdirectory(safuLogGetStreamLevel)
