#!/bin/bash

CMD_PATH="$(realpath "$(dirname "$0")")"
BASE_DIR="$(realpath "$CMD_PATH/..")"
BUILD_TYPE="${1:-Release}"
. "$BASE_DIR/ci/common_names.sh"

"$CMD_PATH/build.sh" "$BUILD_TYPE"

"$BASE_DIR/test/coverage/run_asmcov.sh"

find "$RESULT_DIR/coverage_results" -name "*.trace" -delete

exit $?
