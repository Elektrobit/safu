#!/bin/bash

CMD_PATH="$(realpath "$(dirname "$0")")"
BASE_DIR="$(realpath "$CMD_PATH/..")"
BUILD_TYPE="${1:-Debug}"
. "$BASE_DIR/ci/common_names.sh"

LICENSE_RESULT_DIR="${LINT_RESULT_DIR-${RESULT_DIR}/checklicense_results}"
LICENSE="MIT"

FINDINGS_LOGS=$LICENSE_RESULT_DIR/findings.log

function check_for_license {
    local SEARCH_PATH="$1"
    local SEARCH_PATTERN="$2"
    local LICENSE_HEADER="$3"

    local FINDINGS=0
    for i in $(find "$SEARCH_PATH" -type f -name "$SEARCH_PATTERN" -not -path "$BASE_DIR/build*/*"); do
        local FIRST_LINE
        FIRST_LINE="$(head -n1 "$i")"
        if ! echo "$FIRST_LINE" | grep -Eqs "$LICENSE_HEADER" ; then
            echo "invalid header in $i expected:" | tee -a "$FINDINGS_LOGS"
            echo -e "$LICENSE_HEADER\nbut found\n$FIRST_LINE\n" | tee -a "$FINDINGS_LOGS"
            (( FINDINGS++ ))
        fi
    done
    return $FINDINGS
}

mkdir -p "$LICENSE_RESULT_DIR"

FINDINGS=0

check_for_license "$BASE_DIR" "*.h" "// SPDX-License-Identifier: $LICENSE"
(( FINDINGS+=$? ))

check_for_license "$BASE_DIR" "*.c" "// SPDX-License-Identifier: $LICENSE"
(( FINDINGS+=$? ))

check_for_license "$BASE_DIR" "CMakeLists.txt" "# SPDX-License-Identifier: $LICENSE"
(( FINDINGS+=$? ))

if [ $FINDINGS -eq 0 ]; then
    echo "LICENSE OK" | tee -a "$FINDINGS_LOGS"
else
    echo "LICENSE CHECK FAILED ($FINDINGS issues)" | tee -a "$FINDINGS_LOGS"
fi

exit $FINDINGS
