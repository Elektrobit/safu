#!/bin/bash
set -e -u -o pipefail

CMD_PATH="$(realpath "$(dirname "$0")")"
BASE_DIR="$(realpath "$CMD_PATH/..")"
BUILD_TYPE="${1:-Release}"
. "$BASE_DIR/ci/common_names.sh"

cd "$CMAKE_BUILD_DIR"
cpack -G DEB
