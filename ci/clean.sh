#!/bin/sh -eu
set -e -u

CMD_PATH="$(realpath "$(dirname "$0")")"
BASE_DIR="$(realpath "$CMD_PATH/..")"

OPTION_DEPS=1
for element in "$@"; do
    case $element in
	--no-deps)     OPTION_DEPS=0 ;;
        *)          echo "error: unknown option: $1"; exit 1 ;;
    esac
done

echo "remove build directories"
if [ $OPTION_DEPS -eq 1 ]; then
  rm -rf "$BASE_DIR/build"
else
  rm -rf \
    "$BASE_DIR/build/Debug" \
    "$BASE_DIR/build/Release" \
    "$BASE_DIR/build/doc"
fi

rm -rf "$BASE_DIR/doc/source/generated"
